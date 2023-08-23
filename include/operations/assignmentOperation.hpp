#pragma once

#include <evaluable/evaluable.hpp>
#include <visitor/visitor.hpp>

class AssignmentOperation
{
public:
    static std::shared_ptr<RVal> evaluate(Visitor *, std::shared_ptr<Evaluable>, std::shared_ptr<Evaluable>, std::unordered_map<std::string, std::shared_ptr<RVal>>&);
};