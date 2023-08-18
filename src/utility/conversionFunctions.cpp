#include <utility/conversionFunctions.hpp>
#include <evaluable/rValConst.hpp>
#include <evaluable/rValueConstFactory.hpp>
#include <exception>
#include <limits>

std::shared_ptr<NumberConst> ConversionFunctions::StringToNumber(std::shared_ptr<RVal> str)
{
    auto stringConst = std::dynamic_pointer_cast<StringConst>(str);
    try
    {
        auto num = std::stod(stringConst->getData());
        return RValConstFactory::createNumberConstSharedPtr(num);
    }
    catch (std::exception e)
    {
        return RValConstFactory::createNumberConstSharedPtr(std::numeric_limits<double>::quiet_NaN());
    }
}

bool ConversionFunctions::RValToBool(std::shared_ptr<RVal> rVal)
{
    auto type = rVal->getType();

    if (type == RVal::Type::NUMBER)
    {
        auto num = std::dynamic_pointer_cast<NumberConst>(rVal);
        return static_cast<bool>(num->getData());
    }

    if (type == RVal::Type::STRING)
    {
        auto str = std::dynamic_pointer_cast<StringConst>(rVal);
        return str->getData().size()>0;
    }

    if (type == RVal::Type::BOOLEAN)
    {   
        auto res = std::dynamic_pointer_cast<BooleanConst>(rVal);
        return res->getData();
    }

    if (type == RVal::Type::ARRAY)
        return true;
        
    if (type == RVal::Type::OBJECT)
        return true;
}