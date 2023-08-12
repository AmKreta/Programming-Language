#pragma once

#include <evaluable/numberConst.hpp>
#include <evaluable/unaryOperation.hpp>
#include <evaluable/binaryOperation.hpp>
class Visitor
{
public:
    virtual double visitNumberConst(NumberConst *) = 0;
    virtual double visitUnaryOperation(UnaryOperation *) = 0;
    virtual double visitBinaryOperation(BinaryOperation *) = 0;
    ~Visitor() = default;
};