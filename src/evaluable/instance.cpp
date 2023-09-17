#include <evaluable/instance.hpp>
#include <visitor/visitor.hpp>

Instance::Instance(std::shared_ptr<Symbol> classSymbol) : classSymbol(classSymbol), dataMembers({}) {}

std::shared_ptr<Symbol> Instance::getClassSymbol()
{
    return this->classSymbol;
}

std::unordered_map<std::string, std::shared_ptr<RVal>> &Instance::getDataMembers()
{
    return this->dataMembers;
}

std::shared_ptr<RVal> Instance::acceptVisitor(Visitor *visitor)
{
    return visitor->visitInstance(this);
}