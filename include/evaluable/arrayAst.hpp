#pragma once

#include <token/token.hpp>
#include <evaluable/evaluable.hpp>
#include <rVal/rVal.hpp>

class ArrayAst : public Evaluable
{
private:
    std::vector<std::shared_ptr<Evaluable>> children;

public:
    ArrayAst(std::vector<std::shared_ptr<Evaluable>>);
    std::vector<std::shared_ptr<Evaluable>> getChildren();
    std::shared_ptr<RVal> acceptVisitor(Visitor *) override;
};