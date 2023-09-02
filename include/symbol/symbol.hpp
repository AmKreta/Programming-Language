#pragma once

#include <string>
#include <vector>

// basically store all defined vars, classes, functions here
class Symbol
{
public:
    enum class Type : int
    {
        FUNCTION = 0,
        VARIABLE,
        CLASS
    };
    int scopeLevel;
    Symbol::Type type;
public:
    Symbol(Symbol::Type, int);
    int getScopeLevel();
    void setScopeLevel(int);
    Symbol::Type getType();
    virtual std::string getInstanceOf() = 0;
    virtual std::string toString() = 0;
    virtual ~Symbol() = default;
};