#pragma once

#include <symbol/symbol.hpp>

class VarSymbol : public Symbol
{
private:
    std::string instanceOf;
public:
    static std::string inTemporalDeadzone;
    VarSymbol(Symbol::Type, std::string);
    void setInstanceOf(std::string);
    std::string getInstanceOf();
    std::string toString();
};