#include <evaluable/variable.hpp>
#include<visitor/visitor.hpp>

Variable::Variable(std::string name) : name(name) {}

std::string Variable::getVarName()
{
    return this->name;
}

std::shared_ptr<RVal> Variable::acceptVisitor(Visitor *visitor)
{
    return visitor->visitVariable(this);
}
