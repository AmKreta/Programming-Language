#include <parser/parser.hpp>
#include <evaluable/rValueConstFactory.hpp>

std::shared_ptr<VarDecleration> Parser::varDecleration()
{
    this->eat(this->currentToken.getTokenType());
    std::vector<std::pair<std::string, std::shared_ptr<Evaluable>>> declerations;
    auto addVarDecl = [this, &declerations]()
    {
        auto name = this->currentToken.getTokenValue();
        this->eat(Token::Type::ID);
        std::shared_ptr<Evaluable> val = RValConstFactory::createUndefinedConstSharedPtr();
        if (this->currentToken.getTokenType() == Token::Type::ASSIGNMENT)
        {
            this->eat(Token::Type::ASSIGNMENT);
            val = this->p11_expression();
        }
        declerations.push_back(std::pair(name, val));
    };
    addVarDecl();
    while (this->currentToken.getTokenType() == Token::Type::COMMA)
    {
        this->eat(Token::Type::COMMA);
        addVarDecl();
    }
    return std::make_shared<VarDecleration>(declerations);
}

std::shared_ptr<Statement> Parser::statement()
{
    if (this->currentToken.getTokenType() == Token::Type::LET || this->currentToken.getTokenType() == Token::Type::CONST)
        return this->varDecleration();
}

std::shared_ptr<Program> Parser::program()
{
    std::vector<std::shared_ptr<Statement>> statementList;
    statementList.push_back(this->statement());
    while (this->currentToken.getTokenType() == Token::Type::SEMI_COLON)
    {
        this->eat(Token::Type::SEMI_COLON);
        statementList.push_back(this->statement());
    }
    return std::make_shared<Program>(statementList);
}
