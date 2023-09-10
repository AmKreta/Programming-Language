#include <runable/print.hpp>
#include <visitor/visitor.hpp>

Print::Print(std::vector<std::shared_ptr<Evaluable>> args) : args(args) {}

std::vector<std::shared_ptr<Evaluable>> Print::getArgs()
{
    return this->args;
}

void Print::acceptVisitor(Visitor *visitor)
{
    visitor->visitPrint(this);
}