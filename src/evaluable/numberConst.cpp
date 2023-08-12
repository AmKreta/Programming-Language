#include <evaluable/numberConst.hpp>

NumberConst::NumberConst(double data) : RValConst<double>(data) {}

double NumberConst::getData()
{
    return this->data;
}

double NumberConst::acceptVisitor(Visitor *visitor)
{
    return visitor->visitNumberConst(this);
}