#include <exception/exceptionFactory.hpp>

template <typename... Args>
Exception ExceptionFactory::create(Args... args)
{
    std::ostringstream oss;
    auto stream_args = [&](const auto &arg)
    { oss << arg << " "; };
    (stream_args(args), ...);
    return Exception{oss.str()};
}