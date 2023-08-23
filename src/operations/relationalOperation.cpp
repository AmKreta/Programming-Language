#include <operations/relationalOperation.hpp>
#include <evaluable/rValueConstFactory.hpp>
#include <exception/exceptionFactory.hpp>

std::shared_ptr<RVal> RelationalExpression::evaluate(std::shared_ptr<RVal> left, Token::Type op, std::shared_ptr<RVal> right)
{
    if (op == Token::Type::EQUAL_TO)
        return RelationalExpression::equalTo(left, right);
    if (op == Token::Type::NOT_EQUAL_TO)
        return RelationalExpression::notEqualTo(left, right);
    if (op == Token::Type::GREATER_THAN)
        return RelationalExpression::greaterThan(left, right);
    if (op == Token::Type::LESS_THAN)
        return RelationalExpression::lessThan(left, right);
    if (op == Token::Type::LESS_THAN_EQUAL_TO)
        return RelationalExpression::lessThanEqualTo(left, right);
    if (op == Token::Type::GREATER_THAN_EQUAL_TO)
        return RelationalExpression::greaterThanEqualTo(left, right);
}

std::shared_ptr<RVal> RelationalExpression::equalTo(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    auto typeLeft = left->getType(), typeRight = right->getType();
    if (typeLeft != typeRight)
        return RValConstFactory::createBooleanConstSharedPtr(false);

    if (typeLeft == RVal::Type::NUMBER)
    {
        auto leftNum = std::dynamic_pointer_cast<NumberConst>(left)->getData();
        auto rightNum = std::dynamic_pointer_cast<NumberConst>(right)->getData();
        return RValConstFactory::createBooleanConstSharedPtr(leftNum == rightNum);
    }

    if (typeLeft == RVal::Type::STRING)
    {
        auto &leftStr = std::dynamic_pointer_cast<StringConst>(left)->getData();
        auto &rightStr = std::dynamic_pointer_cast<StringConst>(right)->getData();
        return RValConstFactory::createBooleanConstSharedPtr(leftStr == rightStr);
    }

    if (typeLeft == RVal::Type::BOOLEAN)
    {
        auto leftBool = std::dynamic_pointer_cast<BooleanConst>(left)->getData();
        auto rightBool = std::dynamic_pointer_cast<BooleanConst>(right)->getData();
        return RValConstFactory::createBooleanConstSharedPtr(leftBool == rightBool);
    }

    return RValConstFactory::createBooleanConstSharedPtr(left == right);
}

std::shared_ptr<RVal> RelationalExpression::notEqualTo(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    if (left->getType() != right->getType())
        return RValConstFactory::createBooleanConstSharedPtr(true);

    if (left->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = std::dynamic_pointer_cast<NumberConst>(left)->getData();
        auto rightNum = std::dynamic_pointer_cast<NumberConst>(right)->getData();
        return RValConstFactory::createBooleanConstSharedPtr(leftNum != rightNum);
    }

    if (left->getType() == RVal::Type::STRING)
    {
        auto &leftStr = std::dynamic_pointer_cast<StringConst>(left)->getData();
        auto &rightStr = std::dynamic_pointer_cast<StringConst>(right)->getData();
        return RValConstFactory::createBooleanConstSharedPtr(leftStr != rightStr);
    }

    if (left->getType() == RVal::Type::BOOLEAN)
    {
        auto leftBool = std::dynamic_pointer_cast<BooleanConst>(left)->getData();
        auto rightBool = std::dynamic_pointer_cast<BooleanConst>(right)->getData();
        return RValConstFactory::createBooleanConstSharedPtr(leftBool != rightBool);
    }

    return RValConstFactory::createBooleanConstSharedPtr(left != right);
}

