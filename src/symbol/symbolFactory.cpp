#include <symbol/symbolFactory.hpp>
#include <symbol/varSymbol.hpp>
#include <exception/exceptionFactory.hpp>

std::shared_ptr<Symbol> SymbolFactory::createVarSymbol(std::string instanceOf, int scopeLevel)
{
    return std::make_shared<VarSymbol>(instanceOf, scopeLevel);
}