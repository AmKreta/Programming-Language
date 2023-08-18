#include <operations/mathemeticalOperation.hpp>
#include <evaluable/rValueConstFactory.hpp>
#include <utility/conversionFunctions.hpp>

// --------------------- binary operations ----------------------------
std::shared_ptr<RVal> MathemeticalExpression::add(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = std::dynamic_pointer_cast<NumberConst>(left)->getData();
        auto rightNum = std::dynamic_pointer_cast<NumberConst>(right)->getData();
        return RValConstFactory::createNumberConstSharedPtr(leftNum + rightNum);
    }

    if (left->getType() == RVal::Type::STRING && right->getType() == RVal::Type::STRING)
    {
        auto leftStr = std::dynamic_pointer_cast<StringConst>(left)->getData();
        auto rightStr = std::dynamic_pointer_cast<StringConst>(right)->getData();
        return RValConstFactory::createStringConstSharedPtr(leftStr + rightStr);
    }
}

std::shared_ptr<RVal> MathemeticalExpression::subtract(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = std::dynamic_pointer_cast<NumberConst>(left)->getData();
        auto rightNum = std::dynamic_pointer_cast<NumberConst>(right)->getData();
        return RValConstFactory::createNumberConstSharedPtr(leftNum - rightNum);
    }
}

std::shared_ptr<RVal> MathemeticalExpression::divide(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = std::dynamic_pointer_cast<NumberConst>(left)->getData();
        auto rightNum = std::dynamic_pointer_cast<NumberConst>(right)->getData();
        return RValConstFactory::createNumberConstSharedPtr(leftNum / rightNum);
    }
}

std::shared_ptr<RVal> MathemeticalExpression::multiply(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = std::dynamic_pointer_cast<NumberConst>(left)->getData();
        auto rightNum = std::dynamic_pointer_cast<NumberConst>(right)->getData();
        return RValConstFactory::createNumberConstSharedPtr(leftNum * rightNum);
    }
}

std::shared_ptr<RVal> MathemeticalExpression::power(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = std::dynamic_pointer_cast<NumberConst>(left)->getData();
        auto rightNum = std::dynamic_pointer_cast<NumberConst>(right)->getData();
        return RValConstFactory::createNumberConstSharedPtr(std::pow(leftNum, rightNum));
    }
}

std::shared_ptr<RVal> MathemeticalExpression::modulus(std::shared_ptr<RVal> left, std::shared_ptr<RVal> right)
{
    if (left->getType() == RVal::Type::NUMBER && right->getType() == RVal::Type::NUMBER)
    {
        auto leftNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(left)->getData());
        auto rightNum = static_cast<int>(std::dynamic_pointer_cast<NumberConst>(right)->getData());
        return RValConstFactory::createNumberConstSharedPtr(leftNum % rightNum);
    }
}

//------------------------- unaryOperation --------------------------------
std::shared_ptr<RVal> MathemeticalExpression::Positive(std::shared_ptr<RVal> child)
{
    auto dataType = child->getType();
    if (dataType == RVal::Type::NUMBER)
        return child;
    if (dataType == RVal::Type::STRING)
    {
        auto numConst = ConversionFunctions::StringToNumber(child);
        return numConst;
    }
}

std::shared_ptr<RVal> MathemeticalExpression::Negative(std::shared_ptr<RVal> child)
{
    auto dataType = child->getType();
    if (dataType == RVal::Type::NUMBER)
    {
        auto numConst = std::dynamic_pointer_cast<NumberConst>(child);
        numConst->setData(-1 * numConst->getData());
        return numConst;
    }

    if (dataType == RVal::Type::STRING)
    {
        auto numConst = ConversionFunctions::StringToNumber(child);
        numConst->setData(-1 * numConst->getData());
        return numConst;
    }
}

// evaluate functions for unary , binary and ternary operations

// unaryOperation
std::shared_ptr<RVal> MathemeticalExpression::evaluate(Token::Type type, std::shared_ptr<RVal> child)
{
    // convert non number into number
    if (type == Token::Type::PLUS)
        return MathemeticalExpression::Positive(child);
    if (type == Token::Type::MINUS)
        return MathemeticalExpression::Negative(child);
}

// binary operations
std::shared_ptr<RVal> MathemeticalExpression::evaluate(std::shared_ptr<RVal> left, Token::Type op, std::shared_ptr<RVal> right)
{
    if (op == Token::Type::PLUS)
        return MathemeticalExpression::add(left, right);
    if (op == Token::Type::MINUS)
        return MathemeticalExpression::subtract(left, right);
    if (op == Token::Type::MULTIPLY)
        return MathemeticalExpression::multiply(left, right);
    if (op == Token::Type::DIVIDE)
        return MathemeticalExpression::divide(left, right);
    if (op == Token::Type::POWER)
        return MathemeticalExpression::power(left, right);
    if (op == Token::Type::MODULUS)
        return MathemeticalExpression::modulus(left, right);
}

// // tertiary operator
// std::shared_ptr<RVal> MathemeticalExpression::evaluate(std::shared_ptr<RVal> first, std::shared_ptr<RVal> second, std::shared_ptr<RVal> third)
// {
// }