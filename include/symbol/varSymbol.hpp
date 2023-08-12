#pragma once

#include <symbol/symbol.hpp>

class VarSymbol : public Symbol
{
private:
    std::string instanceOf;

public:
    VarSymbol(Symbol::Type, std::string);
    std::string toString();
};