#include <parser/parser.hpp>
#include <evaluable/variable.hpp>
#include <evaluable/rValueConstFactory.hpp>

std::shared_ptr<Evaluable> Parser::function(bool isAnonymous)
{
    this->eat(Token::Type::FUNCTION);

    std::string name = "anonymous"; // if name is anonymous don't store in symbol table function symbol
    if (!isAnonymous)
    {
        name = this->currentToken.getTokenValue();
        this->eat(Token::Type::ID);
    }

    this->eat(Token::Type::L_PAREN);
    std::vector<std::pair<std::shared_ptr<Variable>, std::shared_ptr<Evaluable>>> params;
    while (this->currentToken.getTokenType() != Token::Type::R_PAREN)
    {
        auto var = std::make_shared<Variable>(this->currentToken.getTokenValue());
        std::__1::shared_ptr<Evaluable> defaultVal = RValConstFactory::createUndefinedConstSharedPtr();
        this->eat(Token::Type::ID);
        if (this->currentToken.getTokenType() == Token::Type::ASSIGNMENT)
        {
            this->eat(Token::Type::ASSIGNMENT);
            defaultVal = this->p11_expression();
        }
        params.push_back(std::pair(var, defaultVal));
        if (this->currentToken.getTokenType() != Token::Type::R_PAREN)
            this->eat(Token::Type::COMMA);
    }
    this->eat(Token::Type::R_PAREN);

    this->eat(Token::Type::L_BRACES);
    auto statementList = this->compoundStatement(false, Token::Type::R_BRACES);
    this->eat(Token::Type::R_BRACES);

    return std::make_shared<Function>(name, params, statementList);
}