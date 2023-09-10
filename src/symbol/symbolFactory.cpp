#include <symbol/symbolFactory.hpp>
#include <exception/exceptionFactory.hpp>

std::shared_ptr<Symbol> SymbolFactory::createVarSymbol(int scopeLevel, std::shared_ptr<RVal> value, bool isInTemporalDeadZone)
{
    return std::make_shared<Symbol>(Symbol::Type::VARIABLE, scopeLevel, value, isInTemporalDeadZone);
}

std::shared_ptr<Symbol> SymbolFactory::createFuncSymbol(int scopeLevel, std::shared_ptr<RVal> value)
{
    return std::make_shared<Symbol>(Symbol::Type::FUNCTION, scopeLevel, value, false);
}