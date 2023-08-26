#pragma once

#include <symbol/symbolTable.hpp>
#include <rVal/rVal.hpp>
#include <evaluable/rValueConstFactory.hpp>

class Scope
{
private:
    std::shared_ptr<SymbolTable> corospondingSymbolTable;
public:
    Scope(std::shared_ptr<SymbolTable>);
    std::shared_ptr<RVal> getVar(std::string); // get this value from symbol table
    void addVar(std::string);                  // make this value isInTemporalDeadzone false
    void setVar(std::string, std::shared_ptr<RVal> value = RValConstFactory::createUndefinedConstSharedPtr());
    std::shared_ptr<SymbolTable> getCorospondingSymbolTable();
};