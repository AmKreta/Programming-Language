#pragma once

#include <symbol/symbol.hpp>
#include <symbol/varSymbol.hpp>
#include <memory>

class SymbolFactory
{
    static std::shared_ptr<Symbol> create(Symbol::Type, std::string);
};