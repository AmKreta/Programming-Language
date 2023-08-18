#include <parser/parser.hpp>
#include <evaluable/binaryOperation.hpp>
#include <operations/operationTypes.hpp>

std::shared_ptr<Evaluable> Parser::p5_relational_gt_lt_expression()
{
    auto res = this->P4_bitwise_shiftExpression();
    while (operatorTypes::relationalComparisionOperators.find(this->currentToken.getTokenType()) != operatorTypes::relationalComparisionOperators.end())
    {
        auto tokenType = this->currentToken.getTokenType();
        this->eat(tokenType);
        res = std::make_shared<BinaryOperation>(res, tokenType, this->P4_bitwise_shiftExpression());
    }
    return res;
}

std::shared_ptr<Evaluable> Parser::p6_relational_equality_expression()
{
    auto res = this->p5_relational_gt_lt_expression();
    while (operatorTypes::relationalEqualityCheckOperators.find(this->currentToken.getTokenType()) != operatorTypes::relationalEqualityCheckOperators.end())
    {
        auto tokenType = this->currentToken.getTokenType();
        this->eat(tokenType);
        res = std::make_shared<BinaryOperation>(res, tokenType, this->p5_relational_gt_lt_expression());
    }
    return res;
}
