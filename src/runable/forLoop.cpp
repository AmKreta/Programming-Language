#include <runable/forLoop.hpp>
#include<visitor/visitor.hpp>

ForLoop::ForLoop(std::shared_ptr<CompoundStatement> initializations, std::shared_ptr<Evaluable> condition, std::shared_ptr<CompoundStatement> updates, std::shared_ptr<CompoundStatement> statementList) : initializations(initializations), condition(condition), updates(updates), statementList(statementList) {}

std::shared_ptr<CompoundStatement> ForLoop::getInitializations()
{
    return this->initializations;
}

std::shared_ptr<Evaluable> ForLoop::getCondition()
{
    return this->condition;
}

std::shared_ptr<CompoundStatement> ForLoop::getUpdates()
{
    return this->updates;
}

std::shared_ptr<CompoundStatement> ForLoop::getStatementList(){
    return this->statementList;
}

void ForLoop::acceptVisitor(Visitor *visitor)
{
    visitor->visitForLoop(this);
}