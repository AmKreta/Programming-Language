#include <runable/assignment.hpp>
#include <visitor/visitor.hpp>

Assignment::Assignment(std::shared_ptr<Variable> var, std::shared_ptr<Evaluable> expr) : var(var), expr(expr), Statement(Statement::Type::ASSIGNMENT) {}

std::shared_ptr<Variable> Assignment::getVar()
{
    return this->var;
}

std::shared_ptr<Evaluable> Assignment::getExpr()
{
    return this->expr;
}

void Assignment::acceptVisitor(Visitor *visitor)
{
    visitor->visitAssignment(this);
}