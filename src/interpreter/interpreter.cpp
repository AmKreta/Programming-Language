#include <interpreter/interpreter.hpp>
#include <exception/exceptionFactory.hpp>

Interpreter::Interpreter(Parser parser) : parser(parser) {}

RVal *Interpreter::visitNumberConst(NumberConst *numberConst)
{
    return numberConst;
}

RVal *Interpreter::visitUnaryOperation(UnaryOperation *unaryOperation)
{
    auto child = unaryOperation->getChild() ? unaryOperation->getChild()->acceptVisitor(this) : nullptr;
    if (child == nullptr)
        return nullptr;
    auto type = unaryOperation->getType(); // + / -
    auto dataType = child->getType();

    if (dataType == RVal::Type::NUMBER)
    {
        if (type == Token::Type::PLUS)
            return child;
        if (type == Token::Type::MINUS)
        {
            auto numConst = dynamic_cast<NumberConst *>(child);
            return new NumberConst(-1 * numConst->getData());
        }
        throw ExceptionFactory::create("operator", Token::getTokenTypeString(type), "not defined or not expected as unary operator");
    }

    throw ExceptionFactory::create("operator", Token::getTokenTypeString(type), "not defined or not expected as unary operator");
}

RVal *Interpreter::visitBinaryOperation(BinaryOperation *binaryOperation)
{
    auto left = binaryOperation->getLeftChild() ? binaryOperation->getLeftChild()->acceptVisitor(this) : nullptr;
    auto right = binaryOperation->getRightChild() ? binaryOperation->getRightChild()->acceptVisitor(this) : nullptr;
    auto op = binaryOperation->getOperation();
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = dynamic_cast<NumberConst *>(left)->getData();
        auto rightNum = dynamic_cast<NumberConst *>(right)->getData();
        if (op == Token::Type::PLUS)
            return new NumberConst(leftNum + rightNum);
        if (op == Token::Type::MINUS)
            return new NumberConst(leftNum - rightNum);
        if (op == Token::Type::MULTIPLY)
            return new NumberConst(leftNum * rightNum);
        if (op == Token::Type::DIVIDE)
            return new NumberConst(leftNum / rightNum);
        if (op == Token::Type::POWER)
            return new NumberConst(std::pow(leftNum, rightNum));
        throw ExceptionFactory::create("operator", Token::getTokenTypeString(op), "not defined or not expected as binary operator");
    }
    throw ExceptionFactory::create("DataType", RVal::getTypeString(left->getType()), " ", RVal::getTypeString(right->getType()), "are not compatible for binary operation", Token::getTokenTypeString(op));
}

double Interpreter::interpret()
{
    auto eval = this->parser.parse();
    auto res = eval->acceptVisitor(this);
    if (res->getType() == RVal::Type::NUMBER)
    {
        auto num = dynamic_cast<NumberConst *>(res);
        return num->getData();
    }
    return 0.0;
}