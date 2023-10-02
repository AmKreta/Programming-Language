#include <exception/exceptionFactory.hpp>
#include <bootstrap/bootstrap.hpp>
#include <bootstrap/array.bootstrap.hpp>
#include <evaluable/rValueConstFactory.hpp>
#include <iostream>

std::string Bootstrap::bootstrapArray()
{
    return arrayBootstrapString;
}

std::shared_ptr<RVal> Bootstrap::bridgeFunction(std::shared_ptr<RVal> val, std::string method, RValPointerArray& args){
    if(val->getType() == RVal::Type::ARRAY){
        auto arrConst = std::dynamic_pointer_cast<ArrayConst>(val);
        auto& arr = arrConst->getData();
        return Bootstrap::arrayBridgeFunction(arr, method, args);
    }
    std::cout<<val->getTypeString();
    return RValConstFactory::createUndefinedConstSharedPtr();
}

std::shared_ptr<RVal> Bootstrap::arrayBridgeFunction(RValPointerArray& val, std::string method, RValPointerArray& args)
{
    if(method == "push"){
        for(auto i=0;i<args.size();i++)
            val.push_back(args[i]);
        return RValConstFactory::createUndefinedConstSharedPtr();
    }
    if(method == "length"){
        return RValConstFactory::createNumberConstSharedPtr(val.size());
    }
}