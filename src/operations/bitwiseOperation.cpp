#include <operations/bitwiseOperation.hpp>
#include <evaluable/rValueConstFactory.hpp>
#include <exception/exceptionFactory.hpp>

// only works with number
std::shared_ptr<RVal> BitwiseOperation::evaluate(std::shared_ptr<RVal> left, Token::Type op, std::shared_ptr<RVal> right)
{
    if (op == Token::Type::BITWISE_AND)
        return BitwiseOperation::And(left, right);
    if (op == Token::Type::BITWISE_OR)
        return BitwiseOperation::Or(left, right);
    if (op == Token::Type::BITWISE_XOR)
        return BitwiseOperation::Xor(left, right);
    if (op == Token::Type::BITWISE_L_SHIFT)
        return BitwiseOperation::LShift(left, right);
    if (op == Token::Type::BITWISE_R_SHIFT)
        return BitwiseOperation::Rshift(left, right);
    throw ExceptionFactory::create("bitwiseOperation.cpp:-", Token::getTokenTypeString(op), "does not support bitwise operation");
}

std::shared_ptr<RVal> BitwiseOperation::evaluate(Token::Type op, std::shared_ptr<RVal> right)
{
    if (op == Token::Type::BITWISE_NOT)
        return BitwiseOperation::Not(right);
    throw ExceptionFactory::create("bitwiseOperation.cpp:-", Token::getTokenTypeString(op), "does not support bitwise operation");
}

std::shared_ptr<RVal> BitwiseOperation::And(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(left)->getData());
        auto rightNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(right)->getData());
        return RValConstFactory::createNumberConstSharedPtr(leftNum & rightNum);
    }
    throw ExceptionFactory::create("bitwiseOperation.cpp:-", " only number support bitwise & (and) operation");
}

std::shared_ptr<RVal> BitwiseOperation::Or(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(left)->getData());
        auto rightNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(right)->getData());
        return RValConstFactory::createNumberConstSharedPtr(leftNum | rightNum);
    }
    throw ExceptionFactory::create("bitwiseOperation.cpp:-", " only number support bitwise | (or) operation");
}

std::shared_ptr<RVal> BitwiseOperation::Xor(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(left)->getData());
        auto rightNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(right)->getData());
        return RValConstFactory::createNumberConstSharedPtr(leftNum ^ rightNum);
    }
    throw ExceptionFactory::create("bitwiseOperation.cpp:-", " only number support bitwise ^ (xor) operation");
}

std::shared_ptr<RVal> BitwiseOperation::Rshift(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(left)->getData());
        auto rightNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(right)->getData());
        return RValConstFactory::createNumberConstSharedPtr(leftNum >> rightNum);
    }
    throw ExceptionFactory::create("bitwiseOperation.cpp:-", " only number support bitwise >> (rightShift) operation");
}

std::shared_ptr<RVal> BitwiseOperation::LShift(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(left)->getData());
        auto rightNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(right)->getData());
        return RValConstFactory::createNumberConstSharedPtr(leftNum << rightNum);
    }
    throw ExceptionFactory::create("bitwiseOperation.cpp:-", " only number support bitwise << (leftShift) operation");
}

std::shared_ptr<RVal> BitwiseOperation::Not(std::shared_ptr<RVal> left)
{
    if (left->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(left)->getData());
        return RValConstFactory::createNumberConstSharedPtr(!left);
    }
    throw ExceptionFactory::create("bitwiseOperation.cpp:-", " only number support bitwise ~ (not) operation");
}