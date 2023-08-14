#include <evaluable/arrayAst.hpp>
#include <visitor/visitor.hpp>

ArrayAst::ArrayAst(std::vector<std::shared_ptr<Evaluable>> children) : children(children) {}

std::vector<std::shared_ptr<Evaluable>> ArrayAst::getChildren()
{
    return this->children;
}

std::shared_ptr<RVal> ArrayAst::acceptVisitor(Visitor *visitor)
{
    return visitor->visitArrayAst(this);
}