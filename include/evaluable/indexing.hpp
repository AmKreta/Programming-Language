#pragma once

#include <evaluable/evaluable.hpp>
#include <rVal/rVal.hpp>

class Indexing : public Evaluable
{
private:
    // valid for
    // rvalConst, functioncall, vars
    std::shared_ptr<Evaluable> val;
    std::shared_ptr<Evaluable> index;

public:
    Indexing(std::shared_ptr<Evaluable>, std::shared_ptr<Evaluable>);
    std::shared_ptr<Evaluable> getVal();
    std::shared_ptr<Evaluable> getIndex();
    std::shared_ptr<RVal> acceptVisitor(Visitor *) override;
};