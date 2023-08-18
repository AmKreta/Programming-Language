#pragma once

#include <evaluable/evaluable.hpp>

class ConditionalOperation : public Evaluable
{
private:
    std::shared_ptr<Evaluable> condition, _if, _else;

public:
    ConditionalOperation(std::shared_ptr<Evaluable>, std::shared_ptr<Evaluable>, std::shared_ptr<Evaluable>);
    std::shared_ptr<Evaluable> getCondition();
    std::shared_ptr<Evaluable> get_if();
    std::shared_ptr<Evaluable> get_else();
    std::shared_ptr<RVal> acceptVisitor(Visitor *) override;
};