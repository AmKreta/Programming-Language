#pragma once

#include <rVal/rVal.hpp>
#include <evaluable/rValConst.hpp>

class ConversionFunctions
{
public:
    static std::shared_ptr<NumberConst> StringToNumber(std::shared_ptr<RVal>);
    static bool RValToBool(std::shared_ptr<RVal>);
};