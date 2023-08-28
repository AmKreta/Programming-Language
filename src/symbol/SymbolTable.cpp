#include <symbol/symbolTable.hpp>
#include <exception/exceptionFactory.hpp>
#include <iostream>

SymbolTable::SymbolTable(std::shared_ptr<SymbolTable> enclosingScope) : enclosingScope(enclosingScope), scopeLevel(enclosingScope ? enclosingScope->getScopeLevel() + 1 : 0), varSymbols({}), children({}) {}

int SymbolTable::getScopeLevel()
{
    return this->scopeLevel;
}

void SymbolTable::addVarSymbol(std::string name, std::shared_ptr<VarSymbol> symbol)
{
    if (this->varSymbols.find(name) == this->varSymbols.end())
        this->varSymbols.insert(std::pair(name, symbol));
    else
        throw ExceptionFactory::create("Redeclearation of symbol", name);
}

std::shared_ptr<VarSymbol> SymbolTable::getVarSymbol(std::string name)
{

    auto res = this->varSymbols.find(name);
    if (res != this->varSymbols.end())
        return res->second;
    else if (this->enclosingScope != nullptr)
        return this->enclosingScope->getVarSymbol(name);
    throw ExceptionFactory::create("Symbol not found", name);
}

std::shared_ptr<SymbolTable> SymbolTable::getEnclosingScope()
{
    return this->enclosingScope;
}

std::list<std::shared_ptr<SymbolTable>> &SymbolTable::getChildren()
{
    return this->children;
}

 std::unordered_map<std::string, std::shared_ptr<VarSymbol>>& SymbolTable::getVarSymbolsMap(){
    return this->varSymbols;
 }

void SymbolTable::print()
{
    std::cout << std::endl
              << "Entering Scope" << std::endl;
    std::cout<<"variables............."<<std::endl;          
    for (auto [var, symbol] : this->varSymbols)
        std::cout << var << " -> " << symbol->toString() << std::endl;
    for (auto child : this->children)
        child->print();
    std::cout << "Exiting Scope" << std::endl;
}

void SymbolTable::printThis()
{
    std::cout << std::endl
              << "Entering Scope" << std::endl;
    std::cout<<"variables............."<<std::endl;          
    for (auto [var, symbol] : this->varSymbols)
        std::cout << var << " -> " << symbol->toString() << std::endl;
    std::cout << "Exiting Scope" << std::endl;
}