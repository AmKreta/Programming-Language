#include <token/token.hpp>
#include <iomanip>

Token::Token(Token::Type type, std::string value) : type(type), value(value) {}

Token::Type Token::getTokenType()
{
    return this->type;
}

std::string Token::getTokenValue()
{
    return this->value;
}

std::string Token::getTokenTypeString()
{
    return Token::TypeStr[static_cast<int>(this->type)];
}

std::string Token::getTokenTypeString(Token::Type type)
{
    return Token::TypeStr[static_cast<int>(type)];
}

std::ostream &operator<<(std::ostream &os, Token &token)
{
    os << "<Token : {Type = " << token.getTokenTypeString() << ", Value = \"" << token.value << "\"}>";
    return os;
}

std::vector<std::string> Token::TypeStr = {
    // var decl
    "LET",
    "CONST",

    // data types
    "NUMBER",
    "STRING",
    "ARRAY",
    "OBJECT",
    "FUNCTION",
    "INTERFACE",
    "CLASS",
    "TYPE",
    "NILL", // null
    "UNDEFINED",

    // comparision / relational operator
    "LESS_THAN",
    "GREATER_THAN",
    "LESS_THAN_EQUAL_TO",
    "GREATER_THAN_EQUAL_TO",
    "EQUAL_TO",
    "NOT_EQUAL_TO",

    // logical operator / boolean operator
    "LOGICAL_AND",
    "LOGICAL_OR",
    "LOGICAL_NOT",

    // mathemetical operator
    "PLUS",
    "MINUS",
    "DIVIDE",
    "MULTIPLY",
    "POWER",
    "MODULUS",

    // BITWISE operator
    "BITWISE_AND",
    "BITWISE_OR",
    "BITWISE_NOT",
    "BITWISE_XOR",

    // assignment
    "ASSIGNMENT",

    // symbols
    "COMMA",
    "COLON",
    "SEMI_COLON",
    "L_PAREN",
    "R_PAREN",
    "L_BRACKET",
    "R_BRACKET",
    "L_BRACES",
    "R_BRACES",

    "ID", // variables

    // R_VALUES
    "NUMBER_CONST",
    "STRING_CONST",

    // loops
    "FOR",
    "WHILE",
    "DO",

    // CONDITIONAL
    "IF",
    "ELIF",
    "ELSE",

    // string
    "SINGLE_QUOTE",
    "DOUBLE_QUOTE",
    "BACK_TICK",

    // return
    "RETURN",
    "END OF FILE",
    "START_OF_FILE"};