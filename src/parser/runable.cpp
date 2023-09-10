#include <parser/parser.hpp>
#include <evaluable/rValueConstFactory.hpp>

// varDecl : (let | const) Id ( = expression)? ( , Id ( = expression ) ?)*
std::shared_ptr<VarDecleration> Parser::varDecleration()
{
    this->eat(this->currentToken.getTokenType()); // let | const
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

// if-else : if RParen expression LParen ({compoundStatement}? | statement semicolon?) (else ({compoundStatement}? | statement semicolon?))?
std::shared_ptr<IfElse> Parser::ifElse()
{
    this->eat(Token::Type::IF);
    this->eat(Token::Type::L_PAREN);
    auto condition = this->p11_expression();
    this->eat(Token::Type::R_PAREN);

    std::shared_ptr<CompoundStatement> ifBlockStatements;

    if (this->currentToken.getTokenType() == Token::Type::L_BRACES)
    {
        // ie if(){}
        this->eat(Token::Type::L_BRACES);
        ifBlockStatements = this->compoundStatement(false, Token::Type::R_BRACES);
        this->eat(Token::Type::R_BRACES);
    }
    else
        ifBlockStatements = this->compoundStatement(true);

    std::shared_ptr<CompoundStatement> elseBlockStatements;
    if (this->currentToken.getTokenType() == Token::Type::ELSE)
    {
        // ie else block exists
        this->eat(Token::Type::ELSE);
        if (this->currentToken.getTokenType() == Token::Type::L_BRACES)
        {
            // ie if(){}
            this->eat(Token::Type::L_BRACES);
            elseBlockStatements = this->compoundStatement(false, Token::Type::R_BRACES);
            this->eat(Token::Type::R_BRACES);
        }
        else
            elseBlockStatements = this->compoundStatement(true);
    }

    if (!elseBlockStatements)
        elseBlockStatements = std::make_shared<CompoundStatement>(std::vector<std::shared_ptr<Statement>>());

    return std::make_shared<IfElse>(condition, ifBlockStatements, elseBlockStatements);
}

// statement : if-else | var decl | loop
std::shared_ptr<Statement> Parser::statement()
{
    if (this->currentToken.getTokenType() == Token::Type::LET || this->currentToken.getTokenType() == Token::Type::CONST)
    {
        auto res = this->varDecleration();
        this->eat(Token::Type::SEMI_COLON);
        return res;
    }

    if (this->currentToken.getTokenType() == Token::Type::IF)
        return this->ifElse();

    if (this->currentToken.getTokenType() == Token::Type::FOR)
        return this->forLoop();

    if (this->currentToken.getTokenType() == Token::Type::WHILE)
        return this->whileLoop();

    if (this->currentToken.getTokenType() == Token::Type::FUNCTION)
    {
        auto res = std::make_shared<ExpressionStatement>(this->function());
        return res;
    }

    if(this->currentToken.getTokenType() == Token::Type::RETURN){
        this->eat(Token::Type::RETURN);
        auto ret = std::make_shared<Return>(this->p11_expression());
        this->eat(Token::Type::SEMI_COLON);
        return ret;
    }

    if(this->currentToken.getTokenType() == Token::Type::PRINT){
        auto res = this->print();
        this->eat(Token::Type::SEMI_COLON);
        return res;
    }

    auto res = std::make_shared<ExpressionStatement>(this->p11_expression());
    this->eat(Token::Type::SEMI_COLON);
    return res;
}

// compoundStatement : statement (semicolon statement)* semicolon?
std::shared_ptr<CompoundStatement> Parser::compoundStatement(bool readOnlyOneStatement, Token::Type delimiter)
{
    std::vector<std::shared_ptr<Statement>> statementList;

    if (readOnlyOneStatement)
    {
        statementList.push_back(this->statement());
        return std::make_shared<CompoundStatement>(statementList);
    }

    while (this->currentToken.getTokenType() != delimiter)
    {
        statementList.push_back(this->statement());
    }

    return std::make_shared<CompoundStatement>(statementList);
}

// program : compoundStatement*
std::shared_ptr<Program> Parser::program()
{
    return std::make_shared<Program>(this->compoundStatement());
}
