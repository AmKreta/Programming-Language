#include <interpreter/interpreter.hpp>
#include <exception/exceptionFactory.hpp>

Interpreter::Interpreter(Parser parser) : parser(parser) {}

RVal *Interpreter::visitRValConst(RVal *rValConst)
{
    return rValConst;
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
            auto res = RValConstFactory::createNumberConstPtr(-1 * numConst->getData());
            return res;
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
            return RValConstFactory::createNumberConstPtr(leftNum + rightNum);
        if (op == Token::Type::MINUS)
            return RValConstFactory::createNumberConstPtr(leftNum - rightNum);
        if (op == Token::Type::MULTIPLY)
            return RValConstFactory::createNumberConstPtr(leftNum * rightNum);
        if (op == Token::Type::DIVIDE)
            return RValConstFactory::createNumberConstPtr(leftNum / rightNum);
        if (op == Token::Type::POWER)
            return RValConstFactory::createNumberConstPtr(std::pow(leftNum, rightNum));
        throw ExceptionFactory::create("operator", Token::getTokenTypeString(op), "not defined or not expected as binary operator for number and number");
    }

    if (left->getType() == RVal::Type::STRING && right->getType() == RVal::Type::STRING)
    {
        auto leftStr = dynamic_cast<StringConst *>(left)->getData();
        auto rightStr = dynamic_cast<StringConst *>(right)->getData();
        if (op == Token::Type::PLUS)
            return RValConstFactory::createStringConstPtr(leftStr + rightStr);
        throw ExceptionFactory::create("operator", Token::getTokenTypeString(op), "not defined or not expected as binary operator for string and string");
    }
    throw ExceptionFactory::create("DataType", RVal::getTypeString(left->getType()), " ", RVal::getTypeString(right->getType()), "are not compatible for binary operation", Token::getTokenTypeString(op));
}

void Interpreter::interpret()
{
    auto eval = this->parser.parse();
    auto res = eval->acceptVisitor(this);
    if (res->getType() == RVal::Type::NUMBER)
    {
        auto num = dynamic_cast<NumberConst *>(res);
        std::cout<<num->getData();
    }
    if (res->getType() == RVal::Type::STRING)
    {
        auto num = dynamic_cast<StringConst *>(res);
        std::cout<<num->getData();
    }
}