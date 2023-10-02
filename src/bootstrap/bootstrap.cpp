#include <exception/exceptionFactory.hpp>
#include <bootstrap/bootstrap.hpp>
#include <bootstrap/array.bootstrap.hpp>
#include <evaluable/rValueConstFactory.hpp>
#include <utility/arr.util.hpp>

std::string Bootstrap::bootstrapArray()
{
    return arrayBootstrapString;
}

std::shared_ptr<RVal> Bootstrap::bridgeFunction(std::shared_ptr<RVal> val, std::string method, RValPointerArray &args)
{
    if (val->getType() == RVal::Type::ARRAY)
    {
        auto arrConst = std::dynamic_pointer_cast<ArrayConst>(val);
        auto &arr = arrConst->getData();
        return Bootstrap::arrayBridgeFunction(arr, method, args);
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
}