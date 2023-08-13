#pragma once

#include <evaluable/numberConst.hpp>
#include <evaluable/unaryOperation.hpp>
#include <evaluable/binaryOperation.hpp>
#include <rVal/rVal.hpp>
class Visitor
{
public:
    virtual RVal* visitNumberConst(NumberConst *) = 0;
    virtual RVal* visitUnaryOperation(UnaryOperation *) = 0;
    virtual RVal* visitBinaryOperation(BinaryOperation *) = 0;
    virtual ~Visitor() = default;
};