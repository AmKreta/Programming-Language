#include <evaluable/mapAst.hpp>
#include <visitor/visitor.hpp>

MapAst::MapAst(std::unordered_map<std::shared_ptr<Evaluable>, std::shared_ptr<Evaluable>> entries) : entries(entries) {}

std::unordered_map<std::shared_ptr<Evaluable>, std::shared_ptr<Evaluable>>& MapAst::getEntries()
{
    return this->entries;
}

std::shared_ptr<RVal> MapAst::acceptVisitor(Visitor *visitor)
{
    return visitor->visitMapAst(this);
}