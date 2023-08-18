#include <interpreter/interpreter.hpp>
#include <exception/exceptionFactory.hpp>
#include <evaluable/rValueConstFactory.hpp>
#include <operations/mathemeticalOperation.hpp>
#include <modules/console.hpp>

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
    return MathemeticalExpression::evaluate(type, child);
}

std::shared_ptr<RVal> Interpreter::visitBinaryOperation(BinaryOperation *binaryOperation)
{
    auto left = binaryOperation->getLeftChild() ? binaryOperation->getLeftChild()->acceptVisitor(this) : nullptr;
    auto right = binaryOperation->getRightChild() ? binaryOperation->getRightChild()->acceptVisitor(this) : nullptr;
    auto op = binaryOperation->getOperation();
    return MathemeticalExpression::evaluate(left, op, right);
}

std::shared_ptr<RVal> Interpreter::visitConditionalOperation(ConditionalOperation *conditionalOperation)
{
    auto condition = conditionalOperation->getCondition()->acceptVisitor(this);
    return condition
               ? conditionalOperation->get_if()->acceptVisitor(this)
               : conditionalOperation->get_else()->acceptVisitor(this);
}

void Interpreter::interpret()
{
    auto eval = this->parser.parse();
    auto res = eval->acceptVisitor(this);
    Console::log(res);
}