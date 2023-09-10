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

    static std::shared_ptr<NullConst> NullSharedPtr;
    static std::shared_ptr<UndefinedConst> UndefinedSharedPtr;

public:
    // for number const
    static NumberConst *createNumberConstPtr(double);
    static std::shared_ptr<NumberConst> createNumberConstSharedPtr(double);

    // for string const
    static StringConst *createStringConstPtr(std::string);
    static std::shared_ptr<StringConst> createStringConstSharedPtr(std::string);

    // for string const
    static BooleanConst *createBooleanConstPtr(bool);
    static std::shared_ptr<BooleanConst> createBooleanConstSharedPtr(bool);

    // for array const
    static ArrayConst *createArrayConstPtr(RValPointerArray);
    static std::shared_ptr<ArrayConst> createArrayConstSharedPtr(RValPointerArray);

    // for map const
    static MapConst *createMapConstPtr(RValPointerMap);
    static std::shared_ptr<MapConst> createMapConstSharedPtr(RValPointerMap);

    // for null
    static std::shared_ptr<NullConst> createNullConstSharedPtr();

    // for undefined
    static std::shared_ptr<UndefinedConst> createUndefinedConstSharedPtr();

    // for functions
    static std::shared_ptr<FunctionConst> createFunctionConstSharedPtr(std::shared_ptr<Function>);
    static FunctionConst* createFunctionConstPtr(std::shared_ptr<Function>);
};