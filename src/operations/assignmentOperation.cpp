#include <operations/assignmentOperation.hpp>
#include<exception/exceptionFactory.hpp>

std::shared_ptr<RVal> AssignmentOperation::evaluate(Visitor *visitor, std::shared_ptr<Evaluable> lhs, std::shared_ptr<Evaluable> rhs, std::unordered_map<std::string, std::shared_ptr<RVal>>& globalScope)
{
    auto res = rhs->acceptVisitor(visitor);

    auto var = std::dynamic_pointer_cast<Variable>(lhs);
    if (var)
    {
        if (globalScope.find(var->getVarName()) != globalScope.end())
        {
            auto rVal = res;
            globalScope[var->getVarName()] = rVal;
            return rVal;
        }
        else
            throw ExceptionFactory::create("variable", var->getVarName(), "is not defined");
    }
    
    auto indexing = std::dynamic_pointer_cast<Indexing>(lhs);
    if (indexing)
    {
        auto val = indexing->getVal()->acceptVisitor(visitor);
        auto index = indexing->getIndex()->acceptVisitor(visitor);
        if (val->getType() == RVal::Type::ARRAY && index->getType() == RVal::Type::NUMBER)
        {

            auto &arr = std::dynamic_pointer_cast<ArrayConst>(val)->getData();
            auto idx = std::dynamic_pointer_cast<NumberConst>(index)->getData();
            return arr[idx] = res;
        }
        if (val->getType() == RVal::Type::MAP)
        {
            auto &map = std::dynamic_pointer_cast<MapConst>(val)->getData();
            return map[index] = res;
        }
    }

    throw ExceptionFactory::create("lhs should be a variable, or indexed array or object");
}