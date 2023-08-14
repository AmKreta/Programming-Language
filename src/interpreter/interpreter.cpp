#include <interpreter/interpreter.hpp>
#include <exception/exceptionFactory.hpp>
#include <evaluable/rValueConstFactory.hpp>
#include <operations/mathemeticalOperation.hpp>

Interpreter::Interpreter(Parser parser) : parser(parser) {}

std::shared_ptr<RVal> Interpreter::visitRValConst(RVal *rValConst)
{
    return std::shared_ptr<RVal>{rValConst};
}

std::shared_ptr<RVal> Interpreter::visitArrayAst(ArrayAst *arrayAst)
{
    std::vector<std::shared_ptr<RVal>> arr;
    for (auto children : arrayAst->getChildren())
        arr.push_back(children->acceptVisitor(this));
    return std::make_shared<ArrayConst>(arr, RVal::Type::ARRAY);
}

std::shared_ptr<RVal> Interpreter::visitUnaryOperation(UnaryOperation *unaryOperation)
{
    auto child = unaryOperation->getChild() ? unaryOperation->getChild()->acceptVisitor(this) : nullptr;
    auto type = unaryOperation->getType();
    return MathemeticalExpression::evaluate(type, child);
}

std::shared_ptr<RVal> Interpreter::visitBinaryOperation(BinaryOperation *binaryOperation)
{
    auto left = binaryOperation->getLeftChild() ? binaryOperation->getLeftChild()->acceptVisitor(this) : nullptr;
    auto right = binaryOperation->getRightChild() ? binaryOperation->getRightChild()->acceptVisitor(this) : nullptr;
    auto op = binaryOperation->getOperation();
    return MathemeticalExpression::evaluate(left, op, right);
}

void Interpreter::interpret()
{
    auto eval = this->parser.parse();
    auto res = eval->acceptVisitor(this);
    if (res->getType() == RVal::Type::NUMBER)
    {
        auto num = std::dynamic_pointer_cast<NumberConst>(res);
        std::cout << num->getData() << std::endl;
    }
    if (res->getType() == RVal::Type::STRING)
    {
        auto num = std::dynamic_pointer_cast<StringConst>(res);
        std::cout << num->getData() << std::endl;
    }

    if (res->getType() == RVal::Type::ARRAY)
    {
        auto arr = std::dynamic_pointer_cast<ArrayConst>(res);
        std::cout<<"[";
        auto children = arr->getData();
        int size = children.size();
        for(int i=0;i<size;i++){
            auto child = children[i];
              if (child->getType() == RVal::Type::NUMBER)
            {
                auto num = std::dynamic_pointer_cast<NumberConst>(child);
                std::cout << num->getData();
            }
            else if (child->getType() == RVal::Type::STRING)
            {
                auto num = std::dynamic_pointer_cast<StringConst>(child);
                std::cout << num->getData();
            }

            if(i<size-1)
                std::cout<<", ";
        }
        std::cout<<"]";
    }
}