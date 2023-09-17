#include <token/tokenFactory.hpp>

std::unordered_map<Token::Type, std::string> TokenFactory::tokenTypeValMap = {
    {Token::Type::LET, "let"},
    {Token::Type::CONST, "const"},
    {Token::Type::NUMBER, "number"},
    {Token::Type::STRING, "string"},
    {Token::Type::ARRAY, "Array"},
    {Token::Type::OBJECT, "Object"},
    {Token::Type::FUNCTION, "Function"},
    {Token::Type::INTERFACE, "interface"},
    {Token::Type::CLASS, "class"},
    {Token::Type::TYPE, "type"},
    {Token::Type::Null, "null"},
    {Token::Type::UNDEFINED, "undefined"},
    {Token::Type::TRUE, "true"},
    {Token::Type::FALSE, "false"},
    {Token::Type::LESS_THAN, "<"},
    {Token::Type::GREATER_THAN, ">"},
    {Token::Type::LESS_THAN_EQUAL_TO, "<="},
    {Token::Type::GREATER_THAN_EQUAL_TO, ">="},
    {Token::Type::EQUAL_TO, "=="},
    {Token::Type::NOT_EQUAL_TO, "!="},
    {Token::Type::LOGICAL_AND, "&&"},
    {Token::Type::LOGICAL_OR, "||"},
    {Token::Type::LOGICAL_NOT, "!"},
    {Token::Type::PLUS, "+"},
    {Token::Type::MINUS, "-"},
    {Token::Type::DIVIDE, "/"},
    {Token::Type::MULTIPLY, "*"},
    {Token::Type::POWER, "**"},
    {Token::Type::MODULUS, "%"},
    {Token::Type::BITWISE_AND, "&"},
    {Token::Type::BITWISE_OR, "|"},
    {Token::Type::BITWISE_NOT, "~"},
    {Token::Type::BITWISE_XOR, "^"},
    {Token::Type::BITWISE_L_SHIFT, "<<"},
    {Token::Type::BITWISE_R_SHIFT, ">>"},
    {Token::Type::ASSIGNMENT, "="},
    {Token::Type::COMMA, ","},
    {Token::Type::COLON, ":"},
    {Token::Type::SEMI_COLON, ";"},
    {Token::Type::L_PAREN, "("},
    {Token::Type::R_PAREN, ")"},
    {Token::Type::L_BRACKET, "["},
    {Token::Type::R_BRACKET, "]"},
    {Token::Type::L_BRACES, "{"},
    {Token::Type::R_BRACES, "}"},
    {Token::Type::FOR, "for"},
    {Token::Type::WHILE, "while"},
    {Token::Type::DO, "do"},
    {Token::Type::IF, "if"},
    {Token::Type::ELIF, "elif"},
    {Token::Type::ELSE, "else"},
    {Token::Type::QUESTION, "?"},
    {Token::Type::RETURN, "return"},
    {Token::Type::SINGLE_QUOTE, "'"},
    {Token::Type::DOUBLE_QUOTE, "\""},
    {Token::Type::BACK_TICK, "`"},
    {Token::Type::END_OF_FILE, "END_OF_FILE"},
    {Token::Type::START_OF_FILE, "START_OF_FILE"},
    {Token::Type::PRINT, "print"},
    {Token::Type::NEW, "new"},
    {Token::Type::DOT, "."}};

Token TokenFactory::build(Token::Type type)
{
    return {type, TokenFactory::tokenTypeValMap[type]};
}

Token TokenFactory::build(Token::Type type, std::string val)
{
    return {type, val};
}
