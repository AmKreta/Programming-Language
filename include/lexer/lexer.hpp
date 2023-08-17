#pragma once

#include <token/token.hpp>
#include <token/tokenFactory.hpp>
#include <string>

class Lexer
{
private:
    std::string input;
    int line, column, currentPosition;
    Token currentToken = TokenFactory::build(Token::Type::START_OF_FILE);

public:
    Lexer(std::string);
    void advance(int); // advances the cursor one step ahead and keeps track of line and col
    int getLine();
    int getColumn();
    std::string peek(int);
    void skipSkippable(); // skips whitespace, nextline, tabs etc
    Token getNextToken();
    Token getCurrentToken();
    Token readNumber();     // reads no
    Token readString(char); // reads string of type """, '', ``
    Token readID();         // reads keywords and identifires
};