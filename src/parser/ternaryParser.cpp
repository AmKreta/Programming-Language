#include <parser/parser.hpp>
#include <evaluable/conditionalOperator.hpp>

std::shared_ptr<Evaluable> Parser::p9_ternary()
{
    auto condition = this->p8_logical_expression();
    while (this->currentToken.getTokenType() == Token::Type::QUESTION)
    {
        this->eat(Token::Type::QUESTION);
        auto _if = this->p8_logical_expression();
        this->eat(Token::Type::COLON);
        auto _else = this->p8_logical_expression();
        condition = std::make_shared<ConditionalOperation>(condition, _if, _else);
    }
    return condition;
}