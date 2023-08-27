#include <symbol/symbol.hpp>
#include <sstream>

Symbol::Symbol(Symbol::Type type, int scopeLevel) : scopeLevel(scopeLevel), type(type) {}

int Symbol::getScopeLevel()
{
    return this->scopeLevel;
}

void Symbol::setScopeLevel(int scopeLevel)
{
    this->scopeLevel = scopeLevel;
}

Symbol::Type Symbol::getType()
{
    return this->type;
}