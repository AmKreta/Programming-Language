#pragma once

#include <evaluable/evaluable.hpp>
#include <visitor/visitor.hpp>
#include <symbol/symbolTable.hpp>

class AssignmentOperation
{
public:
    static std::shared_ptr<RVal> evaluate(Visitor *, std::shared_ptr<Evaluable>, std::shared_ptr<Evaluable>, std::shared_ptr<SymbolTable>);
};