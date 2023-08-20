#include <interpreter/interpreter.hpp>
#include <exception/exceptionFactory.hpp>
#include <evaluable/rValueConstFactory.hpp>
#include <operations/mathemeticalOperation.hpp>
#include <operations/operationTypes.hpp>
#include <operations/logicalOperation.hpp>
#include <operations/relationalOperation.hpp>
#include <operations/bitwiseOperation.hpp>
#include <modules/console.hpp>
#include <rval/rVal.hpp>

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
    auto left = binaryOperation->getLeftChild() ? binaryOperation->getLeftChild()->acceptVisitor(this) : nullptr;
    auto right = binaryOperation->getRightChild() ? binaryOperation->getRightChild()->acceptVisitor(this) : nullptr;
    auto op = binaryOperation->getOperation();
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
    return condition
               ? conditionalOperation->get_if()->acceptVisitor(this)
               : conditionalOperation->get_else()->acceptVisitor(this);
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

void Interpreter::visitProgram(Program *program)
{
    // just traverse all the statements
    auto statementList = program->getStatementList();
    for (auto statement : statementList)
        statement->acceptVisitor(this);
}

void Interpreter::interpret()
{
    auto eval = this->parser.parse();
    eval->acceptVisitor(this);
    // Console::log(res);
    std::cout<<std::endl<<"content of scope"<<std::endl;
    for(auto& [key, val]: globalScope){
        std::cout<<key<<" ----> ";
        Console::log(val);
        std::cout<<std::endl;
    }
}