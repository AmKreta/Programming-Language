#include <exception/exceptionFactory.hpp>
#include <bootstrap/bootstrap.hpp>
#include <bootstrap/array.bootstrap.hpp>
#include <bootstrap/map.bootstrap.hpp>
#include <bootstrap/string.bootstrap.hpp>
#include <evaluable/rValueConstFactory.hpp>
#include <utility/arr.util.hpp>

std::string Bootstrap::bootstrapArray()
{
    return arrayBootstrapString;
}

std::string Bootstrap::bootstrapMap()
{
    return mapBootstrapString;
}

std::string Bootstrap::bootstrapString()
{
    return stringBootstrapString;
}

std::shared_ptr<RVal> Bootstrap::bridgeFunction(std::shared_ptr<RVal> val, std::string method, RValPointerArray &args)
{
    if (val->getType() == RVal::Type::ARRAY)
    {
        auto arrConst = std::dynamic_pointer_cast<ArrayConst>(val);
        auto &arr = arrConst->getData();
        return Bootstrap::arrayBridgeFunction(arr, method, args);
    }
    else if (val->getType() == RVal::Type::MAP)
    {
        auto mapConst = std::dynamic_pointer_cast<MapConst>(val);
        auto &map = mapConst->getData();
        return Bootstrap::mapBridgeFunction(map, method, args);
    }
    else if (val->getType() == RVal::Type::STRING)
    {
        auto strConst = std::dynamic_pointer_cast<StringConst>(val);
        auto &str = strConst->getData();
        return Bootstrap::stringBridgeFunction(str, method, args);
    }
    return RValConstFactory::createUndefinedConstSharedPtr();
}

std::shared_ptr<RVal> Bootstrap::arrayBridgeFunction(RValPointerArray &val, std::string method, RValPointerArray &args)
{

    if (method == "push")
    {
        for (auto i = 0; i < args.size(); i++)
            val.push_back(args[i]);
        return RValConstFactory::createUndefinedConstSharedPtr();
    }

    else if (method == "length")
    {
        return RValConstFactory::createNumberConstSharedPtr(val.size());
    }

    else if (method == "slice")
    {
        if (args[0]->getType() == RVal::Type::UNDEFINED)
        {
            auto res = slice(val, 0);
            return RValConstFactory::createArrayConstSharedPtr(res);
        }
        else if (args[0]->getType() == RVal::Type::NUMBER)
        {
            if (args[1]->getType() == RVal::Type::UNDEFINED)
            {
                // only srart provided
                auto startConst = std::dynamic_pointer_cast<NumberConst>(args[0]);
                auto start = static_cast<int>(startConst->getData());
                auto res = slice(val, start);
                return RValConstFactory::createArrayConstSharedPtr(res);
            }
            else if (args[0]->getType() == RVal::Type::NUMBER)
            {
                auto startConst = std::dynamic_pointer_cast<NumberConst>(args[0]);
                auto endConst = std::dynamic_pointer_cast<NumberConst>(args[1]);
                auto start = startConst->getData();
                auto end = endConst->getData();
                auto res = slice(val, start, end);
                return RValConstFactory::createArrayConstSharedPtr(res);
            }
            throw ExceptionFactory::create("Array.slice expects second arg as number, got ", args[1]->getTypeString());
        }
        throw ExceptionFactory::create("Array.slice expects first arg as number, got ", args[0]->getTypeString());
    }
    else if (method == "splice")
    {
        if (args[0]->getType() != RVal::Type::NUMBER)
            throw ExceptionFactory::create("Array.splice expects second arg as number, got ", args[1]->getTypeString());
        auto startConst = std::dynamic_pointer_cast<NumberConst>(args[0]);
        auto start = static_cast<int>(startConst->getData());
        if (args[1]->getType() != RVal::Type::NUMBER)
            throw ExceptionFactory::create("Array.splice expects second arg as number, got ", args[1]->getTypeString());
        auto deleteCountConst = std::dynamic_pointer_cast<NumberConst>(args[1]);
        auto deleteCount = static_cast<int>(startConst->getData());
        if (args[2]->getType() != RVal::Type::ARRAY)
            throw ExceptionFactory::create("Array.splice expects second arg as array, got ", args[1]->getTypeString());
        auto arrConst = std::dynamic_pointer_cast<ArrayConst>(args[2]);
        auto &arr = arrConst->getData();
        auto spliced = splice(val, start, deleteCount, arr);
        return RValConstFactory::createArrayConstSharedPtr(spliced);
    }
    else if (method == "reverse")
    {
        std::reverse(val.begin(), val.end());
        return RValConstFactory::createUndefinedConstSharedPtr();
    }
    else if(method == "clone"){
        auto res = std::vector(val.begin(), val.end());
        return RValConstFactory::createArrayConstSharedPtr(res);
    }
    throw ExceptionFactory::create("method ", method, " is not present in class Array.");
}

std::shared_ptr<RVal> Bootstrap::mapBridgeFunction(RValPointerMap &val, std::string method, RValPointerArray &args)
{
    if (method == "insert")
    {
        if (args.size() == 0 || args.size() == 1)
            throw ExceptionFactory::create("map.insert(key, val) need a key and a value to insert in map");
        val.insert(std::pair(args[0], args[1]));
        return RValConstFactory::createUndefinedConstSharedPtr();
    }
    else if (method == "remove")
    {
        if (args.size() == 0)
            throw ExceptionFactory::create("map.delete(key) needs a key to delete in map");
        val.erase(args[0]);
        return RValConstFactory::createUndefinedConstSharedPtr();
    }
    else if (method == "getKeys")
    {
        RValPointerArray keys;
        for (auto &[key, _] : val)
            keys.push_back(key);
        return RValConstFactory::createArrayConstSharedPtr(keys);
    }
    else if (method == "getValues")
    {
        RValPointerArray values;
        for (auto &[_, vals] : val)
            values.push_back(vals);
        return RValConstFactory::createArrayConstSharedPtr(values);
    }
    else if(method == "clone"){
        auto res = RValPointerMap(val.begin(), val.end());
        return RValConstFactory::createMapConstSharedPtr(res);
    }
    throw ExceptionFactory::create("method ", method, " is not present in class Map.");
}

