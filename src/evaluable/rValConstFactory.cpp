#include <evaluable/rValueConstFactory.hpp>

// for number
RValConst<double> *RValConstFactory::createNumberConstPtr(double data)
{
    return RValConstFactory::createPtr<double>(data, RVal::Type::NUMBER);
}

std::shared_ptr<RValConst<double>> RValConstFactory::createNumberConstSharedPtr(double data)
{
    return RValConstFactory::createSharedPtr<double>(data, RVal::Type::NUMBER);
}

// for string const
RValConst<std::string> *RValConstFactory::createStringConstPtr(std::string data)
{
    return RValConstFactory::createPtr<std::string>(data, RVal::Type::STRING);
}

std::shared_ptr<RValConst<std::string>> RValConstFactory::createStringConstSharedPtr(std::string data)
{
    return RValConstFactory::createSharedPtr<std::string>(data, RVal::Type::STRING);
}