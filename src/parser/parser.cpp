#include <parser/parser.hpp>
#include <exception/exceptionFactory.hpp>

Parser::Parser(Lexer lexer) : lexer(lexer), currentToken(this->lexer.getNextToken()), previousToken(this->lexer.getCurrentToken()) {}

void Parser::eat(Token::Type type)
{
    // std::cout << "before eat>>   " << this->currentToken << ", sent type -> " << Token::getTokenTypeString(type) << std::endl;
    if (this->currentToken.getTokenType() == type)
        this->currentToken = this->lexer.getNextToken();
    else
    {
        throw ExceptionFactory::create(this->lexer.getLine(), ":", this->lexer.getColumn(), " -> ", "expected", Token::getTokenTypeString(type), "got", this->currentToken.getTokenTypeString());
    }
    // std::cout << "after eat>>   " << this->currentToken << ", sent type -> " << Token::getTokenTypeString(type) << std::endl << std::endl;
}

std::shared_ptr<Evaluable> Parser::parse()
{
    return this->p11_expression();
}
