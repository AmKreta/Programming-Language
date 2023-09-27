#pragma once

#include <evaluable/evaluable.hpp>

class New : public Evaluable
{
private:
    std::string className;
    std::vector<std::shared_ptr<Evaluable>> args;

public:
    New(std::string, std::vector<std::shared_ptr<Evaluable>>);
    std::string getClassName();
    std::vector<std::shared_ptr<Evaluable>> &getArgs();
    std::shared_ptr<RVal> acceptVisitor(Visitor *) override;
};