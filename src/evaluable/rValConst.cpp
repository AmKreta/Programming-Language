#include <evaluable/rValConst.hpp>
#include <visitor/visitor.hpp>

// template <typename T>
// std::shared_ptr<RVal> RValConst<T>::acceptVisitor(Visitor *visitor)
// {
//     return visitor->visit(this);
// }

std::shared_ptr<RVal> visitorFn(Visitor *visitor, RVal* rVal){
    return visitor->visitRValConst(rVal);
}