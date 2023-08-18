#include <parser/parser.hpp>
#include <evaluable/binaryOperation.hpp>

std::shared_ptr<Evaluable> Parser::P2_mathemetical_multiplicativeExpression()
{
    std::shared_ptr<Evaluable> res = this->P1_factor();
    while (this->currentToken.getTokenType() == Token::Type::MULTIPLY || this->currentToken.getTokenType() == Token::Type::DIVIDE || this->currentToken.getTokenType() == Token::Type::POWER)
    {
        auto type = this->currentToken.getTokenType();
        this->eat(type);
        res = std::make_shared<BinaryOperation>(res, type, this->P1_factor());
    }
    return res;
} 

std::shared_ptr<Evaluable> Parser::P3_mathemetical_addativeExpression()
{
    std::shared_ptr<Evaluable> res = this->P2_mathemetical_multiplicativeExpression();
    while (this->currentToken.getTokenType() == Token::Type::PLUS || this->currentToken.getTokenType() == Token::Type::MINUS)
    {
        auto op = this->currentToken.getTokenType();
        this->eat(op);
        res = std::make_shared<BinaryOperation>(res, op, this->P2_mathemetical_multiplicativeExpression());
    }
    return res;
}