#include <evaluable/rValueConstFactory.hpp>

// for number
NumberConst *RValConstFactory::createNumberConstPtr(double data)
{
    return RValConstFactory::createPtr<double>(data, RVal::Type::NUMBER);
}

std::shared_ptr<NumberConst> RValConstFactory::createNumberConstSharedPtr(double data)
{
    return RValConstFactory::createSharedPtr<double>(data, RVal::Type::NUMBER);
}

// for string const
StringConst *RValConstFactory::createStringConstPtr(std::string data)
{
    return RValConstFactory::createPtr<std::string>(data, RVal::Type::STRING);
}

std::shared_ptr<StringConst> RValConstFactory::createStringConstSharedPtr(std::string data)
{
    return RValConstFactory::createSharedPtr<std::string>(data, RVal::Type::STRING);
}

// for Array Const
ArrayConst *RValConstFactory::createArrayConstPtr(RValPointerArray data)
{
    return RValConstFactory::createPtr<RValPointerArray>(data, RVal::Type::ARRAY);
}

std::shared_ptr<ArrayConst> RValConstFactory::createArrayConstSharedPtr(RValPointerArray data)
{
    return RValConstFactory::createSharedPtr<RValPointerArray>(data, RVal::Type::ARRAY);
}

// for map const
MapConst *RValConstFactory::createMapConstPtr(RValPointerMap data)
{
    return RValConstFactory::createPtr<RValPointerMap>(data, RVal::Type::MAP);
}

std::shared_ptr<MapConst> RValConstFactory::createMapConstSharedPtr(RValPointerMap data)
{
    return RValConstFactory::createSharedPtr<RValPointerMap>(data, RVal::Type::MAP);
}

// for string const
BooleanConst *RValConstFactory::createBooleanConstPtr(bool data)
{
    return RValConstFactory::createPtr<bool>(data, RVal::Type::BOOLEAN);
}

std::shared_ptr<BooleanConst> RValConstFactory::createBooleanConstSharedPtr(bool data)
{
    return RValConstFactory::createSharedPtr<bool>(data, RVal::Type::BOOLEAN);
}