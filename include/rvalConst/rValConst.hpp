#pragma once

template<typename T>
class RValConst{
    protected:
        T data;
    public:
        RValConst(T data) : data(data) {}
        virtual T getData() = 0;
        virtual ~RValConst() = default;
};