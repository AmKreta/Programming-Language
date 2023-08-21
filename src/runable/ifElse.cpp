// #pragma once

#include <runable/ifElse.hpp>
#include <visitor/visitor.hpp>

IfElse::IfElse(std::shared_ptr<Evaluable> condition, std::vector<std::shared_ptr<Statement>> ifBlock, std::vector<std::shared_ptr<Statement>> elseBlock) : condition(condition), ifBlock(ifBlock), elseBlock(elseBlock), Statement(Statement::Type::IF_ELSE_STATEMENT) {}

std::shared_ptr<Evaluable> IfElse::getCondition()
{
    return this->condition;
}

std::vector<std::shared_ptr<Statement>> IfElse::getIfBlock()
{
    return this->ifBlock;
}

std::vector<std::shared_ptr<Statement>> IfElse::getElseBlock()
{
    return this->elseBlock;
}

void IfElse::acceptVisitor(Visitor *visitor)
{
    visitor->visitIfElse(this);
}
