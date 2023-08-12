#include <symbol/varSymbol.hpp>
#include <sstream>

VarSymbol::VarSymbol(Symbol::Type type, std::string instanceOf) : Symbol(type), instanceOf(instanceOf) {}

std::string VarSymbol::toString()
{
    std::ostringstream oss;
    oss << "Symbol ------> " << this->getTokenTypeString() << " : " << this->instanceOf;
    return oss.str();
}
