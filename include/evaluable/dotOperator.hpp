#pragma once

#include <evaluable/evaluable.hpp>

class DotOperator : public Evaluable
{
private:
    // any expression
    std::shared_ptr<Evaluable> instanceExpr;
    // var or function call
    std::shared_ptr<Evaluable> member;

public:
    DotOperator(std::shared_ptr<Evaluable>, std::shared_ptr<Evaluable>);
    std::shared_ptr<Evaluable> getInstanceExpr();
    std::shared_ptr<Evaluable> getMember();
    std::shared_ptr<RVal> acceptVisitor(Visitor *) override;
};