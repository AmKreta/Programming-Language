#pragma once

#include <rVal/rVal.hpp>
#include <evaluable/evaluable.hpp>

// need to define template class in header itlself
template <typename T>
class RValConst : public RVal, public Evaluable
{
protected:
    T data;

public:
    RValConst(T data, RVal::Type type) : data(data), RVal(type) {}

    T getData()
    {
        return this->data;
    }

    void setDate(T data)
    {
        this->data = data;
    }

    RVal *acceptVisitor(Visitor *visitor)
    {
        return this;
    }
};

// type alias
typedef RValConst<double> NumberConst;
typedef RValConst<std::string> StringConst;