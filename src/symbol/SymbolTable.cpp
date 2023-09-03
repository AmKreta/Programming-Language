#include <symbol/symbolTable.hpp>
#include <exception/exceptionFactory.hpp>
#include <iostream>

SymbolTable::SymbolTable(std::shared_ptr<SymbolTable> enclosingScope, bool shouldDestroyChildren) : enclosingScope(enclosingScope), scopeLevel(enclosingScope ? enclosingScope->getScopeLevel() + 1 : 0), varSymbols({}), children({}), shouldDestroyChildren(shouldDestroyChildren) {}

int SymbolTable::getScopeLevel()
{
    return this->scopeLevel;
}

void SymbolTable::addVarSymbol(std::string name, std::shared_ptr<VarSymbol> symbol)
{
    if (this->varSymbols.find(name) == this->varSymbols.end())
        this->varSymbols.insert(std::pair(name, symbol));
    else
        throw ExceptionFactory::create("Redeclearation of variable", name);
}

std::shared_ptr<VarSymbol> SymbolTable::getVarSymbol(std::string name)
{

    auto res = this->varSymbols.find(name);
    if (res != this->varSymbols.end())
        return res->second;
    else if (this->enclosingScope != nullptr)
        return this->enclosingScope->getVarSymbol(name);
    throw ExceptionFactory::create("variable not found", name);
}

std::shared_ptr<SymbolTable> SymbolTable::getEnclosingScope()
{
    return this->enclosingScope;
}

std::vector<std::shared_ptr<SymbolTable>> &SymbolTable::getChildren()
{
    return this->children;
}

std::unordered_map<std::string, std::shared_ptr<VarSymbol>> &SymbolTable::getVarSymbolsMap()
{
    return this->varSymbols;
}

void SymbolTable::print()
{
    std::cout << std::endl
              << "Entering Scope level " << this->scopeLevel << std::endl;
    for (auto child : this->children)
        child->print();
    if (this->varSymbols.size())
    {
        std::cout << std::endl
                  << "variables .................." << std::endl;
        for (auto &[var, symbol] : this->varSymbols)
            std::cout << var << " -> " << symbol->toString() << std::endl;
    }
    if (this->funSymbols.size())
    {
        std::cout << std::endl
                  << "functions .................." << std::endl;
        for (auto [name, funSymbol] : this->funSymbols)
            std::cout << name << " -> " << funSymbol->toString() << std::endl;
    }
    std::cout << "Exiting Scope level " << this->scopeLevel << std::endl
              << std::endl;
}

void SymbolTable::printThis()
{
    std::cout << std::endl
              << "Entering Scope level " << this->scopeLevel << std::endl;
    for (auto [var, symbol] : this->varSymbols)
        std::cout << var << " -> " << symbol->toString() << std::endl;
    std::cout << "Exiting Scope level " << this->scopeLevel << std::endl
              << std::endl;
}

bool SymbolTable::getshouldDestroyChildren()
{
    return this->shouldDestroyChildren;
}

void SymbolTable::addFuncSymbol(std::string name, std::shared_ptr<FunctionSymbol> funSymbol)
{
    if (this->funSymbols.find(name) == this->funSymbols.end())
        this->funSymbols.insert(std::pair(name, funSymbol));
    else
        throw ExceptionFactory::create("Redeclearation of function", name);
}

std::shared_ptr<FunctionSymbol> SymbolTable::getFunSymbol(std::string name)
{
    auto res = this->funSymbols.find(name);
    if (res != this->funSymbols.end())
        return res->second;
    else if (this->enclosingScope != nullptr)
        return this->enclosingScope->getFunSymbol(name);
    throw ExceptionFactory::create("variable not found", name);
}
