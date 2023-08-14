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
ArrayConst *RValConstFactory::createArrayConstPtr(ArrayElement data)
{
    return RValConstFactory::createPtr<ArrayElement>(data, RVal::Type::ARRAY);
}

std::shared_ptr<ArrayConst> RValConstFactory::createArrayConstSharedPtr(ArrayElement data)
{
    return RValConstFactory::createSharedPtr<ArrayElement>(data, RVal::Type::ARRAY);
}