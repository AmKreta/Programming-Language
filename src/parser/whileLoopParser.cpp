#include <parser/parser.hpp>
#include <evaluable/rValueConstFactory.hpp>

std::shared_ptr<WhileLoop> Parser::whileLoop()
{
    this->eat(Token::Type::WHILE);
    this->eat(Token::Type::L_PAREN);
    std::shared_ptr<Evaluable> condition = RValConstFactory::createBooleanConstSharedPtr(true);

    if (this->currentToken.getTokenType() == Token::Type::R_PAREN)
        this->eat(Token::Type::R_PAREN); // no condition
    else
    {
        condition = this->p11_expression();
        this->eat(Token::Type::R_PAREN);
    }

    std::shared_ptr<CompoundStatement> compoundStatement;
    if (this->currentToken.getTokenType() == Token::Type::L_BRACES)
    {
        this->eat(Token::Type::L_BRACES);
        compoundStatement = this->compoundStatement(false, Token::Type::R_BRACES);
        this->eat(Token::Type::R_BRACES);
    }
    else
        compoundStatement = this->compoundStatement(true);

    return std::make_shared<WhileLoop>(condition, compoundStatement);
}