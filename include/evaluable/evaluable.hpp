#pragma once

#include <astNode/astNode.hpp>
#include <visitor/visitor.hpp>

class Evaluable : public AstNode
{
public:
    virtual double acceptVisitor(Visitor *) = 0;
    virtual ~Evaluable() = 0;
};