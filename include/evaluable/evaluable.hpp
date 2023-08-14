#pragma once

#include <astNode/astNode.hpp>
#include<rVal/rVal.hpp>

class Visitor;

class Evaluable : public AstNode
{
public:
    virtual std::shared_ptr<RVal> acceptVisitor(Visitor *) = 0;
    virtual ~Evaluable() = default;
};