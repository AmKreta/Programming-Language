#include<evaluable/functionCall.hpp>
#include<visitor/visitor.hpp>

FunctionCall::FunctionCall(std::shared_ptr<Evaluable> function, std::vector<std::shared_ptr<Evaluable>> arguments):function(function), arguments(arguments){}

std::vector<std::shared_ptr<Evaluable>> FunctionCall::getArgs(){
    return this->arguments;
}

std::shared_ptr<Evaluable> FunctionCall::getFunction(){
    return this->function;
}

std::shared_ptr<RVal> FunctionCall::acceptVisitor(Visitor *visitor){
    return visitor->visitFunctionCall(this);
}
