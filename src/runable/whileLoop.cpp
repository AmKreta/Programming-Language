#include <runable/whileLoop.hpp>
#include <visitor/visitor.hpp>

WhileLoop::WhileLoop(std::shared_ptr<Evaluable> condition, std::shared_ptr<CompoundStatement> compoundStatement) : condition(condition), compoundStatement(compoundStatement) {}

std::shared_ptr<Evaluable> WhileLoop::getCondition()
{
    return this->condition;
}

std::shared_ptr<CompoundStatement> WhileLoop::getCompoundStatement()
{
    return this->compoundStatement;
}

void WhileLoop::acceptVisitor(Visitor *visitor)
{
    visitor->visitWhileLoop(this);
}