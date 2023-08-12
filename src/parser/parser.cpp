#include <parser/parser.hpp>
#include <evaluable/numberConst.hpp>
#include <evaluable/unaryOperation.hpp>
#include <evaluable/binaryOperation.hpp>
#include <exception/exceptionFactory.hpp>

Parser::Parser(Lexer lexer) : lexer(lexer), currentToken(this->lexer.getNextToken()) {}

void Parser::eat(Token::Type type)
{
    // std::cout << "before eat>>" << this->currentToken << ", sent type -> " << Token::getTokenTypeStr(type) << std::endl;
    if (this->currentToken.getTokenType() == type)
        this->currentToken = this->lexer.getNextToken();
    else
    {
        throw ExceptionFactory::create(this->lexer.getLine(), ":", this->lexer.getColumn(), " -> ", "expected", this->currentToken.getTokenTypeString(), "got", Token::getTokenTypeString(type));
    }
    // std::cout << "after eat>>" << this->currentToken << ", sent type -> " << Token::getTokenTypeStr(type) << std::endl;
}

std::shared_ptr<Evaluable> Parser::factor()
{
    auto currentTokenType = this->currentToken.getTokenType();

    if(currentTokenType == Token::Type::NUMBER_CONST)
    {
        auto res = std::make_shared<NumberConst>(stod(this->currentToken.getTokenValue()));
        this->eat(Token::Type::NUMBER_CONST);
        return res;
    }

    if(currentTokenType == Token::Type::PLUS)
    {
        this->eat(Token::Type::PLUS);
        return std::make_shared<UnaryOperation>(Token::Type::PLUS, this->factor());
    }

    if(currentTokenType == Token::Type::MINUS)
    {
        this->eat(Token::Type::MINUS);
        return std::make_shared<UnaryOperation>(Token::Type::MINUS, this->factor());
    }

    if(currentTokenType == Token::Type::L_PAREN)
    {
        this->eat(Token::Type::L_PAREN);
        auto res = this->expr();
        this->eat(Token::Type::R_PAREN);
        return res;
    }
}

std::shared_ptr<Evaluable> Parser::term()
{
    std::shared_ptr<Evaluable> res = this->factor();
    auto currentTokenType = this->currentToken.getTokenType();
    while (currentTokenType == Token::Type::MULTIPLY || currentTokenType == Token::Type::DIVIDE || currentTokenType == Token::Type::POWER)
    {
        this->eat(currentTokenType);
        res = std::make_shared<BinaryOperation>(res, currentTokenType, this->factor());
    }
    return res;
}

std::shared_ptr<Evaluable> Parser::expr()
{
    std::shared_ptr<Evaluable> res = this->term();
    auto currentTokenType = this->currentToken.getTokenType();
    while (currentTokenType == Token::Type::PLUS || currentTokenType == Token::Type::MINUS)
    {
        this->eat(currentTokenType);
        res = std::make_shared<BinaryOperation>(res, currentTokenType, this->term());
    }
    return res;
}

std::shared_ptr<Evaluable> Parser::parse()
{
    return this->expr();
}