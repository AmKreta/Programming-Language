#pragma once

#include <token/token.hpp>
#include <evaluable/evaluable.hpp>
#include <rVal/rVal.hpp>

class BinaryOperation : public Evaluable
{
private:
    Token::Type operation;
    std::shared_ptr<Evaluable> leftChild, rightChild;

public:
    BinaryOperation(std::shared_ptr<Evaluable>, Token::Type, std::shared_ptr<Evaluable>);
    Token::Type getOperation();
    std::shared_ptr<Evaluable> getLeftChild();
    std::shared_ptr<Evaluable> getRightChild();
    std::shared_ptr<RVal> acceptVisitor(Visitor *) override;
};