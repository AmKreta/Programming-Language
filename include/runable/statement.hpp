#pragma once

#include<runable/runable.hpp>

class Statement : public Runable
{
public:
    enum class Type : int
    {
        ASSIGNMENT,
        VAR_DECLERATION,
        FUNCTION_DECLERATION,
        CLASS_DECLERATION,
        IF_ELSE_STATEMENT,
        LOOP,
        SWITCH
    };

private:
    Statement::Type type;

public:
    Statement(Statement::Type);
    Statement::Type getType();
};