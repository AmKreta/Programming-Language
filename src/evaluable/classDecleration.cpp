#include <evaluable/classDecleration.hpp>
#include <visitor/visitor.hpp>

ClassDecleration::ClassDecleration(std::string name, std::unordered_map<std::string, std::shared_ptr<Function>> members) : name(name), members(members), corospondingSymbolTable(nullptr), dataMembers({}){};

std::string ClassDecleration::getName()
{
    return this->name;
}

std::unordered_map<std::string, std::shared_ptr<Function>> &ClassDecleration::getMembers()
{
    return this->members;
}

std::shared_ptr<RVal> ClassDecleration::acceptVisitor(Visitor *visitor)
{
    return visitor->visitClassDecleration(this);
}

std::shared_ptr<ClassDecleration> ClassDecleration::getSharedPtr()
{
    return this->shared_from_this();
}

std::shared_ptr<SymbolTable> ClassDecleration::getCorospondingSymbolTable()
{
    return this->corospondingSymbolTable;
}

void ClassDecleration::setCorospondingSymbolTable(std::shared_ptr<SymbolTable> corospondingSymbolTable)
{
    this->corospondingSymbolTable = corospondingSymbolTable;
}

std::unordered_map<std::string, std::shared_ptr<RVal>> &ClassDecleration::getDataMembers()
{
    return this->dataMembers;
}

void ClassDecleration::setDataMember(std::string name, std::shared_ptr<RVal> val)
{
    this->dataMembers.insert(std::pair(name, val));
}