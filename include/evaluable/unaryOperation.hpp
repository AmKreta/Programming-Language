#pragma once

#include <token/token.hpp>
#include <evaluable/evaluable.hpp>
#include <rVal/rVal.hpp>

class UnaryOperation : public Evaluable
{
private:
    Token::Type type;
    std::shared_ptr<Evaluable> child;
public:
    UnaryOperation(Token::Type, std::shared_ptr<Evaluable>);
    Token::Type getType();
    std::shared_ptr<Evaluable> getChild();
    RVal* acceptVisitor(Visitor *) override;
};