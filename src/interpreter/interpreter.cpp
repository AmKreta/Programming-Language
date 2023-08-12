#include <interpreter/interpreter.hpp>
#include <exception/exceptionFactory.hpp>

Interpreter::Interpreter(Parser parser) : parser(parser) {}

double Interpreter::visitNumberConst(NumberConst *numberConst)
{
    return numberConst->getData();
}

double Interpreter::visitUnaryOperation(UnaryOperation *unaryOperation)
{
    double child = unaryOperation->getChild() ? unaryOperation->getChild()->acceptVisitor(this) : 0;
    auto type = unaryOperation->getType();
    switch (type)
    {
    case Token::Type::PLUS:
        return child;
    case Token::Type::MINUS:
        return -1 * child;
    default:
        throw ExceptionFactory("operator", Token::getTokenTypeString(op), "not defined or not expected as unary operator");
    }
}

double Interpreter::visitBinaryOperation(BinaryOperation *binaryOperation)
{
    double left = binaryOperation->getLeftChild() ? binaryOperation->getLeftChild()->acceptVisitor(this) : 0;
    double right = binaryOperation->getRightChild() ? binaryOperation->getRightChild()->acceptVisitor(this) : 0;
    auto op = binaryOperation->getOperation();
    switch (op)
    {
    case Token::Type::PLUS:
        return left + right;
    case Token::Type::MINUS:
        return left - right;
    case Token::Type::MULTIPLY:
        return left * right;
    case Token::Type::DIVIDE:
        return left / right;
    case Token::Type::POWER:
        return std::pow(left, right);
    default:
        throw ExceptionFactory("operator", Token::getTokenTypeString(op), "not defined or not expected as binary operator");
    }
}

double Interpreter::interpret()
{
    auto eval = this->parser.parse();
    return eval->acceptVisitor(this);
}