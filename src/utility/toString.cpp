#include <utility/toString.hpp>
#include <iostream>
#include <token/token.hpp>
#include <sstream>
#include <exception/exceptionFactory.hpp>

std::string ToString::convertNumberConst(std::shared_ptr<NumberConst> num)
{
    std::ostringstream oss;
    oss << num->getData();
    return oss.str();
}

std::string ToString::convertStringConst(std::shared_ptr<StringConst> str)
{
    std::ostringstream oss;
    oss << "\"" << str->getData() << "\"";
    return oss.str();
}

std::string ToString::convertArrayConst(std::shared_ptr<ArrayConst> arr)
{
    std::ostringstream oss;
    oss << "[";
    auto children = arr->getData();
    int size = children.size();
    for (int i = 0; i < size; i++)
    {
        oss << ToString::convert(children[i]);
        if (i < size - 1)
            oss << ", ";
    }
    oss << "]";
    return oss.str();
}

std::string ToString::convertMapConst(std::shared_ptr<MapConst> map)
{
    std::ostringstream oss;
    oss << "{";
    auto entries = map->getData();
    int size = entries.size();
    int i = 0;
    for (auto [key, val] : entries)
    {
        oss << ToString::convert(key);
        oss << " : ";
        oss << ToString::convert(val);
        if (i++ < size - 1)
            oss << ", ";
    }
    oss << "}";
    return oss.str();
}

std::string ToString::convertBoolean(std::shared_ptr<BooleanConst> bl)
{
    auto res = bl->getData() ? "true" : "false";
    return res;
}

std::string ToString::convertNull()
{
    return "null";
}

std::string ToString::convertUndefined()
{
    return "undefined";
}

std::string ToString::convert(std::shared_ptr<RVal> rval)
{
    auto type = rval->getType();
    if (type == RVal::Type::NUMBER)
        return ToString::convertNumberConst(std::dynamic_pointer_cast<NumberConst>(rval));
    if (type == RVal::Type::STRING)
        return ToString::convertStringConst(std::dynamic_pointer_cast<StringConst>(rval));
    if (type == RVal::Type::ARRAY)
        return ToString::convertArrayConst(std::dynamic_pointer_cast<ArrayConst>(rval));
    if (type == RVal::Type::MAP)
        return ToString::convertMapConst(std::dynamic_pointer_cast<MapConst>(rval));
    if (type == RVal::Type::BOOLEAN)
        return ToString::convertBoolean(std::dynamic_pointer_cast<BooleanConst>(rval));
    if (type == RVal::Type::Null)
        return ToString::convertNull();
    if (type == RVal::Type::UNDEFINED)
        return ToString::convertUndefined();
    if (type == RVal::Type::FUNCTION)
    {
        std::ostringstream oss;
        oss << "[FUNCTION - ";
        auto name = std::dynamic_pointer_cast<FunctionConst>(rval)->getData()->getName();
        oss << (name == "!__ANONYMOUS__" ? "ANONYMOUS" : name);
        oss << "]";
        return oss.str();
    }

    throw ExceptionFactory::create("unable to convert" , rval->getTypeString(), "to string");
}