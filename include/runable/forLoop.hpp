#pragma once

#include <runable/runable.hpp>
#include <runable/compoundStatement.hpp>
#include <evaluable/evaluable.hpp>

class ForLoop : public Statement
{
private:
    std::shared_ptr<CompoundStatement> initializations; // mitght be comman separated assignment or varDecl or empty
    std::shared_ptr<Evaluable> condition;               // empty
    std::shared_ptr<CompoundStatement> updates;         //'comma separated values | empty'
    std::shared_ptr<CompoundStatement> statementList;

public:
    ForLoop(std::shared_ptr<CompoundStatement>, std::shared_ptr<Evaluable>, std::shared_ptr<CompoundStatement>, std::shared_ptr<CompoundStatement>);
    std::shared_ptr<CompoundStatement> getInitializations();
    std::shared_ptr<Evaluable> getCondition();
    std::shared_ptr<CompoundStatement> getUpdates();
    std::shared_ptr<CompoundStatement> getStatementList();
    void acceptVisitor(Visitor *) override;
};