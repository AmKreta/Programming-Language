#include <evaluable/classDecleration.hpp>
#include <visitor/visitor.hpp>

ClassDecleration::ClassDecleration(std::string name, std::unordered_map<std::string, std::shared_ptr<RVal>> members, std::unordered_map<std::string, std::shared_ptr<FunctionConst>> staticMembers) : name(name), members(members), staticMembers(staticMembers){};

std::string ClassDecleration::getName()
{
    return this->name;
}

std::unordered_map<std::string, std::shared_ptr<RVal>> &ClassDecleration::getMembers()
{
    return this->members;
}

std::unordered_map<std::string, std::shared_ptr<FunctionConst>> &ClassDecleration::getStaticMembers()
{
    return this->staticMembers;
}

std::shared_ptr<RVal> ClassDecleration::acceptVisitor(Visitor *visitor)
{
    return visitor->visitClassDecleration(this);
}