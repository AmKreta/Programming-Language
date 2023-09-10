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

std::shared_ptr<RVal> Function::getReturnVal()
{
    return this->returnVal;
}

std::shared_ptr<RVal> Function::acceptVisitor(Visitor *visitor)
{
    return visitor->visitFunction(this);
}

std::string Function::getName()
{
    return this->name;
}

void Function::setCorospondingSymbolTable(std::shared_ptr<SymbolTable> corospondingSymbolTable)
{
    this->corospondingSymbolTable = corospondingSymbolTable;
}

std::shared_ptr<SymbolTable> Function::getCorospondingSymbolTable()
{
    return this->corospondingSymbolTable;
}

std::shared_ptr<Function> Function::getSharedPtr()
{
    return this->shared_from_this();
}

void Function::setReturnVal(std::shared_ptr<RVal> val)
{
    this->returnVal = val;
}
