#include <rVal/rVal.hpp>

std::vector<std::string> RVal::TypeStr = {
    "NUMBER",
    "STRING",
    "ARRAY",
    "MAP",
    "SET",
    "OBJECT",
    "FUNCTION",
    "BOOLEAN",
    "Null", // null,
    "UNDEFINED"};

RVal::RVal(RVal::Type type) : type(type){};

RVal::Type RVal::getType()
{
    return this->type;
}

std::string RVal::getTypeString()
{
    return RVal::TypeStr[static_cast<int>(this->type)];
}

std::string RVal::getTypeString(RVal::Type type)
{
    return RVal::TypeStr[static_cast<int>(type)];
}
