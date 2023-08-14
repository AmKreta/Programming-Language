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
