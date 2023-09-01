#include <parser/parser.hpp>
#include <runable/expressionStatement.hpp>
#include <evaluable/rValueConstFactory.hpp>

std::shared_ptr<ForLoop> Parser::forLoop()
{
    this->eat(Token::Type::FOR);
    this->eat(Token::Type::L_PAREN);

    // initialization can be empty also
    std::vector<std::shared_ptr<Statement>> initializationStatement;
    while (this->currentToken.getTokenType() != Token::Type::SEMI_COLON)
    {
        // only comma separated var decl or initialization is allowed
        if (this->currentToken.getTokenType() == Token::Type::LET || this->currentToken.getTokenType() == Token::Type::CONST)
            initializationStatement.push_back(this->varDecleration());
        else
            initializationStatement.push_back(std::make_shared<ExpressionStatement>(this->p11_expression()));
        // statement, statement, statement;
        if (this->currentToken.getTokenType() != Token::Type::SEMI_COLON)
            this->eat(Token::Type::COMMA);
    }
    this->eat(Token::Type::SEMI_COLON);

    // condition can be empty also
    // if no condition, treat it as true
    std::__1::shared_ptr<Evaluable> condition = RValConstFactory::createBooleanConstSharedPtr(true);
    if (this->currentToken.getTokenType() != Token::Type::SEMI_COLON)
        condition = this->p11_expression();
    this->eat(Token::Type::SEMI_COLON);

    // update can be empty also
    std::vector<std::shared_ptr<Statement>> updateStatement;
    while (this->currentToken.getTokenType() != Token::Type::R_PAREN)
    {
        // ;update1, update2)
        updateStatement.push_back(std::make_shared<ExpressionStatement>(this->p11_expression()));
        if (this->currentToken.getTokenType() != Token::Type::R_PAREN)
            this->eat(Token::Type::COMMA);
    }
    this->eat(Token::Type::R_PAREN);

    // for loop block
    std::shared_ptr<CompoundStatement> compoundStatement;
    if (this->currentToken.getTokenType() == Token::Type::L_BRACES)
    {
        this->eat(Token::Type::L_BRACES);
        compoundStatement = this->compoundStatement(false, Token::Type::R_BRACES);
        this->eat(Token::Type::R_BRACES);
    }
    else
        compoundStatement = this->compoundStatement(true);

    auto initialization = std::make_shared<CompoundStatement>(initializationStatement);
    auto updation = std::make_shared<CompoundStatement>(updateStatement);

    return std::make_shared<ForLoop>(initialization, condition, updation, compoundStatement);
}