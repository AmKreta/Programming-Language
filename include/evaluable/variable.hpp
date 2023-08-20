#pragma once

#include <string>
#include <evaluable/evaluable.hpp>

class Variable : public Evaluable
{
private:
    std::string name;

public:
    Variable(std::string);
    std::string getVarName();
    std::shared_ptr<RVal> acceptVisitor(Visitor *) override;
};