#pragma once

#include <evaluable/evaluable.hpp>
#include <rValConst/rValConst.hpp>

class NumberConst : public Evaluable, public RValConst<double>
{
public:
    NumberConst(double);
    double getData() override;
    double acceptVisitor(Visitor *) override;
};