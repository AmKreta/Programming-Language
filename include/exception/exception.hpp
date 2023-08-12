#pragma once

#include<exception>
#include<string>

class Exception:public std::exception{
    private:
        std::string message;
    public:
        Exception(std::string);
        const char* what() const noexcept override;
};