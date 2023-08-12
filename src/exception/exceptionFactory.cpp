#include <exception/exceptionFactory.hpp>

template <typename... Args>
Exception ExceptionFactory::create(int line, int col, Args... args)
{
    std::ostringstream oss;
    auto stream_args = [&](const auto &arg)
    { oss << arg << " "; };
    (stream_args(args), ...);
    oss << "on line no. " << line << ", on column " << col;
    return Exception{oss.str()};
}