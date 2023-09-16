#pragma once

#include <evaluable/evaluable.hpp>

class FunctionCall : public Evaluable
{
private:
    std::shared_ptr<Evaluable> function;
    std::vector<std::shared_ptr<Evaluable>> arguments;

public:
    FunctionCall(std::shared_ptr<Evaluable>, std::vector<std::shared_ptr<Evaluable>>);
    std::vector<std::shared_ptr<Evaluable>>& getArgs();
    std::shared_ptr<Evaluable> getFunction();
    std::shared_ptr<RVal> acceptVisitor(Visitor *) override;
};