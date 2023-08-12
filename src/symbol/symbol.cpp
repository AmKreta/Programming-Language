#include <symbol/symbol.hpp>
#include <sstream>

// #pragma once

Symbol::Symbol(Symbol::Type type) : type(type) {}

std::vector<std::string> Symbol::typeString = {
    "VARIABLE",
    "CLASS",
    "FUNCTION"};

std::string Symbol::getTokenTypeString(Symbol::Type type)
{
    return Symbol::typeString[static_cast<int>(type)];
}

std::string Symbol::getTokenTypeString()
{
    return Symbol::typeString[static_cast<int>(this->type)];
}

std::string Symbol::toString()
{
    std::ostringstream oss;
    oss << "Symbol ------> "<<this->getTokenTypeString();
    return oss.str();
}
