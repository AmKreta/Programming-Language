#include <evaluable/binaryOperation.hpp>
#include<visitor/visitor.hpp>

BinaryOperation::BinaryOperation(std::shared_ptr<Evaluable> leftChild, Token::Type operation, std::shared_ptr<Evaluable> rightChild) : leftChild(leftChild), rightChild(rightChild), operation(operation) {}

Token::Type BinaryOperation::getOperation()
{
    return this->operation;
}

std::shared_ptr<Evaluable> BinaryOperation::getLeftChild()
{
    return this->leftChild;
}

std::shared_ptr<Evaluable> BinaryOperation::getRightChild()
{
    return this->rightChild;
}

RVal* BinaryOperation::acceptVisitor(Visitor *visitor)
{
    return visitor->visitBinaryOperation(this);
}