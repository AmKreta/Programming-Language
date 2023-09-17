#include <evaluable/instance.hpp>

Instance::Instance(std::shared_ptr<Symbol> classSymbol) : classSymbol(classSymbol), dataMembers({}) {}

std::shared_ptr<Symbol> Instance::getClassSymbol()
{
    return this->classSymbol;
}

std::unordered_map<std::string, std::shared_ptr<RVal>> &Instance::getDataMembers()
{
    return this->dataMembers;
}

std::shared_ptr<RVal> acceptVisitor(Visitor *visitor)
{
}