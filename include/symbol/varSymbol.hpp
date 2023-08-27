#pragma once

#include <symbol/symbol.hpp>
#include <rVal/rVal.hpp>

class VarSymbol : public Symbol
{
private:
    std::shared_ptr<RVal> value;
    bool isInTemploralDeadzone; // set true in execution phase, when decleared
public:
    VarSymbol(int);
    std::shared_ptr<RVal> getValue();
    void setValue(std::shared_ptr<RVal>);
    std::string getInstanceOf();
    bool getIsInTemporalDeadZone();
    void setIsInTemporalDeadZone(bool);
    std::string toString() override;
};