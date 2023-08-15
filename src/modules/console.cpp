// #pragma once

// #include<rval/rVal.hpp>
// #include<evaluable/rValConst.hpp>

// class Console{
//     private:
//         static logNumberCOnst(std::shared_ptr<NumberConst>);

//         static logStringConst(std::shared_ptr<StringConst>);

//         static logArrayConst(std::shared_ptr<ArrayConst>);

//         static logMapConst(std::shared_ptr<MapConst>);

//     public:
//         static log(std::shared_ptr<RVal>);
// }

#include <modules/console.hpp>
#include <iostream>

void Console::logNumberConst(std::shared_ptr<NumberConst> num)
{
    std::cout << num->getData();
}

void Console::logStringConst(std::shared_ptr<StringConst> str)
{
    std::cout <<"\""<<str->getData()<<"\"";
}

void Console::logArrayConst(std::shared_ptr<ArrayConst> arr)
{
    std::cout << "[";
    auto children = arr->getData();
    int size = children.size();
    for (int i = 0; i < size; i++)
    {
        Console::log(children[i]);
        if (i < size - 1)
            std::cout << ", ";
    }
    std::cout << "]";
}

void Console::logMapConst(std::shared_ptr<MapConst> map)
{
    std::cout << "{";
    auto entries = map->getData();
    int size = entries.size();
    int i = 0;
    for (auto [key, val] : entries)
    {
        Console::log(key);
        std::cout << " : ";
        Console::log(val);
        if (i++ < size - 1)
            std::cout << ", ";
    }
    std::cout << "}";
}

void Console::log(std::shared_ptr<RVal> rval)
{
    auto type = rval->getType();

    if (type == RVal::Type::NUMBER)
        return Console::logNumberConst(std::dynamic_pointer_cast<NumberConst>(rval));
    if (type == RVal::Type::STRING)
        return Console::logStringConst(std::dynamic_pointer_cast<StringConst>(rval));
    if (type == RVal::Type::ARRAY)
        return Console::logArrayConst(std::dynamic_pointer_cast<ArrayConst>(rval));
    if (type == RVal::Type::MAP)
        return Console::logMapConst(std::dynamic_pointer_cast<MapConst>(rval));
}