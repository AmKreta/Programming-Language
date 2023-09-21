#include <parser/parser.hpp>
#include <exception/exceptionFactory.hpp>
#include <evaluable/rValueConstFactory.hpp>

std::shared_ptr<ClassDecleration> Parser::classDecleration()
{
    this->eat(Token::Type::CLASS);
    auto name = this->currentToken.getTokenValue();
    this->eat(Token::Type::ID);
    this->eat(Token::Type::L_BRACES);
    std::unordered_map<std::string, std::shared_ptr<Function>> staticMembers;
    while (this->currentToken.getTokenType() == Token::Type::FUNCTION)
    {
        auto fn = this->function();
        auto function = std::dynamic_pointer_cast<Function>(fn);
        if (!function)
            throw ExceptionFactory::create("Expected a function");
        auto name = function->getName();
        staticMembers.insert(std::pair(name, function));
    }
    this->eat(Token::Type::R_BRACES);
    return std::make_shared<ClassDecleration>(name, staticMembers);
}