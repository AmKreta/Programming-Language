#include <symbol/functionSymbol.hpp>
#include <sstream>

FunctionSymbol::FunctionSymbol(int scopeLevel, std::shared_ptr<Function> function, std::shared_ptr<SymbolTable> corospondingSymbolTable) : Symbol(Symbol::Type::FUNCTION, scopeLevel), function(function), corospondingSymbolTable(corospondingSymbolTable) {}

std::shared_ptr<Function> FunctionSymbol::getFunction()
{
    return this->function;
}

std::string FunctionSymbol::getInstanceOf()
{
    return "FUNCTION";
}

std::string FunctionSymbol::toString()
{
    std::ostringstream oss;
    oss << "<Instance Of -> '" << this->getInstanceOf() << "', "
        << "Scope Level -> " << this->scopeLevel<<">";
    return oss.str();
}

std::shared_ptr<SymbolTable> FunctionSymbol::getCorospndingSymbolTable()
{
    return this->corospondingSymbolTable;
}