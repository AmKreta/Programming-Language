#include <evaluable/unaryOperation.hpp>
#include<visitor/visitor.hpp>

UnaryOperation::UnaryOperation(Token::Type type, std::shared_ptr<Evaluable> child) : type(type), child(child) {}

Token::Type UnaryOperation::getType()
{
    return this->type;
}

std::shared_ptr<Evaluable> UnaryOperation::getChild()
{
    return this->child;
}

std::shared_ptr<RVal> UnaryOperation::acceptVisitor(Visitor *visitor)
{
    return visitor->visitUnaryOperation(this);
}