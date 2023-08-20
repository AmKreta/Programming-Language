#pragma once

class Statement
{
public:
    enum class Type : int
    {
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