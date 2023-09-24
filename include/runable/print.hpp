#pragma once

#include <runable/statement.hpp>
#include <evaluable/evaluable.hpp>

class Print : public Statement
{
private:
    std::vector<std::shared_ptr<Evaluable>> args;
    bool newLine;

public:
    Print(std::vector<std::shared_ptr<Evaluable>>, bool newLine = false);
    void acceptVisitor(Visitor *) override;
    std::vector<std::shared_ptr<Evaluable>> &getArgs();
    bool hasNewLine();
};