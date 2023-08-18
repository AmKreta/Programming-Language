#include <operations/relationalOperation.hpp>
#include <evaluable/rValueConstFactory.hpp>

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
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = std::dynamic_pointer_cast<NumberConst>(left)->getData();
        auto rightNum = std::dynamic_pointer_cast<NumberConst>(right)->getData();
        return RValConstFactory::createBooleanConstSharedPtr(leftNum == rightNum);
    }
}

std::shared_ptr<RVal> RelationalExpression::notEqualTo(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = std::dynamic_pointer_cast<NumberConst>(left)->getData();
        auto rightNum = std::dynamic_pointer_cast<NumberConst>(right)->getData();
        return RValConstFactory::createBooleanConstSharedPtr(leftNum != rightNum);
    }
}

std::shared_ptr<RVal> RelationalExpression::lessThan(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = std::dynamic_pointer_cast<NumberConst>(left)->getData();
        auto rightNum = std::dynamic_pointer_cast<NumberConst>(right)->getData();
        return RValConstFactory::createBooleanConstSharedPtr(leftNum < rightNum);
    }
}

std::shared_ptr<RVal> RelationalExpression::lessThanEqualTo(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = std::dynamic_pointer_cast<NumberConst>(left)->getData();
        auto rightNum = std::dynamic_pointer_cast<NumberConst>(right)->getData();
        return RValConstFactory::createBooleanConstSharedPtr(leftNum <= rightNum);
    }
}

std::shared_ptr<RVal> RelationalExpression::greaterThan(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = std::dynamic_pointer_cast<NumberConst>(left)->getData();
        auto rightNum = std::dynamic_pointer_cast<NumberConst>(right)->getData();
        return RValConstFactory::createBooleanConstSharedPtr(leftNum > rightNum);
    }
}

std::shared_ptr<RVal> RelationalExpression::greaterThanEqualTo(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = std::dynamic_pointer_cast<NumberConst>(left)->getData();
        auto rightNum = std::dynamic_pointer_cast<NumberConst>(right)->getData();
        return RValConstFactory::createBooleanConstSharedPtr(leftNum >= rightNum);
    }
}