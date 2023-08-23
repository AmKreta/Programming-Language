#pragma once

#include <runable/runable.hpp>
#include <evaluable/evaluable.hpp>

// expression ;
class Statement : public Runable
{
    public:
        virtual void fn(){}
};