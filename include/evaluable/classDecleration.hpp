#pragma once
#include <evaluable/evaluable.hpp>
#include <rVal/rVal.hpp>
#include <evaluable/rValConst.hpp>

class ClassDecleration : public Evaluable
{
private:
    std::string name;
    std::unordered_map<std::string, std::shared_ptr<RVal>> dataMembers;
    std::unordered_map<std::string, std::shared_ptr<FunctionConst>> staticMembers;

public:
    ClassDecleration(std::string, std::unordered_map<std::string, std::shared_ptr<FunctionConst>>);
    std::string getName();
    std::unordered_map<std::string, std::shared_ptr<FunctionConst>> &getStaticMembers();
     std::unordered_map<std::string, std::shared_ptr<RVal>>& getDataMembers();
    std::shared_ptr<RVal> acceptVisitor(Visitor *);
};