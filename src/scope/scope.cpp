#include <scope/scope.hpp>
#include <symbol/varSymbol.hpp>

Scope::Scope(std::shared_ptr<SymbolTable> corospondingSymbolTable) : corospondingSymbolTable(corospondingSymbolTable) {}

std::shared_ptr<RVal> Scope::getVar(std::string name)
{
    // call this whenever u encounter a variable
    auto res = this->corospondingSymbolTable->getVarSymbol(name);
    return res->getValue();
}

void Scope::addVar(std::string name)
{
    // call this on var decleration
    this->corospondingSymbolTable->getVarSymbol(name)->setIsInTemporalDeadZone(false);
}

void Scope::setVar(std::string name, std::shared_ptr<RVal> value)
{
    //call this on assignment operator
    this->corospondingSymbolTable->getVarSymbol(name)->setValue(value);
}


std::shared_ptr<SymbolTable> Scope::getCorospondingSymbolTable(){
    return this->corospondingSymbolTable;
}