#include <parser/parser.hpp>
#include <evaluable/rValConst.hpp>
#include <evaluable/unaryOperation.hpp>
#include <evaluable/binaryOperation.hpp>
#include <exception/exceptionFactory.hpp>
#include <evaluable/rValueConstFactory.hpp>
#include <evaluable/arrayAst.hpp>
#include <evaluable/mapAst.hpp>

Parser::Parser(Lexer lexer) : lexer(lexer), currentToken(this->lexer.getNextToken()) {}

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

std::shared_ptr<Evaluable> Parser::factor()
{
    if (this->currentToken.getTokenType() == Token::Type::NUMBER_CONST)
    {
        auto res = RValConstFactory::createNumberConstSharedPtr(stod(this->currentToken.getTokenValue()));
        this->eat(Token::Type::NUMBER_CONST);
        return res;
    }

    if (this->currentToken.getTokenType() == Token::Type::STRING_CONST)
    {
        auto res = RValConstFactory::createStringConstSharedPtr(this->currentToken.getTokenValue());
        this->eat(Token::Type::STRING_CONST);
        return res;
    }

    if (this->currentToken.getTokenType() == Token::Type::PLUS)
    {
        this->eat(Token::Type::PLUS);
        return std::make_shared<UnaryOperation>(Token::Type::PLUS, this->factor());
    }

    if (this->currentToken.getTokenType() == Token::Type::MINUS)
    {
        this->eat(Token::Type::MINUS);
        return std::make_shared<UnaryOperation>(Token::Type::MINUS, this->factor());
    }

    if (this->currentToken.getTokenType() == Token::Type::L_PAREN)
    {
        this->eat(Token::Type::L_PAREN);
        auto res = this->expr();
        this->eat(Token::Type::R_PAREN);
        return res;
    }

    if (this->currentToken.getTokenType() == Token::Type::L_BRACKET)
    {
        // [ (expr (, expr)*)]
        this->eat(Token::Type::L_BRACKET);
        std::vector<std::shared_ptr<Evaluable>> arrAst;
        if (this->currentToken.getTokenType() == Token::Type::R_BRACKET)
        {
            // empty array
            this->eat(Token::Type::R_BRACKET);
            return std::make_shared<ArrayAst>(arrAst);
        }
        arrAst.push_back(this->expr());
        while (this->currentToken.getTokenType() == Token::Type::COMMA)
        {
            this->eat(Token::Type::COMMA);
            arrAst.push_back(this->expr());
        }
        this->eat(Token::Type::R_BRACKET);
        return std::make_shared<ArrayAst>(arrAst);
    }

    if (this->currentToken.getTokenType() == Token::Type::L_BRACES)
    {
        // maybe a map, maybe a block
        this->eat(Token::Type::L_BRACES);
        std::unordered_map<std::shared_ptr<Evaluable>, std::shared_ptr<Evaluable>> mapAst;

        if (this->currentToken.getTokenType() == Token::Type::R_BRACES)
        {
            // empty map
            this->eat(Token::Type::R_BRACES);
            return std::make_shared<MapAst>(mapAst);
        }
        auto addKeyValPair = [&mapAst, this]()
        {
            auto key = this->expr();
            this->eat(Token::Type::COLON);
            auto val = this->expr();
            mapAst.insert(std::pair(key, val));
        };
        addKeyValPair();  // adding first key, val pair
        while (this->currentToken.getTokenType() == Token::Type::COMMA)
        {
            this->eat(Token::Type::COMMA);
            addKeyValPair();
        }
        this->eat(Token::Type::R_BRACES);
        return std::make_shared<MapAst>(mapAst);
    }
}

std::shared_ptr<Evaluable> Parser::term()
{
    std::shared_ptr<Evaluable> res = this->factor();
    while (this->currentToken.getTokenType() == Token::Type::MULTIPLY || this->currentToken.getTokenType() == Token::Type::DIVIDE || this->currentToken.getTokenType() == Token::Type::POWER)
    {
        auto type = this->currentToken.getTokenType();
        this->eat(type);
        res = std::make_shared<BinaryOperation>(res, type, this->factor());
    }
    return res;
}

std::shared_ptr<Evaluable> Parser::expr()
{
    std::shared_ptr<Evaluable> res = this->term();
    while (this->currentToken.getTokenType() == Token::Type::PLUS || this->currentToken.getTokenType() == Token::Type::MINUS)
    {
        auto op = this->currentToken.getTokenType();
        this->eat(op);
        res = std::make_shared<BinaryOperation>(res, op, this->term());
    }
    return res;
}

std::shared_ptr<Evaluable> Parser::parse()
{
    return this->expr();
}