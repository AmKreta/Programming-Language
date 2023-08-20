#pragma once

#include <astNode/astNode.hpp>

class Visitor;

class Runable : public AstNode
{
public:
    virtual void acceptVisitor(Visitor *) = 0;
    virtual ~Runable() = default;
};