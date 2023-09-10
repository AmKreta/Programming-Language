#pragma once

#include <string>
#include <vector>
#include <rVal/rVal.hpp>

// basically store all defined vars, classes, functions here
class Symbol
{
public:
    enum class Type : int
    {
        FUNCTION = 0,
        VARIABLE,
        CLASS
    };
    int scopeLevel;
    Symbol::Type type;
    std::shared_ptr<RVal> value;
    bool isInTemploralDeadzone; // set true in execution phase, when decleared

public:
    Symbol(Symbol::Type, int, std::shared_ptr<RVal>, bool isInTemporalDeadZone = false); // symbol type, scope level, value, isIntemporalDezdzone
    int getScopeLevel();
    void setScopeLevel(int);
    bool getIsInTemporalDeadZone();
    void setIsInTemporalDeadZone(bool);
    std::shared_ptr<RVal> getValue();
    void setValue(std::shared_ptr<RVal>);
    Symbol::Type getType();
    std::string getInstanceOf();
    std::string toString();
};