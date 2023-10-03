#pragma once

#include <token/token.hpp>
#include <evaluable/evaluable.hpp>
#include <rVal/rVal.hpp>

class BridgeFnExpr : public Evaluable
{
private:
    std::shared_ptr<Evaluable> valueExpr;
    std::string fnName;
    std::vector<std::shared_ptr<Evaluable>> args;

public:
    BridgeFnExpr(std::shared_ptr<Evaluable>, std::string, std::vector<std::shared_ptr<Evaluable>>&);
    std::shared_ptr<RVal> acceptVisitor(Visitor *) override;
    std::shared_ptr<Evaluable> getValueExpr();
    std::string getFnName();
    std::vector<std::shared_ptr<Evaluable>>& getArgs();
};