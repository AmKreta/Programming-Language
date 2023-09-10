#pragma once

#include <runable/statement.hpp>
#include <evaluable/evaluable.hpp>

class Print : public Statement
{
private:
    std::vector<std::shared_ptr<Evaluable>> args;

public:
    Print(std::vector<std::shared_ptr<Evaluable>>);
    void acceptVisitor(Visitor *) override;
    std::vector<std::shared_ptr<Evaluable>> getArgs();
};