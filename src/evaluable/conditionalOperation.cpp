#include <evaluable/conditionalOperator.hpp>
#include<visitor/visitor.hpp>

ConditionalOperation::ConditionalOperation(std::shared_ptr<Evaluable> condition, std::shared_ptr<Evaluable> _if, std::shared_ptr<Evaluable> _else) : condition(condition), _if(_if), _else(_else) {}

std::shared_ptr<Evaluable> ConditionalOperation::getCondition()
{
    return this->condition;
}

std::shared_ptr<Evaluable> ConditionalOperation::get_if()
{
    return this->_if;
}

std::shared_ptr<Evaluable> ConditionalOperation::get_else()
{
    return this->_else;
}

std::shared_ptr<RVal> ConditionalOperation::acceptVisitor(Visitor *visitor){
    return visitor->visitConditionalOperation(this);
}