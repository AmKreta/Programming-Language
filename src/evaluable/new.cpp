#include <evaluable/new.hpp>
#include <visitor/visitor.hpp>

New::New(std::shared_ptr<Evaluable> classNameExpr, std::vector<std::shared_ptr<Evaluable>> args) : classNameExpr(classNameExpr), args(args) {}

std::shared_ptr<Evaluable> New::getClassNameExpr()
{
    return this->classNameExpr;
}

std::vector<std::shared_ptr<Evaluable>> &New::getArgs()
{
    return this->args;
}

std::shared_ptr<RVal> New::acceptVisitor(Visitor *visitor)
{
    return visitor->visitNew(this);
}