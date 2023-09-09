#include <symbol/symbolTable.hpp>
#include <exception/exceptionFactory.hpp>
#include <iostream>
#include <evaluable/rValConst.hpp>

SymbolTable::SymbolTable(std::shared_ptr<SymbolTable> enclosingScope, bool shouldDestroyChildren) : enclosingScope(enclosingScope), scopeLevel(enclosingScope ? enclosingScope->getScopeLevel() + 1 : 0), symbols({}), children({}), shouldDestroyChildren(shouldDestroyChildren) {}

int SymbolTable::getScopeLevel()
{
    return this->scopeLevel;
}

void SymbolTable::addSymbol(std::string name, std::shared_ptr<Symbol> symbol)
{
    if (this->symbols.find(name) == this->symbols.end())
        this->symbols.insert(std::pair(name, symbol));
    else
        throw ExceptionFactory::create("Redeclearation of variable", name);
}

void SymbolTable::setSymbol(std::string name, std::shared_ptr<RVal> value)
{
    if (this->symbols.find(name) != this->symbols.end())
    {
        auto symbol = this->symbols[name];
        symbol->setValue(value);
        symbol->setIsInTemporalDeadZone(false);
    }
    else
        throw ExceptionFactory::create("symbol not found", name);
}

std::shared_ptr<Symbol> SymbolTable::getSymbol(std::string name)
{

    auto res = this->symbols.find(name);
    if (res != this->symbols.end())
        return res->second;
    else if (this->enclosingScope != nullptr)
        return this->enclosingScope->getSymbol(name);
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

std::unordered_map<std::string, std::shared_ptr<Symbol>> &SymbolTable::getSymbolsMap()
{
    return this->symbols;
}

void SymbolTable::print(int ident)
{
    std::cout << std::endl
              << std::string(ident, ' ') << "Entering Scope level " << this->scopeLevel;
    for (auto child : this->children)
        child->print((ident + 1) * 2);
    if (this->symbols.size())
    {
        std::cout << std::endl;
        for (auto &[var, symbol] : this->symbols)
        {
            std::cout << std::string(ident, ' ') << var << " -> " << symbol->toString() << std::endl;
            if (symbol->getType() == Symbol::Type::FUNCTION)
            {
                auto fnConst = std::dynamic_pointer_cast<FunctionConst>(symbol->getValue());
                if (symbol->getScopeLevel() == this->scopeLevel)
                    fnConst->getData().getCorospondingSymbolTable()->print((ident + 1) * 2);
            }
        }
    }
    std::cout << std::string(ident, ' ') << "Exiting Scope level " << this->scopeLevel << std::endl
              << std::endl;
}

void SymbolTable::printThis()
{
    std::cout << std::endl
              << "Entering Scope level " << this->scopeLevel << std::endl;
    if (this->symbols.size())
    {
        std::cout << std::endl
                  << "variables .................." << std::endl;
        for (auto &[var, symbol] : this->symbols)
        {
            std::cout << var << " -> " << symbol->toString() << std::endl;
        }
    }
    std::cout << "Exiting Scope level " << this->scopeLevel << std::endl
              << std::endl;
}

bool SymbolTable::getshouldDestroyChildren()
{
    return this->shouldDestroyChildren;
}