#pragma once

#include <rVal/rVal.hpp>
#include <evaluable/evaluable.hpp>

// need to define template class in header itlself
template <typename T>
class RValConst : public RVal, public Evaluable, public std::enable_shared_from_this<RValConst<T>>
{
protected:
    T data;

public:
    RValConst(T data, RVal::Type type) : data(data), RVal(type) {}

    T getData()
    {
        return this->data;
    }

    void setData(T data)
    {
        this->data = data;
    }

    std::shared_ptr<RVal> acceptVisitor(Visitor *visitor)
    {
        return this->shared_from_this();
    }
};

// type alias
typedef RValConst<double> NumberConst;
typedef RValConst<std::string> StringConst;
typedef std::vector<std::shared_ptr<RVal>> ArrayElement; // element of an array
typedef RValConst<ArrayElement> ArrayConst;