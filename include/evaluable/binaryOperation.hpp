#pragma once

#include <token/token.hpp>
#include <evaluable/evaluable.hpp>
#include <rValConst/rValConst.hpp>
#include <visitor/visitor.hpp>

class BinaryOperation : public Evaluable
{
private:
    Token::Type operation;
    std::shared_ptr<Evaluable> leftChild, rightChild;

public:
    BinaryOperation(std::shared_ptr<Evaluable>, Token::Type ,std::shared_ptr<Evaluable>);
    Token::Type getOperation();
    std::shared_ptr<Evaluable> getLeftChild();
    std::shared_ptr<Evaluable> getRightChild();
    double acceptVisitor(Visitor *) override;
};