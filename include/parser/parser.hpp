#pragma once

#include <lexer/lexer.hpp>
#include <evaluable/evaluable.hpp>
#include <evaluable/indexing.hpp>
#include <evaluable/classDecleration.hpp>
#include <runable/varDecleration.hpp>
#include <runable/statement.hpp>
#include <runable/program.hpp>
#include <runable/ifElse.hpp>
#include <runable/compoundStatement.hpp>
#include <runable/expressionStatement.hpp>
#include <runable/forLoop.hpp>
#include <runable/whileLoop.hpp>
#include <runable/return.hpp>
#include <runable/print.hpp>

// grammer
// program : compoundStatement
// compoundStatement : (statement)*
// statement : ((varDecleration | function call ) SEMI_COLON) | (functionDecleration | if-else | class)

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
    std::shared_ptr<Print> print();
    std::shared_ptr<Evaluable> indexingOrFunctionCall(std::shared_ptr<Evaluable>);
    std::shared_ptr<Evaluable> function(bool isAnonymous = false);
    std::shared_ptr<ClassDecleration> classDecleration();
    std::shared_ptr<RVal> functionCall();
    std::shared_ptr<Evaluable> P1_factor();                                         // +i, -i, ++i, --i, i++, i--, fn(), !i, rVal etc , logical not, bitwise not
    std::shared_ptr<Evaluable> P2_mathemetical_multiplicativeExpression();          //*,**,/,%
    std::shared_ptr<Evaluable> P3_mathemetical_addativeExpression();                //, +,-
    std::shared_ptr<Evaluable> P4_bitwise_shiftExpression();                        //<<, >>
    std::shared_ptr<Evaluable> p5_relational_gt_lt_expression();                    // >,<,>=,<=
    std::shared_ptr<Evaluable> p6_relational_equality_expression();                 // ==, !=
    std::shared_ptr<Evaluable> p7_bitwise_expression();                             // and, or, xor
    std::shared_ptr<Evaluable> p8_logical_expression();                             // &&, ||
    std::shared_ptr<Evaluable> p9_ternary(std::shared_ptr<Evaluable> ev = nullptr); //?:
    std::shared_ptr<Evaluable> p10_assignment();                                    // =, +=, -=, *=, /=, **=, %=, <<=, >>=, &=, |=
    std::shared_ptr<Evaluable> p11_expression();                                    // whole expression
    std::shared_ptr<VarDecleration> varDecleration();
    std::shared_ptr<IfElse> ifElse();
    std::shared_ptr<ForLoop> forLoop();
    std::shared_ptr<WhileLoop> whileLoop();
    std::shared_ptr<Statement> statement();
    std::shared_ptr<CompoundStatement> compoundStatement(bool readOnlyOneStatement = false, Token::Type delimiter = Token::Type::END_OF_FILE);
    std::shared_ptr<Program> program();
    std::shared_ptr<Program> parse();
};