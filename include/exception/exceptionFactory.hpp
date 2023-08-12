#pragma once

#include <exception/exception.hpp>
#include <sstream>

class ExceptionFactory
{
public:
    template <typename... Args>
    static Exception create(int, int, Args...);
};