std::shared_ptr<RVal> Bootstrap::stringBridgeFunction(std::string &val, std::string method, RValPointerArray &args)
{
    if (method == "slice")
    {
        if (args.size() < 2 || (args[0]->getType() != RVal::Type::NUMBER || args[1]->getType() != RVal::Type::NUMBER))
            throw ExceptionFactory::create("string.replace(old, new) expects two strings as arguments.");
        int start = std::dynamic_pointer_cast<NumberConst>(args[0])->getData();
        int end = std::dynamic_pointer_cast<NumberConst>(args[1])->getData();
        if (start < 0)
            start += val.size();
        if (end < 0)
            end += val.size();
        if (start < 0)
            start = 0;
        if (end > static_cast<int>(val.size()))
            end = val.size();

        if (start >= end)
            return RValConstFactory::createStringConstSharedPtr("");

        auto res = val.substr(start, end - start);
        return RValConstFactory::createStringConstSharedPtr(res);
    }
    else if (method == "length")
        return RValConstFactory::createNumberConstSharedPtr(val.size());
    else if (method == "reverse")
    {
        std::reverse(val.begin(), val.end());
        return RValConstFactory::createUndefinedConstSharedPtr();
    }
    else if (method == "includes")
    {
        if (args.size() == 0 || args[0]->getType() != RVal::Type::STRING)
            throw ExceptionFactory::create("string.includes(substr) expects a string as argument.");
        auto subStrConst = std::dynamic_pointer_cast<StringConst>(args[0]);
        auto substr = subStrConst->getData();
        auto res = val.find(substr) != std::string::npos;
        return RValConstFactory::createBooleanConstSharedPtr(res);
    }
    else if (method == "replace")
    {
        if (args.size() < 2 || (args[0]->getType() != RVal::Type::STRING || args[1]->getType() != RVal::Type::STRING))
            throw ExceptionFactory::create("string.replace(old, new) expects two strings as arguments.");
        size_t pos = 0;
        auto oldSubstrConst = std::dynamic_pointer_cast<StringConst>(args[0]);
        auto &oldSubstr = oldSubstrConst->getData();
        auto newSubstrConst = std::dynamic_pointer_cast<StringConst>(args[0]);
        auto &newSubstr = oldSubstrConst->getData();
        while ((pos = val.find(oldSubstr, pos)) != std::string::npos)
        {
            val.replace(pos, oldSubstr.length(), newSubstr);
            pos += newSubstr.length();
        }
        RValConstFactory::createUndefinedConstSharedPtr();
    }
    else if (method == "replaceAll")
    {
        if (args.size() < 2 || (args[0]->getType() != RVal::Type::STRING || args[1]->getType() != RVal::Type::STRING))
            throw ExceptionFactory::create("string.replace(old, new) expects two strings as arguments.");
        size_t pos = 0;
        auto oldSubstrConst = std::dynamic_pointer_cast<StringConst>(args[0]);
        auto &oldSubstr = oldSubstrConst->getData();
        auto newSubstrConst = std::dynamic_pointer_cast<StringConst>(args[0]);
        auto &newSubstr = oldSubstrConst->getData();
        while ((pos = val.find(oldSubstr, pos)) != std::string::npos)
        {
            val.replace(pos, oldSubstr.length(), newSubstr);
            pos += newSubstr.length();
        }
        RValConstFactory::createUndefinedConstSharedPtr();
    }
    else if (method == "clone")
    {
        auto str = std::string(val.begin(), val.end());
        return RValConstFactory::createStringConstSharedPtr(str);
    }
    else if (method == "findIndex")
    {
        if (args.size() == 0 || (args[0]->getType() != RVal::Type::STRING))
            throw ExceptionFactory::create("string.findIndex(substr) expects a strings a arguments.");
        auto substrConst = std::dynamic_pointer_cast<StringConst>(args[0]);
        auto &substr = substrConst->getData();
        size_t pos = substr.find(substr);
        auto res = -1;
        if (pos != std::string::npos)
            res = static_cast<int>(pos);
        return RValConstFactory::createNumberConstSharedPtr(res);
    }
    else if(method == "split"){
    RValPointerArray result;
    std::string delimiter = "";
    if(args[0]->getType()!=RVal::Type::STRING)
        throw ExceptionFactory::create("string.findIndex(delimiter) expects a strings a arguments got ", args[0]->getTypeString());
    delimiter = std::dynamic_pointer_cast<StringConst>(args[0])->getData();
    size_t start = 0;
    size_t end = val.find(delimiter);

    while (end != std::string::npos) {
        auto res = RValConstFactory::createStringConstSharedPtr(val.substr(start, end - start));
        result.push_back(res);
        start = end + 1;
        end = val.find(delimiter, start);
    }
    auto res = RValConstFactory::createStringConstSharedPtr(val.substr(start, end));
    result.push_back(res);
    return RValConstFactory::createArrayConstSharedPtr(result);
    }
    throw ExceptionFactory::create("method ", method, " is not present in class string.");
}