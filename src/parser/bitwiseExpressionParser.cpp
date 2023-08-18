#include <parser/parser.hpp>
#include <evaluable/binaryOperation.hpp>
#include <operations/operationTypes.hpp>

std::shared_ptr<Evaluable> Parser::P4_bitwise_shiftExpression()
{
    auto res = this->P3_mathemetical_addativeExpression();
    while (operatorTypes::bitwiseShiftOperators.find(this->currentToken.getTokenType()) != operatorTypes::bitwiseShiftOperators.end())
    {
        auto tokenType = this->currentToken.getTokenType();
        this->eat(tokenType);
        res = std::make_shared<BinaryOperation>(res, tokenType, this->p6_relational_equality_expression());
    }
    return res;
}

std::shared_ptr<Evaluable> Parser::p7_bitwise_expression()
{
    // handle logical not in factor
    auto res = this->p6_relational_equality_expression();
    while (operatorTypes::bitwiseOperators.find(this->currentToken.getTokenType()) != operatorTypes::bitwiseOperators.end())
    {
        auto tokenType = this->currentToken.getTokenType();
        this->eat(tokenType);
        res = std::make_shared<BinaryOperation>(res, tokenType, this->p6_relational_equality_expression());
    }
    return res;
}