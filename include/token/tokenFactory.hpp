#pragma once

#include <token/token.hpp>
#include <string>
#include <unordered_map>

class TokenFactory
{
private:
    static std::unordered_map<Token::Type, std::string> tokenTypeValMap;

public:
    static Token build(Token::Type);
    static Token build(Token::Type, std::string);
};