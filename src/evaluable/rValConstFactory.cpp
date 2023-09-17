#include <evaluable/rValueConstFactory.hpp>

// defining constants

std::shared_ptr<NullConst> RValConstFactory::NullSharedPtr = std::make_shared<NullConst>(nullptr, RVal::Type::Null);
std::shared_ptr<UndefinedConst> RValConstFactory::UndefinedSharedPtr = std::make_shared<UndefinedConst>(nullptr, RVal::Type::UNDEFINED);

// for number
NumberConst *RValConstFactory::createNumberConstPtr(double data)
{
    return RValConstFactory::createPtr<double>(data, RVal::Type::NUMBER);
}

std::shared_ptr<NumberConst> RValConstFactory::createNumberConstSharedPtr(double data)
{
    return RValConstFactory::createSharedPtr<double>(data, RVal::Type::NUMBER);
}

// for string const
StringConst *RValConstFactory::createStringConstPtr(std::string data)
{
    return RValConstFactory::createPtr<std::string>(data, RVal::Type::STRING);
}

std::shared_ptr<StringConst> RValConstFactory::createStringConstSharedPtr(std::string data)
{
    return RValConstFactory::createSharedPtr<std::string>(data, RVal::Type::STRING);
}

// for Array Const
ArrayConst *RValConstFactory::createArrayConstPtr(RValPointerArray data)
{
    return RValConstFactory::createPtr<RValPointerArray>(data, RVal::Type::ARRAY);
}

std::shared_ptr<ArrayConst> RValConstFactory::createArrayConstSharedPtr(RValPointerArray data)
{
    return RValConstFactory::createSharedPtr<RValPointerArray>(data, RVal::Type::ARRAY);
}

// for map const
MapConst *RValConstFactory::createMapConstPtr(RValPointerMap data)
{
    return RValConstFactory::createPtr<RValPointerMap>(data, RVal::Type::MAP);
}

std::shared_ptr<MapConst> RValConstFactory::createMapConstSharedPtr(RValPointerMap data)
{
    return RValConstFactory::createSharedPtr<RValPointerMap>(data, RVal::Type::MAP);
}

// for string const
BooleanConst *RValConstFactory::createBooleanConstPtr(bool data)
{
    return RValConstFactory::createPtr<bool>(data, RVal::Type::BOOLEAN);
}

std::shared_ptr<BooleanConst> RValConstFactory::createBooleanConstSharedPtr(bool data)
{
    return RValConstFactory::createSharedPtr<bool>(data, RVal::Type::BOOLEAN);
}

// for null
std::shared_ptr<NullConst> RValConstFactory::createNullConstSharedPtr()
{
    return RValConstFactory::NullSharedPtr;
}

// for undefined
std::shared_ptr<UndefinedConst> RValConstFactory::createUndefinedConstSharedPtr()
{
    return RValConstFactory::UndefinedSharedPtr;
}

// for function
std::shared_ptr<FunctionConst> RValConstFactory::createFunctionConstSharedPtr(std::shared_ptr<Function> fn)
{
    return RValConstFactory::createSharedPtr<std::shared_ptr<Function>>(fn, RVal::Type::FUNCTION);
}

FunctionConst *RValConstFactory::createFunctionConstPtr(std::shared_ptr<Function> fn)
{
    return RValConstFactory::createPtr<std::shared_ptr<Function>>(fn, RVal::Type::FUNCTION);
}

// for classes
std::shared_ptr<ClassDeclerationConst> RValConstFactory::createClassDeclerationConstSharedPtr(std::shared_ptr<ClassDecleration> classDecleration)
{
    return RValConstFactory::createSharedPtr<std::shared_ptr<ClassDecleration>>(classDecleration, RVal::Type::CLASS);
}

ClassDeclerationConst *RValConstFactory::createClassDeclerationCnstPtr(std::shared_ptr<ClassDecleration> classDecleration)
{
    return RValConstFactory::createPtr<std::shared_ptr<ClassDecleration>>(classDecleration, RVal::Type::CLASS);
}

// for Instances
std::shared_ptr<InstanceConst> RValConstFactory::createInstanceConstSharedPtr(std::shared_ptr<Instance> instance)
{
    return RValConstFactory::createSharedPtr<std::shared_ptr<Instance>>(instance, RVal::Type::INSTANCE);
}

InstanceConst *RValConstFactory::createInstanceConstPtr(std::shared_ptr<Instance> instance)
{
    return RValConstFactory::createPtr<std::shared_ptr<Instance>>(instance, RVal::Type::INSTANCE);
}