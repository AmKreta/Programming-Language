#pragma once

#include <rVal/rVal.hpp>
#include <evaluable/evaluable.hpp>

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
    static RValConst<double> *createNumberConstPtr(double data)
    {
        return RValConstFactory::createPtr<double>(data, RVal::Type::NUMBER);
    }

    static std::shared_ptr<RValConst<double>> createNumberConstSharedPtr(double data)
    {
        return RValConstFactory::createSharedPtr<double>(data, RVal::Type::NUMBER);
    }

    // for string const
    static RValConst<std::string> *createStringConstPtr(std::string data)
    {
        return RValConstFactory::createPtr<std::string>(data, RVal::Type::STRING);
    }

    static std::shared_ptr<RValConst<std::string>> createStringConstSharedPtr(std::string data)
    {
        return RValConstFactory::createSharedPtr<std::string>(data, RVal::Type::STRING);
    }

    
};

// type alias
typedef RValConst<double> NumberConst;
typedef RValConst<std::string> StringConst;