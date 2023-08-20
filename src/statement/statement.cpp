#include <statement/statement.hpp>

Statement::Statement(Statement::Type type) : type(type) {}

Statement::Type Statement::getType()
{
    return this->type;
}