#pragma once
#include <string>
#include <vector>
class RVal
{
public:
    enum class Type : int
    {
        NUMBER = 0,
        STRING,
        ARRAY,
        MAP,
        SET,
        OBJECT,
        FUNCTION,
        BOOLEAN,
        Null, // null,
        UNDEFINED
    };
    static std::vector<std::string> TypeStr;

protected:
    RVal::Type type;

public:
    RVal(RVal::Type);
    RVal::Type getType();
    std::string getTypeString();
    static std::string getTypeString(RVal::Type);
    virtual std::shared_ptr<RVal> getSharedPtr() = 0;
    virtual ~RVal() = default;
    // also add size of operator
    // toString
    //cout overload virtual function
};