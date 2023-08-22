// #pragma once

#include <runable/ifElse.hpp>
#include <visitor/visitor.hpp>

IfElse::IfElse(std::shared_ptr<Evaluable> condition, std::shared_ptr<CompoundStatement> ifBlock, std::shared_ptr<CompoundStatement> elseBlock) : condition(condition), ifBlock(ifBlock), elseBlock(elseBlock) {}

std::shared_ptr<Evaluable> IfElse::getCondition()
{
    return this->condition;
}

std::shared_ptr<CompoundStatement> IfElse::getIfBlock()
{
    return this->ifBlock;
}

std::shared_ptr<CompoundStatement> IfElse::getElseBlock()
{
    return this->elseBlock;
}

void IfElse::acceptVisitor(Visitor *visitor)
{
    visitor->visitIfElse(this);
}
