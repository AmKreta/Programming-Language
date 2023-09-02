#pragma once

#include <symbol/symbol.hpp>
#include <rVal/rVal.hpp>
#include <evaluable/rValConst.hpp>

class FunctionSymbol : public Symbol
{
private:
    std::shared_ptr<Function> function;

public:
    FunctionSymbol(int, std::shared_ptr<Function>);
    std::shared_ptr<Function> getFunction();
    std::string getInstanceOf() override;
    std::string toString() override;
};