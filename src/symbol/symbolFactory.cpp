#include <symbol/symbolFactory.hpp>
#include <symbol/varSymbol.hpp>
#include <exception/exceptionFactory.hpp>

std::shared_ptr<Symbol> SymbolFactory::createVarSymbol(int scopeLevel)
{
    return std::make_shared<VarSymbol>(scopeLevel);
}