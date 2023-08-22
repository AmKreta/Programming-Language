#include <evaluable/indexing.hpp>
#include <visitor/visitor.hpp>

Indexing::Indexing(std::shared_ptr<Evaluable> val, std::shared_ptr<Evaluable> index) : val(val), index(index) {}

std::shared_ptr<Evaluable> Indexing::getVal()
{
    return this->val;
}

std::shared_ptr<Evaluable> Indexing::getIndex()
{
    return this->index;
}

std::shared_ptr<RVal> Indexing::acceptVisitor(Visitor *visitor)
{
    return visitor->visitIndexing(this);
}