#include <operations/bitwiseOperation.hpp>
#include <evaluable/rValueConstFactory.hpp>

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
}

std::shared_ptr<RVal> BitwiseOperation::evaluate(Token::Type op, std::shared_ptr<RVal> right)
{
    if (op == Token::Type::BITWISE_NOT)
        return BitwiseOperation::Not(right);
}

std::shared_ptr<RVal> BitwiseOperation::And(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(left)->getData());
        auto rightNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(right)->getData());
        return RValConstFactory::createNumberConstSharedPtr(leftNum & rightNum);
    }
}

std::shared_ptr<RVal> BitwiseOperation::Or(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(left)->getData());
        auto rightNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(right)->getData());
        return RValConstFactory::createNumberConstSharedPtr(leftNum | rightNum);
    }
}
std::shared_ptr<RVal> BitwiseOperation::Xor(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(left)->getData());
        auto rightNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(right)->getData());
        return RValConstFactory::createNumberConstSharedPtr(leftNum ^ rightNum);
    }
}

std::shared_ptr<RVal> BitwiseOperation::Rshift(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(left)->getData());
        auto rightNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(right)->getData());
        return RValConstFactory::createNumberConstSharedPtr(leftNum >> rightNum);
    }
}

std::shared_ptr<RVal> BitwiseOperation::LShift(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(left)->getData());
        auto rightNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(right)->getData());
        return RValConstFactory::createNumberConstSharedPtr(leftNum < rightNum);
    }
}

std::shared_ptr<RVal> BitwiseOperation::Not(std::shared_ptr<RVal> left)
{
    if (left->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(left)->getData());
        return RValConstFactory::createNumberConstSharedPtr(!left);
    }
}