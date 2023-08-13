#include <evaluable/numberConst.hpp>
#include<visitor/visitor.hpp>
#include<rVal/rVal.hpp>

NumberConst::NumberConst(double data) : RValConst<double>(data, RVal::Type::NUMBER) {}

double NumberConst::getData()
{
    return this->data;
}

RVal* NumberConst::acceptVisitor(Visitor *visitor)
{
    return visitor->visitNumberConst(this);
}