#pragma once

#include <token/token.hpp>
#include <evaluable/evaluable.hpp>
#include <rVal/rVal.hpp>

//{[key]}
class MapAst : public Evaluable
{
private:
    std::unordered_map<std::shared_ptr<Evaluable>, std::shared_ptr<Evaluable>> entries;

public:
    MapAst(std::unordered_map<std::shared_ptr<Evaluable>, std::shared_ptr<Evaluable>>);
    std::unordered_map<std::shared_ptr<Evaluable>, std::shared_ptr<Evaluable>> getEntries();
    std::shared_ptr<RVal> acceptVisitor(Visitor *) override;
};