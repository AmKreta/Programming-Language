#include <evaluable/bridgeFnExpr.hpp>
#include <visitor/visitor.hpp>

BridgeFnExpr::BridgeFnExpr(std::shared_ptr<Evaluable> valueExpr, std::string fnName, std::vector<std::shared_ptr<Evaluable>>& args) : valueExpr(valueExpr), fnName(fnName), args(args) {}

std::shared_ptr<RVal> BridgeFnExpr::acceptVisitor(Visitor *visitor)
{
    return visitor->visitBridgeFnExpr(this);
}

std::shared_ptr<Evaluable> BridgeFnExpr::getValueExpr()
{
    return this->valueExpr;
}

std::string BridgeFnExpr::getFnName()
{
    return this->fnName;
}

std::vector<std::shared_ptr<Evaluable>>& BridgeFnExpr::getArgs()
{
    return this->args;
}
