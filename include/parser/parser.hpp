#pragma once

#include <lexer/lexer.hpp>
#include <evaluable/evaluable.hpp>

// grammer
// program : compoundStatement
// compoundStatement : (statement)*
// statement : ((varDecleration | assignment| function call | comparision) SEMI_COLON) | (functionDecleration | if-else | class)

// varDecleration : (let | const ) ID (= expr)? (, varDecleration)*
// assignment : Id = expression
// comparision : Id (== | <= | < | >= | > | != ) expression

// function : function id (params){compoundStatement (return expr ;)?}
// params: ID (= expr)? (, params)*

// if-else : ifBlock elseBlock?
// ifBlock : if(condition) statement {program}
// elseBlock : else (statement | {program} | ifBlock)

// class : class Id { constructorFn? functions*};

// factor : RValConst , + factor, - factor , LPAREN EXPR RPAREN, Variable, function call
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