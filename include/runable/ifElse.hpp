#pragma once

#include <runable/statement.hpp>
#include <evaluable/evaluable.hpp>

class IfElse : public Statement
{
private:
    std::shared_ptr<Evaluable> condition;
    std::vector<std::shared_ptr<Statement>> ifBlock;
    std::vector<std::shared_ptr<Statement>> elseBlock;

public:
    IfElse(std::shared_ptr<Evaluable>, std::vector<std::shared_ptr<Statement>>, std::vector<std::shared_ptr<Statement>>);
    std::shared_ptr<Evaluable> getCondition();
    std::vector<std::shared_ptr<Statement>> getIfBlock();
    std::vector<std::shared_ptr<Statement>> getElseBlock();
    void acceptVisitor(Visitor *) override;
};