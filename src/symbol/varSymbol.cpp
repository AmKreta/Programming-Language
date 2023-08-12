#include <symbol/varSymbol.hpp>
#include <sstream>

VarSymbol::VarSymbol(Symbol::Type type, std::string instanceOf = VarSymbol::inTemporalDeadzone) : Symbol(type), instanceOf(instanceOf) {}

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

std::string VarSymbol::inTemporalDeadzone = "__DANGER_VARIABLE_IS_NOT_DECLEARED_YET__";