#pragma once

#include <exception/exception.hpp>
#include <sstream>

class ExceptionFactory
{
public:
    template <typename... Args>
    static Exception create(Args... args)
    {
        std::ostringstream oss;
        auto stream_args = [&](const auto &arg)
        { oss << arg << " "; };
        (stream_args(args), ...);
        return Exception{oss.str()};
    }
};