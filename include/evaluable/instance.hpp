#pragma once

#include <symbol/symbol.hpp>
#include <evaluable/evaluable.hpp>
#include <rVal/rVal.hpp>

class Instance:public Evaluable
{
private:
    std::shared_ptr<Symbol> classSymbol;
    std::unordered_map<std::string, std::shared_ptr<RVal>> dataMembers;

public:
    Instance(std::shared_ptr<Symbol>);
    std::shared_ptr<Symbol> getClassSymbol();
    std::unordered_map<std::string, std::shared_ptr<RVal>> &getDataMembers();
    std::shared_ptr<RVal> acceptVisitor(Visitor *) override;
};