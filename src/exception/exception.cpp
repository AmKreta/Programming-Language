#include<exception/exception.hpp>

Exception::Exception(std::string message):message(message){}

const char* Exception::what() const noexcept {
    return this->message.c_str();
}