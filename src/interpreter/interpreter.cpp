#include <interpreter/interpreter.hpp>
#include <exception/exceptionFactory.hpp>
#include <evaluable/rValueConstFactory.hpp>
#include <operations/mathemeticalOperation.hpp>
#include <operations/operationTypes.hpp>
#include <operations/logicalOperation.hpp>
#include <operations/relationalOperation.hpp>
#include <operations/bitwiseOperation.hpp>
#include <operations/assignmentOperation.hpp>
#include <modules/console.hpp>
#include <rVal/rVal.hpp>
#include <utility/conversionFunctions.hpp>
#include <symbol/symbolTableBuilder.hpp>

Interpreter::Interpreter(Parser *parser, CallStack callStack) : astNode(parser->parse()), callStack(callStack), hasReturned(false) {}

Interpreter::Interpreter(std::shared_ptr<AstNode> astNode, CallStack callStack) : callStack(callStack), astNode(astNode), hasReturned(false) {}

std::shared_ptr<RVal> Interpreter::visitRValConst(RVal *rValConst)
{
    if (rValConst->getType() == RVal::Type::FUNCTION)
    {
        auto fnConst = std::dynamic_pointer_cast<FunctionConst>(rValConst->getSharedPtr());
        auto fnAst = fnConst->getData();
        auto symbolTableBuilder = SymbolTableBuilder(fnAst->getSharedPtr(), std::make_shared<SymbolTable>(this->callStack.getActivationRecord()));
        symbolTableBuilder.buildForFunction(fnAst);
        return fnConst;
    }
    return rValConst->getSharedPtr();
}

std::shared_ptr<RVal> Interpreter::visitArrayAst(ArrayAst *arrayAst)
{
    RValPointerArray arr;
    for (auto children : arrayAst->getChildren())
        arr.push_back(children->acceptVisitor(this));
    return RValConstFactory::createArrayConstSharedPtr(arr);
}

std::shared_ptr<RVal> Interpreter::visitMapAst(MapAst *mapAst)
{
    RValPointerMap map;
    for (auto &[key, val] : mapAst->getEntries())
        map.insert(std::pair(key->acceptVisitor(this), val->acceptVisitor(this)));
    return RValConstFactory::createMapConstSharedPtr(map);
}

std::shared_ptr<RVal> Interpreter::visitUnaryOperation(UnaryOperation *unaryOperation)
{
    auto child = unaryOperation->getChild() ? unaryOperation->getChild()->acceptVisitor(this) : nullptr;
    auto type = unaryOperation->getType();
    if (type == Token::Type::LOGICAL_NOT)
        return LogicalExpression::evaluate(type, child);
    if (type == Token::Type::BITWISE_NOT)
        return BitwiseOperation::evaluate(type, child);
    if (type == Token::Type::PLUS || type == Token::Type::MINUS)
        return MathemeticalExpression::evaluate(type, child);
}

std::shared_ptr<RVal> Interpreter::visitBinaryOperation(BinaryOperation *binaryOperation)
{
    auto op = binaryOperation->getOperation();

    if (op == Token::Type::ASSIGNMENT)
        return AssignmentOperation::evaluate(this, binaryOperation->getLeftChild(), binaryOperation->getRightChild(), this->callStack.getActivationRecord());

    auto left = binaryOperation->getLeftChild() ? binaryOperation->getLeftChild()->acceptVisitor(this) : nullptr;
    auto right = binaryOperation->getRightChild() ? binaryOperation->getRightChild()->acceptVisitor(this) : nullptr;

    if (operatorTypes::mathemeticalOperators.find(op) != operatorTypes::mathemeticalOperators.end())
        return MathemeticalExpression::evaluate(left, op, right);

    if (operatorTypes::logicalOperators.find(op) != operatorTypes::logicalOperators.end())
        return LogicalExpression::evaluate(left, op, right);

    if (operatorTypes::relationalEqualityCheckOperators.find(op) != operatorTypes::relationalEqualityCheckOperators.end())
        return RelationalExpression::evaluate(left, op, right);
    if (operatorTypes::relationalComparisionOperators.find(op) != operatorTypes::relationalComparisionOperators.end())
        return RelationalExpression::evaluate(left, op, right);

    if (operatorTypes::bitwiseOperators.find(op) != operatorTypes::bitwiseOperators.end())
        return BitwiseOperation::evaluate(left, op, right);
    if (operatorTypes::bitwiseShiftOperators.find(op) != operatorTypes::bitwiseShiftOperators.end())
        return BitwiseOperation::evaluate(left, op, right);
}

std::shared_ptr<RVal> Interpreter::visitConditionalOperation(ConditionalOperation *conditionalOperation)
{
    auto condition = conditionalOperation->getCondition()->acceptVisitor(this);
    return ConversionFunctions::RValToBool(condition)
               ? conditionalOperation->get_if()->acceptVisitor(this)
               : conditionalOperation->get_else()->acceptVisitor(this);
}

std::shared_ptr<RVal> Interpreter::visitIndexing(Indexing *indexing)
{
    auto val = indexing->getVal()->acceptVisitor(this);
    auto index = indexing->getIndex()->acceptVisitor(this);
    if (val->getType() == RVal::Type::ARRAY && index->getType() == RVal::Type::NUMBER)
    {
        auto &arr = std::dynamic_pointer_cast<ArrayConst>(val)->getData();
        auto num = std::dynamic_pointer_cast<NumberConst>(index)->getData();
        return arr[static_cast<int>(num)]; // because no. can be double too
    }
    if (val->getType() == RVal::Type::MAP)
    {
        auto &map = std::dynamic_pointer_cast<MapConst>(val)->getData();
        auto res = map.find(index);
        if (res != map.end())
            return res->second;
        return RValConstFactory::createUndefinedConstSharedPtr();
    }
    throw ExceptionFactory::create("can't use indexing operator on", RVal::getTypeString(val->getType()));
}

