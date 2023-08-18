#include <parser/parser.hpp>
#include <evaluable/binaryOperation.hpp>
#include <operations/operationTypes.hpp>

std::shared_ptr<Evaluable> Parser::p8_logical_expression()
{
    // handle logical not in factor
    auto res = this->p7_bitwise_expression();
    while (operatorTypes::logicalOperators.find(this->currentToken.getTokenType()) != operatorTypes::logicalOperators.end())
    {
        auto tokenType = this->currentToken.getTokenType();
        this->eat(tokenType);
        res = std::make_shared<BinaryOperation>(res, tokenType, this->p7_bitwise_expression());
    }
    return res;
}