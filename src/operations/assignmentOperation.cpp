#include <operations/assignmentOperation.hpp>
#include <exception/exceptionFactory.hpp>

std::shared_ptr<RVal> AssignmentOperation::evaluate(Visitor *visitor, std::shared_ptr<Evaluable> lhs, std::shared_ptr<Evaluable> rhs, std::shared_ptr<Scope> activationRecord)
{
    auto res = rhs->acceptVisitor(visitor);

    auto var = std::dynamic_pointer_cast<Variable>(lhs);
    if (var)
    {
        activationRecord->setVar(var->getVarName(), res);
        return res;
    }

    auto indexing = std::dynamic_pointer_cast<Indexing>(lhs);
    if (indexing)
    {
        auto val = indexing->getVal();
        auto index = indexing->getIndex()->acceptVisitor(visitor);
        auto rVal = val->acceptVisitor(visitor);
        if (rVal->getType() == RVal::Type::ARRAY && index->getType() == RVal::Type::NUMBER)
        {

            auto &arr = std::dynamic_pointer_cast<ArrayConst>(rVal)->getData();
            auto idx = std::dynamic_pointer_cast<NumberConst>(index)->getData();
            return arr[idx] = res;
        }
        if (rVal->getType() == RVal::Type::MAP)
        {
            auto &map = std::dynamic_pointer_cast<MapConst>(rVal)->getData();
            return map[index] = res;
        }
    }

    throw ExceptionFactory::create("lhs should be a variable, or indexed array or object");
}