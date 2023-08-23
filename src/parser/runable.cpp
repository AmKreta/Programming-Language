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
        ifBlockStatements = this->compoundStatement();
        this->eat(Token::Type::R_BRACES);
    }
    else
        ifBlockStatements = this->compoundStatement();

    std::shared_ptr<CompoundStatement> elseBlockStatements;
    if (this->currentToken.getTokenType() == Token::Type::ELSE)
    {
        // ie else block exists
        this->eat(Token::Type::ELSE);
        if (this->currentToken.getTokenType() == Token::Type::L_BRACES)
        {
            // ie if(){}
            this->eat(Token::Type::L_BRACES);
            elseBlockStatements = this->compoundStatement();
            this->eat(Token::Type::R_BRACES);
        }
        else
            elseBlockStatements = this->compoundStatement();
    }

    return std::make_shared<IfElse>(condition, ifBlockStatements, elseBlockStatements);
}

// std::shared_ptr<Assignment> Parser::assignmentStatement(){
//     auto varName = this->currentToken.getTokenValue();
//     this->eat(Token::Type::ID);
//     this->eat(Token::Type::ASSIGNMENT);
//     auto expr = this->p11_expression();
//     return std::make_shared<Assignment>(std::make_shared<Variable>(varName), expr);
// }

// statement : if-else | var decl | loop
std::shared_ptr<Statement> Parser::statement()
{
    if (this->currentToken.getTokenType() == Token::Type::LET || this->currentToken.getTokenType() == Token::Type::CONST)
        return this->varDecleration();
    if (this->currentToken.getTokenType() == Token::Type::IF)
        return this->ifElse();
    return std::make_shared<ExpressionStatement>(this->p11_expression());
}

// compoundStatement : statement (semicolon statement)* semicolon?
std::shared_ptr<CompoundStatement> Parser::compoundStatement()
{
    std::vector<std::shared_ptr<Statement>> statementList;
    statementList.push_back(this->statement());
    while (this->currentToken.getTokenType() == Token::Type::SEMI_COLON)
    {
        this->eat(Token::Type::SEMI_COLON);
        // places where statement can end
        if (!(this->currentToken.getTokenType() == Token::Type::END_OF_FILE || this->currentToken.getTokenType() == Token::Type::R_BRACES || this->currentToken.getTokenType() == Token::Type::ELSE))
            statementList.push_back(this->statement());
    }
    return std::make_shared<CompoundStatement>(statementList);
}

// program : compoundStatement*
std::shared_ptr<Program> Parser::program()
{
    return std::make_shared<Program>(this->compoundStatement());
}
