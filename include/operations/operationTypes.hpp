#pragma once

#include <token/token.hpp>
#include <unordered_set>

class operatorTypes
{
public:
    static auto inline mathemeticalOperators = std::unordered_set<Token::Type>{
        Token::Type::PLUS,
        Token::Type::MINUS,
        Token::Type::MULTIPLY,
        Token::Type::DIVIDE,
        Token::Type::POWER, // also add pre-post increment-decrement
    };

    static auto inline relationalEqualityCheckOperators = std::unordered_set<Token::Type>{
        Token::Type::EQUAL_TO,
        Token::Type::NOT_EQUAL_TO};

    static auto inline relationalComparisionOperators = std::unordered_set<Token::Type>{
        Token::Type::GREATER_THAN,
        Token::Type::GREATER_THAN_EQUAL_TO,
        Token::Type::LESS_THAN,
        Token::Type::LESS_THAN_EQUAL_TO};

    static auto inline logicalOperators = std::unordered_set<Token::Type>{
        Token::Type::LOGICAL_AND,
        Token::Type::LOGICAL_OR,
        // Token::Type::LOGICAL_NOT , handled as unary operator
    };

    static auto inline bitwiseOperators = std::unordered_set<Token::Type>{
        Token::Type::BITWISE_AND,
        // Token::Type::BITWISE_NOT, handled as unary operator
        Token::Type::BITWISE_OR,
        Token::Type::BITWISE_XOR};

    static auto inline bitwiseShiftOperators = std::unordered_set<Token::Type>{
        Token::Type::BITWISE_L_SHIFT,
        Token::Type::BITWISE_R_SHIFT};
};