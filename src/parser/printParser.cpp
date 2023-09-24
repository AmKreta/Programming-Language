#include <parser/parser.hpp>

std::shared_ptr<Print> Parser::print(bool hasNewLine)
{
    if (hasNewLine)
        this->eat(Token::Type::PRINT_LN);
    else
        this->eat(Token::Type::PRINT);
    this->eat(Token::Type::L_PAREN);
    std::vector<std::shared_ptr<Evaluable>> args;
    if (this->currentToken.getTokenType() == Token::Type::R_PAREN)
    {
        return std::make_shared<Print>(args);
    }
    else
    {
        args.push_back(this->p11_expression());
        while (this->currentToken.getTokenType() == Token::Type::COMMA)
        {
            this->eat(Token::Type::COMMA);
            args.push_back(this->p11_expression());
        }
        this->eat(Token::Type::R_PAREN);
        return std::make_shared<Print>(args, hasNewLine);
    }
}