#pragma once

#include <runable/statement.hpp>
#include <evaluable/evaluable.hpp>

class Return : public Statement
{
private:
    std::shared_ptr<Evaluable> expr;

public:
    Return(std::shared_ptr<Evaluable>);
    std::shared_ptr<Evaluable> getExpr();
    void acceptVisitor(Visitor *) override;
};