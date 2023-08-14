#pragma once

#include <rVal/rVal.hpp>
#include <token/token.hpp>

class MathemeticalExpression
{
private:
public:
    // unaryOperation
    static std::shared_ptr<RVal> evaluate(Token::Type, std::shared_ptr<RVal>);
    // binary operations
    static std::shared_ptr<RVal> evaluate(std::shared_ptr<RVal>, Token::Type, std::shared_ptr<RVal>);

    // binary operations
    static std::shared_ptr<RVal> add(std::shared_ptr<RVal>, std::shared_ptr<RVal>);
    static std::shared_ptr<RVal> subtract(std::shared_ptr<RVal>, std::shared_ptr<RVal>);
    static std::shared_ptr<RVal> divide(std::shared_ptr<RVal>, std::shared_ptr<RVal>);
    static std::shared_ptr<RVal> multiply(std::shared_ptr<RVal>, std::shared_ptr<RVal>);
    static std::shared_ptr<RVal> power(std::shared_ptr<RVal>, std::shared_ptr<RVal>);

    // unaryOperation
    static std::shared_ptr<RVal> Positive(std::shared_ptr<RVal>);
    static std::shared_ptr<RVal> Negative(std::shared_ptr<RVal>);
};
