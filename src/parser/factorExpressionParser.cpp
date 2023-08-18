#include <parser/parser.hpp>
#include <evaluable/rValueConstFactory.hpp>
#include <evaluable/unaryOperation.hpp>
#include <evaluable/arrayAst.hpp>
#include <evaluable/mapAst.hpp>



std::shared_ptr<Evaluable> Parser::P1_factor()
{
    // number
    if (this->currentToken.getTokenType() == Token::Type::NUMBER_CONST)
    {
        auto res = RValConstFactory::createNumberConstSharedPtr(stod(this->currentToken.getTokenValue()));
        this->eat(Token::Type::NUMBER_CONST);
        return res;
    }

    // string
    if (this->currentToken.getTokenType() == Token::Type::STRING_CONST)
    {
        auto res = RValConstFactory::createStringConstSharedPtr(this->currentToken.getTokenValue());
        this->eat(Token::Type::STRING_CONST);
        return res;
    }

    // positive
    if (this->currentToken.getTokenType() == Token::Type::PLUS)
    {
        this->eat(Token::Type::PLUS);
        return std::make_shared<UnaryOperation>(Token::Type::PLUS, this->P1_factor());
    }

    // negative
    if (this->currentToken.getTokenType() == Token::Type::MINUS)
    {
        this->eat(Token::Type::MINUS);
        return std::make_shared<UnaryOperation>(Token::Type::MINUS, this->P1_factor());
    }

    // ()
    if (this->currentToken.getTokenType() == Token::Type::L_PAREN)
    {
        this->eat(Token::Type::L_PAREN);
        auto res = p11_expression();
        this->eat(Token::Type::R_PAREN);
        return res;
    }

    // array and indexing
    if (this->currentToken.getTokenType() == Token::Type::L_BRACKET)
    {
        // [ (p10_expression() (, p10_expression())*)]
        this->eat(Token::Type::L_BRACKET);
        std::vector<std::shared_ptr<Evaluable>> arrAst;
        if (this->currentToken.getTokenType() == Token::Type::R_BRACKET)
        {
            // empty array
            this->eat(Token::Type::R_BRACKET);
            return std::make_shared<ArrayAst>(arrAst);
        }
        arrAst.push_back(p11_expression());
        while (this->currentToken.getTokenType() == Token::Type::COMMA)
        {
            this->eat(Token::Type::COMMA);
            arrAst.push_back(p11_expression());
        }
        this->eat(Token::Type::R_BRACKET);
        return std::make_shared<ArrayAst>(arrAst);
    }

    // object
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
            auto key = p11_expression();
            this->eat(Token::Type::COLON);
            auto val = p11_expression();
            mapAst.insert(std::pair(key, val));
        };
        addKeyValPair(); // adding first key, val pair
        while (this->currentToken.getTokenType() == Token::Type::COMMA)
        {
            this->eat(Token::Type::COMMA);
            addKeyValPair();
        }
        this->eat(Token::Type::R_BRACES);
        return std::make_shared<MapAst>(mapAst);
    }

    // remaining
    // !, ~ , ++, --, true, false, null
}