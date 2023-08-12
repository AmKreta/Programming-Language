#include <symbol/symbolFactory.hpp>
#include <symbol/varSymbol.hpp>
#include <exception/exceptionFactory.hpp>

std::shared_ptr<Symbol> SymbolFactory::create(Symbol::Type type, std::string instanceOf)
{
    if (type == Symbol::Type::VARIABLE)
    {
        if (instanceOf == "")
            return std::make_shared<VarSymbol>(type, VarSymbol::inTemporalDeadzone);
        return std::make_shared<VarSymbol>(type, instanceOf);
    }
    return std::make_shared<Symbol>(type);
}