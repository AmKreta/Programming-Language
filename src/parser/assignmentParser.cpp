#include <parser/parser.hpp>
#include <evaluable/binaryOperation.hpp>
#include <evaluable/indexing.hpp>

// assignment will be treated as both expression and statement
// eg a = b = c = 10;
// here b = c = 10 is expression , let it be x
// a = x is statement
// so in runable->statement , eat id, =, then get expression
std::shared_ptr<Evaluable> Parser::p10_assignment()
{
    // auto res = this->p9_ternary();
    // while (this->currentToken.getTokenType() == Token::Type::ASSIGNMENT)
    // {
    //     this->eat(Token::Type::ASSIGNMENT);
    //     if (this->currentToken.getTokenType() == Token::Type::L_BRACKET)
    //     {
    //         // indexing
    //         this->eat(Token::Type::L_BRACKET);
    //         auto index = this->p11_expression();
    //         this->eat(Token::Type::R_BRACKET);
    //         res = std::make_shared<Indexing>(res, index);
    //     }
    //     res = std::make_shared<BinaryOperation>(res, Token::Type::ASSIGNMENT, this->p9_ternary());
    // }
    // return res;

    auto lhs = this->p9_ternary();
    if (this->currentToken.getTokenType() == Token::Type::ASSIGNMENT)
    {
        this->eat(Token::Type::ASSIGNMENT);
        auto rhs = this->p9_ternary();
        if (this->currentToken.getTokenType() == Token::Type::ASSIGNMENT)
        {
            this->eat(Token::Type::ASSIGNMENT);
            rhs = std::make_shared<BinaryOperation>(rhs, Token::Type::ASSIGNMENT, this->p10_assignment());
        }
        return std::make_shared<BinaryOperation>(lhs, Token::Type::ASSIGNMENT, rhs);
    }
    return lhs;
}