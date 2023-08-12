#pragma once

template<typename T>
class RValConst{
    protected:
        T data;
    public:
        RValConst(T);
        virtual T getData() = 0;
        ~RValConst() = default;
};