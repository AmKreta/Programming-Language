#pragma once

#include <symbol/symbol.hpp>
#include <rVal/rVal.hpp>
#include <evaluable/rValConst.hpp>
// #include <symbol/symbolTable.hpp>

class SymbolTable;

class FunctionSymbol : public Symbol
{
private:
    std::shared_ptr<Function> function;
    std::shared_ptr<SymbolTable> corospondingSymbolTable;

public:
    FunctionSymbol(int, std::shared_ptr<Function>, std::shared_ptr<SymbolTable>);
    std::shared_ptr<SymbolTable> getCorospndingSymbolTable();
    void setCorospndingSymbolTable(std::shared_ptr<SymbolTable>);
    std::shared_ptr<Function> getFunction();
    std::string getInstanceOf() override;
    std::string toString() override;
};