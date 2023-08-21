#pragma once

#include <runable/statement.hpp>
#include <evaluable/evaluable.hpp>
#include <evaluable/variable.hpp>

class Assignment : public Statement
{
private:
    std::shared_ptr<Variable> var;
    std::shared_ptr<Evaluable> expr;

public:
    Assignment(std::shared_ptr<Variable>, std::shared_ptr<Evaluable>);
    std::shared_ptr<Variable> getVar();
    std::shared_ptr<Evaluable> getExpr();
    void acceptVisitor(Visitor *) override;
};