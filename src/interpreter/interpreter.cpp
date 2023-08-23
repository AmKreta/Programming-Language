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

Interpreter::Interpreter(Parser parser) : parser(parser) {}

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
    auto op = binaryOperation->getOperation();

    if (op == Token::Type::ASSIGNMENT)
        return AssignmentOperation::evaluate(this, binaryOperation->getLeftChild(), binaryOperation->getRightChild(), globalScope);

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
    auto var = globalScope.find(name);
    if (var != globalScope.end())
        return var->second;
    throw ExceptionFactory::create("Variable", name, "is not defined");
}

void Interpreter::visitVarDecleration(VarDecleration *varDecleration)
{
    auto declerations = varDecleration->getDeclerations();
    for (auto &[name, rVal] : declerations)
    {
        // put this in symbol table
        auto val = rVal->acceptVisitor(this);
        globalScope.insert(std::pair(name, val));
    }
}

void Interpreter::visitIfElse(IfElse *ifElse)
{
    auto condition = ifElse->getCondition()->acceptVisitor(this);
    if (ConversionFunctions::RValToBool(condition))
    {
        // create a new child symbol table
        ifElse->getIfBlock()->acceptVisitor(this);
        // exit child symbol table
    }
    else
    {
        // create a new child symbol table
        ifElse->getElseBlock()->acceptVisitor(this);
        // exit child symbol table
    }
}

void Interpreter::visitForLoop(ForLoop *forLoop)
{
    // create a new child in symbol table
    forLoop->getInitializations()->acceptVisitor(this);
    while (ConversionFunctions::RValToBool(forLoop->getCondition()->acceptVisitor(this)))
    {
        forLoop->getStatementList()->acceptVisitor(this);
        forLoop->getUpdates()->acceptVisitor(this);
    }
    // exit symbol table
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
    auto eval = this->parser.parse();
    eval->acceptVisitor(this);
    // Console::log(res);
    std::cout << std::endl
              << "\ncontent of symbol table\n"
              << std::endl;
    for (auto &[key, val] : globalScope)
    {
        std::cout << key << " ----> ";
        Console::log(val);
        std::cout << std::endl;
    }
}