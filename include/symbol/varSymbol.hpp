#pragma once

#include <symbol/symbol.hpp>

class VarSymbol : public Symbol
{
private:
    std::string instanceOf;
    static std::string inTemporalDeadzone;
public:
    VarSymbol(Symbol::Type, std::string);
    void setInstanceOf(std::string);
    std::string getInstanceOf();
    std::string toString();
};