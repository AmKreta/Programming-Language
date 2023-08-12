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
    if (type == Token::Type::PLUS)
        return child;
    if (type == Token::Type::MINUS)
        return -1 * child;
    // throw ExceptionFactory::create("operator", Token::getTokenTypeString(type), "not defined or not expected as unary operator");
}

double Interpreter::visitBinaryOperation(BinaryOperation *binaryOperation)
{
    double left = binaryOperation->getLeftChild() ? binaryOperation->getLeftChild()->acceptVisitor(this) : 0;
    double right = binaryOperation->getRightChild() ? binaryOperation->getRightChild()->acceptVisitor(this) : 0;
    auto op = binaryOperation->getOperation();
    if (op == Token::Type::PLUS)
        return left + right;
    if (op == Token::Type::MINUS)
        return left - right;
    if (op == Token::Type::MULTIPLY)
        return left * right;
    if (op == Token::Type::DIVIDE)
        return left / right;
    if (op == Token::Type::POWER)
        return std::pow(left, right);
    // throw ExceptionFactory::create("operator", Token::getTokenTypeString(op), "not defined or not expected as binary operator");
}

double Interpreter::interpret()
{
    auto eval = this->parser.parse();
    return eval->acceptVisitor(this);
}