std::shared_ptr<RVal> RelationalExpression::lessThan(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    auto typeLeft = left->getType(), typeRight = right->getType();
    if (typeLeft != typeRight)
        throw ExceptionFactory::create("can compare ", left->getTypeString(), "and", right->getTypeString());

    if (typeLeft == RVal::Type::NUMBER)
    {
        auto leftNum = std::dynamic_pointer_cast<NumberConst>(left)->getData();
        auto rightNum = std::dynamic_pointer_cast<NumberConst>(right)->getData();
        return RValConstFactory::createBooleanConstSharedPtr(leftNum < rightNum);
    }

    if (typeLeft == RVal::Type::STRING)
    {
        auto &leftStr = std::dynamic_pointer_cast<StringConst>(left)->getData();
        auto &rightStr = std::dynamic_pointer_cast<StringConst>(right)->getData();
        return RValConstFactory::createBooleanConstSharedPtr(leftStr < rightStr);
    }

    throw ExceptionFactory::create("can compare (<) ", left->getTypeString(), "and", right->getTypeString());
}

std::shared_ptr<RVal> RelationalExpression::lessThanEqualTo(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    auto typeLeft = left->getType(), typeRight = right->getType();
    if (typeLeft != typeRight)
        throw ExceptionFactory::create("can compare ", left->getTypeString(), "and", right->getTypeString());

    if (typeLeft == RVal::Type::NUMBER)
    {
        auto leftNum = std::dynamic_pointer_cast<NumberConst>(left)->getData();
        auto rightNum = std::dynamic_pointer_cast<NumberConst>(right)->getData();
        return RValConstFactory::createBooleanConstSharedPtr(leftNum <= rightNum);
    }

    if (typeLeft == RVal::Type::STRING)
    {
        auto &leftStr = std::dynamic_pointer_cast<StringConst>(left)->getData();
        auto &rightStr = std::dynamic_pointer_cast<StringConst>(right)->getData();
        return RValConstFactory::createBooleanConstSharedPtr(leftStr <= rightStr);
    }

    throw ExceptionFactory::create("can compare (<=", left->getTypeString(), "and", right->getTypeString());
}

std::shared_ptr<RVal> RelationalExpression::greaterThan(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    auto typeLeft = left->getType(), typeRight = right->getType();
    if (typeLeft != typeRight)
        throw ExceptionFactory::create("can compare ", left->getTypeString(), "and", right->getTypeString());

    if (typeLeft == RVal::Type::NUMBER)
    {
        auto leftNum = std::dynamic_pointer_cast<NumberConst>(left)->getData();
        auto rightNum = std::dynamic_pointer_cast<NumberConst>(right)->getData();
        return RValConstFactory::createBooleanConstSharedPtr(leftNum > rightNum);
    }

    if (typeLeft == RVal::Type::STRING)
    {
        auto &leftStr = std::dynamic_pointer_cast<StringConst>(left)->getData();
        auto &rightStr = std::dynamic_pointer_cast<StringConst>(right)->getData();
        return RValConstFactory::createBooleanConstSharedPtr(leftStr > rightStr);
    }

    throw ExceptionFactory::create("can compare (>)", left->getTypeString(), "and", right->getTypeString());
}

std::shared_ptr<RVal> RelationalExpression::greaterThanEqualTo(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    auto typeLeft = left->getType(), typeRight = right->getType();
    if (typeLeft != typeRight)
        throw ExceptionFactory::create("can compare ", left->getTypeString(), "and", right->getTypeString());

    if (typeLeft == RVal::Type::NUMBER)
    {
        auto leftNum = std::dynamic_pointer_cast<NumberConst>(left)->getData();
        auto rightNum = std::dynamic_pointer_cast<NumberConst>(right)->getData();
        return RValConstFactory::createBooleanConstSharedPtr(leftNum >= rightNum);
    }

    if (typeLeft == RVal::Type::STRING)
    {
        auto &leftStr = std::dynamic_pointer_cast<StringConst>(left)->getData();
        auto &rightStr = std::dynamic_pointer_cast<StringConst>(right)->getData();
        return RValConstFactory::createBooleanConstSharedPtr(leftStr >= rightStr);
    }

    throw ExceptionFactory::create("can compare (>=)", left->getTypeString(), "and", right->getTypeString());
}