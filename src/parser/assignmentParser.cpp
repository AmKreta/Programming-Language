#include <parser/parser.hpp>
#include <evaluable/binaryOperation.hpp>

std::shared_ptr<Evaluable> Parser::p10_assignment()
{
    auto res = this->p9_ternary();
    while (this->currentToken.getTokenType() == Token::Type::ASSIGNMENT)
    {
        this->eat(Token::Type::ASSIGNMENT);
        res = std::make_shared<BinaryOperation>(res, Token::Type::ASSIGNMENT, this->p9_ternary());
    }
    return res;
}