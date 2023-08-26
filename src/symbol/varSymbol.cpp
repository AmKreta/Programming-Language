#include <symbol/varSymbol.hpp>
#include <evaluable/rValueConstFactory.hpp>
#include <sstream>

VarSymbol::VarSymbol(std::string instanceOf, int scopeLevel) : value(RValConstFactory::createUndefinedConstSharedPtr()), isInTemploralDeadzone(true), Symbol(Symbol::Type::VARIABLE, scopeLevel) {}

std::string VarSymbol::getInstanceOf()
{
    return this->value->getTypeString();
}

bool VarSymbol::getIsInTemporalDeadZone()
{
    return this->isInTemploralDeadzone;
}

void VarSymbol::setIsInTemporalDeadZone(bool isInTemploralDeadzone)
{
    this->isInTemploralDeadzone = isInTemploralDeadzone;
}

std::string VarSymbol::toString()
{
    std::ostringstream oss;
    oss << "<Instance Of -> '" << this->getInstanceOf() << "', "
        << "Scope Level -> " << this->scopeLevel << ">";
    return oss.str();
}

std::shared_ptr<RVal> VarSymbol::getValue()
{
    return this->value;
}

void VarSymbol::setValue(std::shared_ptr<RVal> val)
{
    this->value = val;
}
