#pragma once

#include <rVal/rVal.hpp>

template <typename T>
class RValConst : public RVal
{
protected:
    T data;

public:
    RValConst(T data, RVal::Type type) : data(data),RVal(type) {}
    virtual T getData() = 0;
    virtual ~RValConst() = default;
};