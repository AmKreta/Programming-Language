#pragma once

#include <evaluable/evaluable.hpp>

class New : public Evaluable
{
private:
    std::shared_ptr<Evaluable> classNameExpr;
    std::vector<std::shared_ptr<Evaluable>> args;

public:
    New(std::shared_ptr<Evaluable>, std::vector<std::shared_ptr<Evaluable>>);
    std::shared_ptr<Evaluable> getClassNameExpr();
    std::vector<std::shared_ptr<Evaluable>> &getArgs();
    std::shared_ptr<RVal> acceptVisitor(Visitor *) override;
};