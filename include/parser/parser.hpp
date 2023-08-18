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

// p indicates priority level
class Parser
{
private:
    Lexer lexer;
    Token currentToken;
    Token previousToken;
    void eat(Token::Type);

public:
    Parser(Lexer);
    std::shared_ptr<Evaluable> P1_factor();                                // +i, -i, ++i, --i, i++, i--, fn(), !i, rVal etc , logical not, bitwise not
    std::shared_ptr<Evaluable> P2_mathemetical_multiplicativeExpression(); //*,**,/,%
    std::shared_ptr<Evaluable> P3_mathemetical_addativeExpression();       //, +,-
    std::shared_ptr<Evaluable> P4_bitwise_shiftExpression();               //<<, >>
    std::shared_ptr<Evaluable> p5_relational_gt_lt_expression();           // >,<,>=,<=
    std::shared_ptr<Evaluable> p6_relational_equality_expression();        // ==, !=
    std::shared_ptr<Evaluable> p7_bitwise_expression();                    // and, or, xor
    std::shared_ptr<Evaluable> p8_logical_expression();                    // &&, ||
    std::shared_ptr<Evaluable> p9_ternary();                               //?:
    std::shared_ptr<Evaluable> p10_assignment();                           // =, +=, -=, *=, /=, **=, %=, <<=, >>=, &=, |=
    std::shared_ptr<Evaluable> p11_expression();                           // whole expression
    std::shared_ptr<Evaluable> parse();
};