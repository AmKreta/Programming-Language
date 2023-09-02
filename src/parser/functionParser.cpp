#include<parser/parser.hpp>
#include<evaluable/variable.hpp>
#include<evaluable/rValueConstFactory.hpp>

std::shared_ptr<Evaluable> Parser::function(){
    this->eat(Token::Type::FUNCTION);
    
    auto name = "anonymous"; // if name is anonymous don't store in symbol table function symbol
    if(this->currentToken.getTokenType() == Token::Type::ID){
        auto name = this->currentToken.getTokenValue();
        this->eat(Token::Type::ID);
    }

    this->eat(Token::Type::L_PAREN);
    std::vector<std::pair<std::shared_ptr<Variable>, std::shared_ptr<Evaluable>>> params;
    while(this->currentToken.getTokenType()!=Token::Type::R_PAREN){
        auto var = std::make_shared<Variable>(this->currentToken.getTokenValue());
        std::__1::shared_ptr<Evaluable> defaultVal = RValConstFactory::createUndefinedConstSharedPtr();
        this->eat(Token::Type::ID);
        if(this->currentToken.getTokenType()==Token::Type::ASSIGNMENT){
            this->eat(Token::Type::ASSIGNMENT);
            defaultVal = this->p11_expression();
        }
        params.push_back(std::pair(var, defaultVal));
        if(this->currentToken.getTokenType()!=Token::Type::R_PAREN)
            this->eat(Token::Type::COMMA);
    }

    this->eat(Token::Type::L_BRACES);
    auto statementList = this->compoundStatement();
    this->eat(Token::Type::R_BRACES);

    
}