std::shared_ptr<RVal> Interpreter::visitVariable(Variable *variable)
{
    auto name = variable->getVarName();
    auto activationRecord = this->callStack.getActivationRecord();
    auto res = activationRecord->getSymbol(name)->getValue();
    return res;
}

void Interpreter::visitPrint(Print *print)
{
    auto &args = print->getArgs();
    for (auto arg : args)
    {
        auto res = arg->acceptVisitor(this);
        Console::log(res);
    }
}

std::shared_ptr<RVal> Interpreter::visitFunctionCall(FunctionCall *functionCall)
{
    auto fn = functionCall->getFunction()->acceptVisitor(this);
    if (fn->getType() == RVal::Type::FUNCTION)
    {
        auto fnConst = std::dynamic_pointer_cast<FunctionConst>(fn);
        auto &functionAst = fnConst->getData();
        CallStack callStack{functionAst->getCorospondingSymbolTable()};
        Interpreter interpreter{functionAst, callStack};
        interpreter.interpret(functionCall->getArgs());
        auto res = functionAst->getReturnVal();
        return res;
    }
    throw ExceptionFactory::create("expression of type", fn->getTypeString(), "is not callable");
}

std::shared_ptr<RVal> Interpreter::visitFunction(Function *function)
{
    return nullptr;
}

void Interpreter::visitReturn(Return *ret)
{
    auto fn = std::dynamic_pointer_cast<Function>(this->astNode);
    if (fn)
    {
        auto expr = ret->getExpr();
        auto res = expr->acceptVisitor(this);
        fn->setReturnVal(res);
        this->hasReturned = true;
        // reset function here
    }
    else
        throw ExceptionFactory::create("Return can only be used inside function");
}

void Interpreter::visitVarDecleration(VarDecleration *varDecleration)
{
    auto &declerations = varDecleration->getDeclerations();
    auto activationRecord = this->callStack.getActivationRecord();
    for (auto &[name, expr] : declerations)
    {
        auto val = expr->acceptVisitor(this);
        activationRecord->setSymbol(name, val);
    }
}

void Interpreter::visitIfElse(IfElse *ifElse)
{
    auto condition = ifElse->getCondition()->acceptVisitor(this);
    if (ConversionFunctions::RValToBool(condition))
    {
        // std::cout<<"if ran ";
        this->callStack.pushScope();
        ifElse->getIfBlock()->acceptVisitor(this);
        this->callStack.popScope();
        this->callStack.skipScope(); // skipping one symbol tree
    }
    else
    {
        // std::cout << "else ran ";
        this->callStack.skipScope();
        this->callStack.pushScope();
        ifElse->getElseBlock()->acceptVisitor(this);
        this->callStack.popScope();
    }
}

void Interpreter::visitForLoop(ForLoop *forLoop)
{
    this->callStack.pushScope();
    forLoop->getInitializations()->acceptVisitor(this);
    while (ConversionFunctions::RValToBool(forLoop->getCondition()->acceptVisitor(this)))
    {
        forLoop->getStatementList()->acceptVisitor(this);
        forLoop->getUpdates()->acceptVisitor(this);
    }
    this->callStack.popScope();
}

void Interpreter::visitWhileLoop(WhileLoop *whileLoop)
{
    this->callStack.pushScope();
    while (ConversionFunctions::RValToBool(whileLoop->getCondition()->acceptVisitor(this)))
        whileLoop->getCompoundStatement()->acceptVisitor(this);
    this->callStack.popScope();
}

void Interpreter::visitExpressionStatement(ExpressionStatement *expressionStatement)
{
    auto expr = expressionStatement->getExpression();
    expr->acceptVisitor(this);
}

void Interpreter::visitCompoundStatement(CompoundStatement *compoundStatement)
{
    auto &statementList = compoundStatement->getStatementList();
    for (auto statement : statementList)
    {
        if (this->hasReturned)
            break;
        statement->acceptVisitor(this);
    }
}

void Interpreter::visitProgram(Program *program)
{
    // just traverse all the statements
    auto compoundStatement = program->getCompoundStatement();
    compoundStatement->acceptVisitor(this);
}

void Interpreter::interpret(std::vector<std::shared_ptr<Evaluable>> args)
{
    auto program = std::dynamic_pointer_cast<Program>(this->astNode);
    if (program)
    {
        program->acceptVisitor(this);
    }
    else
    {
        auto function = std::dynamic_pointer_cast<Function>(this->astNode);
        if (function)
        {
            auto &params = function->getParams();
            auto activationRecord = this->callStack.getActivationRecord();
            for(int i=0;i<params.size();i++){
                auto &[var, expr] = params[i];
                if(i<args.size())
                    activationRecord->setSymbol(var->getVarName(), args[i]->acceptVisitor(this));
                else
                    activationRecord->setSymbol(var->getVarName(), expr->acceptVisitor(this));
            }
            function->getCompoundStatement()->acceptVisitor(this);
        }
        else
        {
            throw ExceptionFactory::create("Interpret can only interpret Function and Program");
        }
    }
}

CallStack &Interpreter::getCallStack()
{
    return this->callStack;
}