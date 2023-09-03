#include <evaluable/function.hpp>
#include <visitor/visitor.hpp>

Function::Function(std::string name, std::vector<std::pair<std::shared_ptr<Variable>, std::shared_ptr<Evaluable>>> params, std::shared_ptr<CompoundStatement> compoundStatement) : name(name), params(params), compoundStatement(compoundStatement), returnVal(nullptr), corospondingSymbolTable(nullptr) {}

std::vector<std::pair<std::shared_ptr<Variable>, std::shared_ptr<Evaluable>>> Function::getParams()
{
    return this->params;
}

std::shared_ptr<CompoundStatement> Function::getCompoundStatement()
{
    return this->compoundStatement;
}

std::shared_ptr<Evaluable> Function::getReturnVal()
{
    return this->returnVal;
}

std::shared_ptr<RVal> Function::acceptVisitor(Visitor* visitor){
    return visitor->visitFunction(this);
}

std::string Function::getName(){
    return this->name;
}

void Function::setCorospondingSymbolable(std::shared_ptr<SymbolTable> corospondingSymbolTable){
    this->corospondingSymbolTable = corospondingSymbolTable;
}