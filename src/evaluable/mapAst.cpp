#include <evaluable/mapAst.hpp>
#include <visitor/visitor.hpp>

// #pragma once

// #include <token/token.hpp>
// #include <evaluable/evaluable.hpp>
// #include <rVal/rVal.hpp>

// //{[key]}
// class MapAst : public Evaluable
// {
// private:
//     std::unordered_map<std::shared_ptr<Evaluable>, std::shared_ptr<Evaluable>> children;

// public:
//     MapAst(std::unordered_map<std::shared_ptr<Evaluable>, std::shared_ptr<Evaluable>>);
//     std::unordered_map<std::shared_ptr<Evaluable>, std::shared_ptr<Evaluable>> getChildren();
//     std::shared_ptr<RVal> acceptVisitor(Visitor *) override;
// };

MapAst::MapAst(std::unordered_map<std::shared_ptr<Evaluable>, std::shared_ptr<Evaluable>> entries) : entries(entries) {}

std::unordered_map<std::shared_ptr<Evaluable>, std::shared_ptr<Evaluable>> MapAst::getEntries()
{
    return this->entries;
}

std::shared_ptr<RVal> MapAst::acceptVisitor(Visitor *visitor)
{
    return visitor->visitMapAst(this);
}