#pragma once

#include <string>
#include <vector>
#include <iostream>

class Token
{
public:
    enum class Type : int
    {
        // var Decl
        LET = 0,
        CONST,

        // data types
        NUMBER,
        STRING,
        ARRAY,
        OBJECT,
        FUNCTION,
        INTERFACE,
        CLASS,
        TYPE,
        NILL, // null
        UNDEFINED,
        TRUE,
        FALSE,

        // comparision / relational operator
        LESS_THAN,
        GREATER_THAN,
        LESS_THAN_EQUAL_TO,
        GREATER_THAN_EQUAL_TO,
        EQUAL_TO,
        NOT_EQUAL_TO,

        // logical operator / boolean operator
        LOGICAL_AND,
        LOGICAL_OR,
        LOGICAL_NOT,

        // mathemetical operator
        PLUS,
        MINUS,
        DIVIDE,
        MULTIPLY,
        POWER,
        MODULUS,

        // BITWISE operator
        BITWISE_AND,
        BITWISE_OR,
        BITWISE_NOT,
        BITWISE_XOR,
        BITWISE_L_SHIFT,
        BITWISE_R_SHIFT,

        // assignment
        ASSIGNMENT,

        // symbols
        COMMA,
        COLON,
        SEMI_COLON,
        L_PAREN,
        R_PAREN,
        L_BRACKET,
        R_BRACKET,
        L_BRACES,
        R_BRACES,

        ID, // variables

        // R_VALUES
        NUMBER_CONST,
        STRING_CONST,

        // loops
        FOR,
        WHILE,
        DO,

        //CONDITIONAL
        IF,
        ELIF,
        ELSE,
        QUESTION,

        // string
        SINGLE_QUOTE,
        DOUBLE_QUOTE,
        BACK_TICK,
                
        // return
        RETURN,
        END_OF_FILE,
        START_OF_FILE
    };

    static std::vector<std::string> TypeStr;

private:
    Token::Type type;
    std::string value;
    Token(Token::Type, std::string);
public:
    Token::Type getTokenType();
    std::string getTokenValue();
    std::string getTokenTypeString();
    static std::string getTokenTypeString(Token::Type);
    friend std::ostream &operator<<(std::ostream &, Token &);
    friend class TokenFactory;
};