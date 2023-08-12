#pragma once

#include <evaluable/numberConst.hpp>
#include <evaluable/unaryOperation.hpp>
class Visitor
{
public:
    virtual double visitNumberConst(NumberConst *) = 0;
    virtual double visitUnaryOperation(UnaryOperation *) = 0;
    ~Visitor() = default;
};