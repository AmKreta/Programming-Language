#pragma once

#include <runable/compoundStatement.hpp>
#include <evaluable/evaluable.hpp>
#include <runable/statement.hpp>

class IfElse : public Statement
{
private:
    std::shared_ptr<Evaluable> condition;
    std::shared_ptr<CompoundStatement> ifBlock;
    std::shared_ptr<CompoundStatement> elseBlock;

public:
    IfElse(std::shared_ptr<Evaluable>, std::shared_ptr<CompoundStatement>, std::shared_ptr<CompoundStatement>);
    std::shared_ptr<Evaluable> getCondition();
    std::shared_ptr<CompoundStatement> getIfBlock();
    std::shared_ptr<CompoundStatement> getElseBlock();
    void acceptVisitor(Visitor *) override;
};