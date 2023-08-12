#pragma once

#include <lexer/lexer.hpp>
#include <evaluable/evaluable.hpp>

// grammer

// factor : RValConst , + factor, - factor , LPAREN EXPR RPAREN
// term : factor (*|/ factor)*
// expr : term (+|- term)*

class Parser
{
private:
    Lexer lexer;
    Token currentToken;
    void eat(Token::Type);
public:
    Parser(Lexer);
    std::shared_ptr<Evaluable> factor();
    std::shared_ptr<Evaluable> term();
    std::shared_ptr<Evaluable> expr();
    std::shared_ptr<Evaluable> parse();
};