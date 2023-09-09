#pragma once

#include <symbol/symbol.hpp>
#include <list>

class SymbolTable
{
private:
    // add symbol for vars/ function defination, class defination
    std::unordered_map<std::string, std::shared_ptr<Symbol>> symbols;
    std::shared_ptr<SymbolTable> enclosingScope;
    std::vector<std::shared_ptr<SymbolTable>> children;
    int scopeLevel;
    bool shouldDestroyChildren; // set False for loops

public:
    SymbolTable(std::shared_ptr<SymbolTable> enclosingScope = nullptr, bool shouldDestroyChildren = false);
    void addSymbol(std::string, std::shared_ptr<Symbol>);
    std::shared_ptr<Symbol> getSymbol(std::string);
    void setSymbol(std::string, std::shared_ptr<RVal>);
    std::vector<std::shared_ptr<SymbolTable>> &getChildren();
    std::unordered_map<std::string, std::shared_ptr<Symbol>> &getSymbolsMap();
    int getScopeLevel();
    std::shared_ptr<SymbolTable> getEnclosingScope();
    bool getshouldDestroyChildren();
    void print(int ident = 0);
    void printThis();
    virtual ~SymbolTable() = default;
};