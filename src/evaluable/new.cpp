#include <evaluable/new.hpp>
#include <visitor/visitor.hpp>

New::New(std::string className, std::vector<std::shared_ptr<Evaluable>> args) : className(className), args(args) {}

std::string &New::getClassName()
{
    return this->className;
}

std::vector<std::shared_ptr<Evaluable>> &New::getArgs()
{
    return this->args;
}

std::shared_ptr<RVal> New::acceptVisitor(Visitor *)
{

}