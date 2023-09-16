#include <runable/varDecleration.hpp>
#include <visitor/visitor.hpp>

VarDecleration::VarDecleration(std::vector<std::pair<std::string, std::shared_ptr<Evaluable>>> declerations) : declerations(declerations) {}

std::vector<std::pair<std::string, std::shared_ptr<Evaluable>>>& VarDecleration::getDeclerations()
{
    return this->declerations;
}

void VarDecleration::acceptVisitor(Visitor *visitor)
{
    visitor->visitVarDecleration(this);
}