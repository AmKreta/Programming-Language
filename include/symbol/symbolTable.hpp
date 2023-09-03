#pragma once

#include <symbol/symbol.hpp>
#include <symbol/varSymbol.hpp>
#include <symbol/functionSymbol.hpp>
#include <list>

class SymbolTable
{
private:
    // add symbol for vars/ function defination, class defination
    std::unordered_map<std::string, std::shared_ptr<VarSymbol>> varSymbols;
    std::unordered_map<std::string, std::shared_ptr<FunctionSymbol>> funSymbols;
    std::shared_ptr<SymbolTable> enclosingScope;
    std::vector<std::shared_ptr<SymbolTable>> children;
    int scopeLevel;
    bool shouldDestroyChildren; // set False for loops

public:
    SymbolTable(std::shared_ptr<SymbolTable> enclosingScope = nullptr, bool shouldDestroyChildren = false);
    void addVarSymbol(std::string, std::shared_ptr<VarSymbol>);
    std::shared_ptr<VarSymbol> getVarSymbol(std::string);
    void addFuncSymbol(std::string, std::shared_ptr<FunctionSymbol>);
    std::shared_ptr<FunctionSymbol> getFunSymbol(std::string);
    std::vector<std::shared_ptr<SymbolTable>> &getChildren();
    std::unordered_map<std::string, std::shared_ptr<VarSymbol>> &getVarSymbolsMap();
    int getScopeLevel();
    std::shared_ptr<SymbolTable> getEnclosingScope();
    bool getshouldDestroyChildren();
    void print();
    void printThis();
    virtual ~SymbolTable() = default;
};