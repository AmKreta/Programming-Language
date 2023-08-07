#pragma once

#include <token/token.hpp>
#include <string>

class Lexer
{
private:
    std::string input;
    int line, column, currentPosition;

public:
    Lexer(std::string);
    void advance(int); // advances the cursor one step ahead and keeps track of line and col
    int getLine();
    int getColumn();
    std::string peek(int);
    void skipSkippable(); // skips whitespace, nextline, tabs etc
    Token getNextToken();
    Token readNumber(); // reads no
    Token readString(char); // reads string of type """, '', ``
    Token readID();     // reads keywords and identifires
};