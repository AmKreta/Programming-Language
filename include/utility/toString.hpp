#pragma once

#include <evaluable/rValConst.hpp>

class ToString
{
    static std::string convertNumberConst(std::shared_ptr<NumberConst>);

    static std::string convertStringConst(std::shared_ptr<StringConst>);

    static std::string convertArrayConst(std::shared_ptr<ArrayConst>);

    static std::string convertMapConst(std::shared_ptr<MapConst>);

    static std::string convertBoolean(std::shared_ptr<BooleanConst>);

    static std::string convertNull();

    static std::string convertUndefined();

public:
    static std::string convert(std::shared_ptr<RVal>);
};