#include <exception/exceptionFactory.hpp>
#include <bootstrap/bootstrap.hpp>
#include <bootstrap/array.bootstrap.hpp>
#include <bootstrap/map.bootstrap.hpp>
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
        if (args.size() == 0 || args.size() == 1)
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
}

std::shared_ptr<RVal> stringBridgeFunction(std::string &val, std::string method, RValPointerArray &args)
{
}