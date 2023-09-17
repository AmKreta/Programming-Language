#include <evaluable/dotOperator.hpp>
#include <visitor/visitor.hpp>

DotOperator::DotOperator(std::shared_ptr<Evaluable> instanceExpr, std::shared_ptr<Evaluable> member) : instanceExpr(instanceExpr), member(member) {}

std::shared_ptr<Evaluable> DotOperator::getInstanceExpr()
{
    return this->instanceExpr;
}

std::shared_ptr<Evaluable> DotOperator::getMember()
{
    return this->member;
}

std::shared_ptr<RVal> DotOperator::acceptVisitor(Visitor *visitor)
{
    return visitor->visitDotOperator(this);
}