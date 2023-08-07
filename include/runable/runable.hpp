#pragma once

#include <astNode/astNode.hpp>
#include <visitor/visitor.hpp>

class Runable : public AstNode
{
public:
    virtual void visit(Visitor *) = 0;
    virtual ~Runable() = default;
}