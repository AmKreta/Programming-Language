#pragma once

#include <runable/statement.hpp>
#include <evaluable/evaluable.hpp>

// expression ;
class ExpressionStatement : public Statement
{
private:
    std::shared_ptr<Evaluable> expression;

public:
    ExpressionStatement(std::shared_ptr<Evaluable>);
    std::shared_ptr<Evaluable> getExpression();
    void acceptVisitor(Visitor *) override;
};