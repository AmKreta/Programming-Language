#include <operations/logicalOperation.hpp>
#include <evaluable/rValueConstFactory.hpp>

std::shared_ptr<RVal> LogicalExpression::evaluate(std::shared_ptr<RVal> left, Token::Type op, std::shared_ptr<RVal> right)
{
    if (op == Token::Type::LOGICAL_AND)
        return LogicalExpression::And(left, right);
    if (op == Token::Type::LOGICAL_OR)
        return LogicalExpression::Or(left, right);
}

std::shared_ptr<RVal> LogicalExpression::evaluate(Token::Type op, std::shared_ptr<RVal> rVal)
{
    if (op == Token::Type::LOGICAL_NOT)
        return LogicalExpression::Not(rVal);
}

std::shared_ptr<RVal> LogicalExpression::And(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    return RValConstFactory::createBooleanConstSharedPtr(left && right);
}

std::shared_ptr<RVal> LogicalExpression::Or(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    return RValConstFactory::createBooleanConstSharedPtr(left || right);
}

std::shared_ptr<RVal> LogicalExpression::Not(std::shared_ptr<RVal> val)
{
    return RValConstFactory::createBooleanConstSharedPtr(!val);
}