#include <symbol/varSymbol.hpp>
#include <sstream>

VarSymbol::VarSymbol(Symbol::Type type, std::string instanceOf) : Symbol(type), instanceOf(instanceOf) {}

std::string VarSymbol::toString()
{
    std::ostringstream oss;
    oss << "Symbol ------> " << this->getTokenTypeString() << " : " << this->instanceOf;
    return oss.str();
}

std::string VarSymbol::getInstanceOf()
{
    return this->instanceOf;
}

void VarSymbol::setInstanceOf(std::string instanceOf)
{
    this->instanceOf = instanceOf;
}

std::string VarSymbol::inTemporalDeadzone = "__DANGER_VARIABLE_IS_CURRENTLY_IN_TEMPORAL_DEADZONE__";