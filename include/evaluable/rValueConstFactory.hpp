#pragma once

#include <evaluable/rValConst.hpp>

class RValConstFactory
{
private:
    template <typename T>
    static RValConst<T> *createPtr(T data, RVal::Type type)
    {
        return new RValConst<T>(data, type);
    }

    template <typename T>
    static std::shared_ptr<RValConst<T>> createSharedPtr(T data, RVal::Type type)
    {
        return std::make_shared<RValConst<T>>(data, type);
    }

public:
    // for number const
    static RValConst<double> *createNumberConstPtr(double);
    static std::shared_ptr<RValConst<double>> createNumberConstSharedPtr(double);

    // for string const
    static RValConst<std::string> *createStringConstPtr(std::string);
    static std::shared_ptr<RValConst<std::string>> createStringConstSharedPtr(std::string);
};