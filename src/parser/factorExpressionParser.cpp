#include <parser/parser.hpp>
#include <evaluable/rValueConstFactory.hpp>
#include <evaluable/unaryOperation.hpp>
#include <evaluable/arrayAst.hpp>
#include <evaluable/mapAst.hpp>
#include <evaluable/rValConst.hpp>
#include <evaluable/variable.hpp>
#include <evaluable/indexing.hpp>
#include <evaluable/dotOperator.hpp>
#include <evaluable/functionCall.hpp>
#include <exception/exceptionFactory.hpp>
#include <evaluable/new.hpp>

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

    // boolean true
    if (this->currentToken.getTokenType() == Token::Type::TRUE)
    {
        this->eat(Token::Type::TRUE);
        return RValConstFactory::createBooleanConstSharedPtr(true);
    }

    // boolean false
    if (this->currentToken.getTokenType() == Token::Type::FALSE)
    {
        this->eat(Token::Type::FALSE);
        return RValConstFactory::createBooleanConstSharedPtr(false);
    }

    // logical not
    if (this->currentToken.getTokenType() == Token::Type::LOGICAL_NOT)
    {
        this->eat(Token::Type::LOGICAL_NOT);
        auto res = this->p11_expression();
        return std::make_shared<UnaryOperation>(Token::Type::LOGICAL_NOT, res);
    }

    // bitwise not
    if (this->currentToken.getTokenType() == Token::Type::BITWISE_NOT)
    {
        this->eat(Token::Type::BITWISE_NOT);
        auto res = this->p11_expression();
        return std::make_shared<UnaryOperation>(Token::Type::BITWISE_NOT, res);
    }

    // bitwise l shift
    if (this->currentToken.getTokenType() == Token::Type::BITWISE_L_SHIFT)
    {
        this->eat(Token::Type::BITWISE_L_SHIFT);
        auto res = this->p11_expression();
        return std::make_shared<UnaryOperation>(Token::Type::BITWISE_L_SHIFT, res);
    }

    // bitwise r shift
    if (this->currentToken.getTokenType() == Token::Type::BITWISE_R_SHIFT)
    {
        this->eat(Token::Type::BITWISE_R_SHIFT);
        auto res = this->p11_expression();
        return std::make_shared<UnaryOperation>(Token::Type::BITWISE_R_SHIFT, res);
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
        // [ (p11_expression() (, p11_expression())*)]
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
        if (this->currentToken.getTokenType() == Token::Type::L_BRACKET)
            return this->indexingOrFunctionCallOrDot(std::make_shared<ArrayAst>(arrAst));
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
        if (this->currentToken.getTokenType() == Token::Type::L_BRACKET)
            return this->indexingOrFunctionCallOrDot(std::make_shared<MapAst>(mapAst));
        return std::make_shared<MapAst>(mapAst);
    }

    // null
    if (this->currentToken.getTokenType() == Token::Type::Null)
    {
        this->eat(Token::Type::Null);
        return RValConstFactory::createNullConstSharedPtr();
    }

    // undefined
    if (this->currentToken.getTokenType() == Token::Type::UNDEFINED)
    {
        this->eat(Token::Type::UNDEFINED);
        return RValConstFactory::createUndefinedConstSharedPtr();
    }

    // variable
    if (this->currentToken.getTokenType() == Token::Type::ID)
    {
        auto name = this->currentToken.getTokenValue();
        this->eat(Token::Type::ID);
        auto var = std::make_shared<Variable>(name);
        if (this->currentToken.getTokenType() == Token::Type::L_BRACKET || this->currentToken.getTokenType() == Token::Type::L_PAREN)
            return this->indexingOrFunctionCallOrDot(var);
        return var;
    }

    if (this->currentToken.getTokenType() == Token::Type::FUNCTION)
        return this->function(true);

    if (this->currentToken.getTokenType() == Token::Type::NEW)
        return this->parseNew();

    if (this->currentToken.getTokenType() == Token::Type::CLASS)
    {
        throw ExceptionFactory::create("Class decleration cant be assigned");
    }

    throw ExceptionFactory::create("misplaced or unsupported token", this->currentToken.getTokenTypeString(), this->currentToken.getTokenValue());
    // remaining
    //  ',' , ++, --,
}

std::shared_ptr<Evaluable> Parser::indexingOrFunctionCallOrDot(std::shared_ptr<Evaluable> expr)
{
    auto res = expr;
    while (this->currentToken.getTokenType() == Token::Type::L_BRACKET || this->currentToken.getTokenType() == Token::Type::L_PAREN || this->currentToken.getTokenType() == Token::Type::DOT)
    {
        if (this->currentToken.getTokenType() == Token::Type::L_BRACKET)
        {
            this->eat(Token::Type::L_BRACKET);
            res = std::make_shared<Indexing>(res, this->p11_expression());
            this->eat(Token::Type::R_BRACKET);
        }
        else if (this->currentToken.getTokenType() == Token::Type::DOT)
        {
            this->eat(Token::Type::DOT);
            res = std::make_shared<DotOperator>(res, this->p11_expression());
        }
        else
        {
            this->eat(Token::Type::L_PAREN);
            std::vector<std::shared_ptr<Evaluable>> args;
            if (this->currentToken.getTokenType() != Token::Type::R_PAREN)
            {
                args.push_back(this->p11_expression());
                while (this->currentToken.getTokenType() == Token::Type::COMMA)
                {
                    this->eat(Token::Type::COMMA);
                    args.push_back(this->p11_expression());
                }
            }
            this->eat(Token::Type::R_PAREN);
            res = std::make_shared<FunctionCall>(res, args);
        }
    }
    return res;
}

std::shared_ptr<New> Parser::parseNew()
{
    this->eat(Token::Type::NEW);
    auto className = this->currentToken.getTokenValue();
    this->eat(Token::Type::ID);
    this->eat(Token::Type::L_PAREN);
    std::vector<std::shared_ptr<Evaluable>> args{};
    if (this->currentToken.getTokenType() != Token::Type::R_PAREN)
    {
        args.push_back(this->p11_expression());
        while (this->currentToken.getTokenType() == Token::Type::COMMA)
        {
            this->eat(Token::Type::COMMA);
            args.push_back(this->p11_expression());
        }
    }
    this->eat(Token::Type::R_PAREN);
    return std::make_shared<New>(className, args);
}