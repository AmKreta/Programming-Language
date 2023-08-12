#pragma once

#include <string>
#include <vector>

class Symbol
{
public:
    enum class Type : int
    {
        VARIABLE = 0,
        CLASS,
        FUNCTION,
    };

private:
    Symbol::Type type;

public:
    Symbol(Symbol::Type);
    static std::vector<std::string> typeString;
    static std::string getTokenTypeString(Symbol::Type);
    std::string getTokenTypeString();
    std::string toString();
    ~Symbol() = default;
};