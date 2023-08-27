#include <symbol/varSymbol.hpp>
#include <evaluable/rValueConstFactory.hpp>
#include <sstream>
#include <utility/toString.hpp>
#include<modules/console.hpp>

VarSymbol::VarSymbol(int scopeLevel) : value(RValConstFactory::createUndefinedConstSharedPtr()), isInTemploralDeadzone(true), Symbol(Symbol::Type::VARIABLE, scopeLevel) {}

std::string VarSymbol::getInstanceOf()
{
    if(this->value->getType() == RVal::Type::UNDEFINED)
        return "UNDEFINED";
    if(this->value->getType() == RVal::Type::Null)
        return "NULL";
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
        << "Scope Level -> " << this->scopeLevel << ", "
        << "value -> " << ToString::convert(this->value) << ", "
        << "isInTemporalDeadZone -> " << this->isInTemploralDeadzone << ">";
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
