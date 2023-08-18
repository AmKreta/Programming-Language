#include <operations/logicalOperation.hpp>
#include <evaluable/rValueConstFactory.hpp>
#include <utility/conversionFunctions.hpp>

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
    auto leftBool = ConversionFunctions::RValToBool(left);
    auto rightBool = ConversionFunctions::RValToBool(right);
    return RValConstFactory::createBooleanConstSharedPtr(leftBool && rightBool);
}

std::shared_ptr<RVal> LogicalExpression::Or(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    auto leftBool = ConversionFunctions::RValToBool(left);
    auto rightBool = ConversionFunctions::RValToBool(right);
    return RValConstFactory::createBooleanConstSharedPtr(leftBool || rightBool);
}

std::shared_ptr<RVal> LogicalExpression::Not(std::shared_ptr<RVal> val)
{
    auto valBool = ConversionFunctions::RValToBool(val);
    return RValConstFactory::createBooleanConstSharedPtr(!valBool);
}