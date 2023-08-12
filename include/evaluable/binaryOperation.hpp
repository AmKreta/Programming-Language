#pragma once

#include <token/token.hpp>
#include <evaluable/evaluable.hpp>
#include <rValConst/rValConst.hpp>
#include <visitor/visitor.hpp>

class UnaryOperation : public Evaluable
{
private:
    Token::Type operation;
    std::shared_ptr<Evaluable> leftChild, rightChild;

public:
    Token::Type getOperation();
    std::shared_ptr<Evaluable> getLeftChild();
    std::shared_ptr<Evaluable> getRightChild();
    double acceptVisitor(Visitor *) override;
};