#pragma once

#include <rVal/rVal.hpp>
#include <evaluable/evaluable.hpp>
#include <iostream>
// need to define template class in header itlself
template <typename T>
class RValConst : public RVal, public Evaluable, public std::enable_shared_from_this<RValConst<T>>
{
protected:
    T data;

public:
    RValConst(T data, RVal::Type type) : data(data), RVal(type) {}

    T& getData()
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
typedef RValConst<bool> BooleanConst;

struct CustomHash
{
    std::size_t operator()(const std::shared_ptr<RVal> &rVal) const
    {
        if (rVal->getType() == RVal::Type::NUMBER)
        {
            std::hash<int> hasher;
            int num = std::dynamic_pointer_cast<NumberConst>(rVal)->getData();
            return hasher(num);
        }

        if (rVal->getType() == RVal::Type::STRING)
        {
            std::hash<std::string> hasher;
            std::string str = std::dynamic_pointer_cast<StringConst>(rVal)->getData();
            return hasher(str);
        }

        if (rVal->getType() == RVal::Type::BOOLEAN)
        {
            std::hash<bool> hasher;
            bool boolean = std::dynamic_pointer_cast<BooleanConst>(rVal)->getData();
            return hasher(boolean);
        }

        std::hash<std::shared_ptr<RVal>> hasher;
        return hasher(rVal);
    }
};

struct MyKeyEqual
{
    bool operator()(const std::shared_ptr<RVal> &lhs, const std::shared_ptr<RVal> &rhs) const
    {
        auto typeLhs = lhs->getType();
        auto typeRhs = rhs->getType();
        if (typeLhs != typeRhs)
            return false;
        if (typeLhs == RVal::Type::NUMBER)
        {
            auto num1 = std::dynamic_pointer_cast<NumberConst>(lhs);
            auto num2 = std::dynamic_pointer_cast<NumberConst>(rhs);
            return num1->getData() == num2->getData();
        }

        if (typeRhs == RVal::Type::STRING)
        {
             auto str1 = std::dynamic_pointer_cast<StringConst>(lhs);
            auto str2 = std::dynamic_pointer_cast<StringConst>(rhs);
            return str1->getData() == str2->getData();
        }

        if (typeRhs == RVal::Type::BOOLEAN)
        {
             auto bool1 = std::dynamic_pointer_cast<BooleanConst>(lhs);
            auto bool2 = std::dynamic_pointer_cast<BooleanConst>(rhs);
            return bool1->getData() == bool2->getData();
        }

        return lhs == rhs;
    }
};

typedef std::vector<std::shared_ptr<RVal>> RValPointerArray; // element of an array
typedef RValConst<RValPointerArray> ArrayConst;

typedef std::unordered_map<std::shared_ptr<RVal>, std::shared_ptr<RVal>, CustomHash, MyKeyEqual> RValPointerMap;
typedef RValConst<RValPointerMap> MapConst;

typedef RValConst<std::shared_ptr<void>> NullConst;
typedef RValConst<std::shared_ptr<void>> UndefinedConst;