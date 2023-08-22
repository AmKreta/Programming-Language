#include <runable/expressionStatement.hpp>
#include <visitor/visitor.hpp>

ExpressionStatement::ExpressionStatement(std::shared_ptr<Evaluable> expression) : expression(expression) {}

std::shared_ptr<Evaluable> ExpressionStatement::getExpression()
{
    return this->expression;
}

void ExpressionStatement::acceptVisitor(Visitor *visitor)
{
    visitor->visitExpressionStatement(this);
}