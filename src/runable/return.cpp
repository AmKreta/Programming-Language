#include <runable/return.hpp>
#include <visitor/visitor.hpp>

Return::Return(std::shared_ptr<Evaluable> expr) : expr(expr) {}

void Return::acceptVisitor(Visitor *visitor)
{
    visitor->visitReturn(this);
}

 std::shared_ptr<Evaluable> Return::getExpr(){
    return this->expr;
 }