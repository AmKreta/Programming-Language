#pragma once

#include <runable/runable.hpp>
#include <runable/compoundStatement.hpp>
#include <evaluable/evaluable.hpp>

class WhileLoop : public Statement
{
private:
    std::shared_ptr<Evaluable> condition; // empty
    std::shared_ptr<CompoundStatement> compoundStatement;

public:
    WhileLoop(std::shared_ptr<Evaluable>, std::shared_ptr<CompoundStatement>);
    std::shared_ptr<Evaluable> getCondition();
    std::shared_ptr<CompoundStatement> getCompoundStatement();
    void acceptVisitor(Visitor *) override;
};