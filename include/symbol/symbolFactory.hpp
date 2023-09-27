#pragma once

#include <symbol/symbol.hpp>
#include <memory>
#include <evaluable/rValueConstFactory.hpp>

class SymbolFactory
{
public:
    static std::shared_ptr<Symbol> createVarSymbol(int, std::shared_ptr<RVal> value = RValConstFactory::createUndefinedConstSharedPtr(), bool isIntemporalDeadZone = true);
    static std::shared_ptr<Symbol> createFuncSymbol(int, std::shared_ptr<RVal> value);  
    static std::shared_ptr<Symbol> createClassSymbol(int, std::shared_ptr<RVal>, bool isIntemporalDeadZone = true);
    static std::shared_ptr<Symbol> createToBeHoistedSymbol(int); // all symbols that are supposed to be hoisted
};