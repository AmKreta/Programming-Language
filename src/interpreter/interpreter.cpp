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

auto globalScope = std::unordered_map<std::string, std::shared_ptr<RVal>>();

Interpreter::Interpreter(Parser* parser, CallStack callStack) : parser(parser), callStack(callStack) {}

Interpreter::Interpreter(CallStack callStack) : callStack(callStack), parser(nullptr) {}

std::shared_ptr<RVal> Interpreter::visitRValConst(RVal *rValConst)
{
    return std::shared_ptr<RVal>{rValConst};
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
    std::cout<<"ran\n";
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

std::shared_ptr<RVal> Interpreter::visitFunctionCall(FunctionCall *functionCall)
{
    auto fn = functionCall->getFunction()->acceptVisitor(this);
    if(fn->getType() == RVal::Type::FUNCTION){
        auto fnConst = std::dynamic_pointer_cast<FunctionConst>(fn);
        auto &functionAst = fnConst->getData();
        CallStack callStack{functionAst.getCorospondingSymbolTable()};
        Interpreter interpreter{callStack};
        interpreter.interpretFunction(functionAst);
        auto res = functionAst.getReturnVal();
        return res;
    }
    throw ExceptionFactory::create("expression of type", fn->getTypeString(), "is not callable");
}

std::shared_ptr<RVal> Interpreter::visitFunction(Function *function)
{
    return nullptr;
}

void Interpreter::visitVarDecleration(VarDecleration *varDecleration)
{
    auto declerations = varDecleration->getDeclerations();
    auto activationRecord = this->callStack.getActivationRecord();
    for (auto &[name, rVal] : declerations)
    {
        // put this in symbol table
        auto val = rVal->acceptVisitor(this);
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
    auto statementList = compoundStatement->getStatementList();
    for (auto statement : statementList)
        statement->acceptVisitor(this);
}

void Interpreter::visitProgram(Program *program)
{
    // just traverse all the statements
    auto compoundStatement = program->getCompoundStatement();
    compoundStatement->acceptVisitor(this);
}

void Interpreter::interpret()
{
    auto eval = this->parser->parse();
    eval->acceptVisitor(this);
}

void Interpreter::interpretFunction(Function& function){
   auto params = function.getParams();
   auto activationRecord = this->callStack.getActivationRecord();
   for(auto& [var, expr]:params)
    activationRecord->setSymbol(var->getVarName(), expr->acceptVisitor(this));
   function.getCompoundStatement()->acceptVisitor(this);
}

CallStack& Interpreter::getCallStack(){
    return this->callStack;
}