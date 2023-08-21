#include <parser/parser.hpp>
#include <evaluable/binaryOperation.hpp>

// assignment will be treated as both expression and statement
// eg a = b = c = 10;
// here b = c = 10 is expression , let it be x
// a = x is statement
// so in runable->statement , eat id, =, then get expression
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