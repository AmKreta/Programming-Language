#include <symbol/symbol.hpp>
#include <sstream>
#include <utility/toString.hpp>

Symbol::Symbol(Symbol::Type type, int scopeLevel, std::shared_ptr<RVal> value, bool isInTemporalDeadZone) : scopeLevel(scopeLevel), type(type), value(value), isInTemploralDeadzone(isInTemporalDeadZone) {}

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

bool Symbol::getIsInTemporalDeadZone()
{
    return this->isInTemploralDeadzone;
}

void Symbol::setIsInTemporalDeadZone(bool isInTemporalDeadzone)
{
    this->isInTemploralDeadzone = isInTemporalDeadzone;
}

std::shared_ptr<RVal> Symbol::getValue()
{
    return this->value;
}

void Symbol::setValue(std::shared_ptr<RVal> value)
{
    this->value = value;
}

std::string Symbol::getInstanceOf()
{
    if (this->value->getType() == RVal::Type::UNDEFINED)
        return "UNDEFINED";
    if (this->value->getType() == RVal::Type::Null)
        return "NULL";
    return this->value->getTypeString();
}

std::string Symbol::toString()
{
    std::ostringstream oss;
    if (this->type == Symbol::Type::VARIABLE)
        oss << "<Instance Of -> '" << this->getInstanceOf() << "', "
            << "Scope Level -> " << this->scopeLevel << ", "
            << "value -> " << ToString::convert(this->value) << ", "
            << "isInTemporalDeadZone -> " << this->isInTemploralDeadzone << ">";
    if (this->type == Symbol::Type::FUNCTION)
    oss << "<Instance Of -> '" << this->getInstanceOf() << "', "
        << "Scope Level -> " << this->scopeLevel << ">";
    return oss.str();
}