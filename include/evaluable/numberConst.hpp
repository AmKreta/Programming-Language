#pragma once

#include <evaluable/evaluable.hpp>
#include <rVal/rValConst.hpp>

class NumberConst : public Evaluable, public RValConst<double>
{
public:
    NumberConst(double);
    double getData() override;
    double acceptVisitor(Visitor *) override;
};