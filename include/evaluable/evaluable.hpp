#pragma once

#include <astNode/astNode.hpp>


class Visitor;

class Evaluable : public AstNode
{
public:
    virtual double acceptVisitor(Visitor *) = 0;
    virtual ~Evaluable() = default;
};