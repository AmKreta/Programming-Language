#pragma once

#include <evaluable/evaluable.hpp>
#include <evaluable/variable.hpp>
#include <runable/compoundStatement.hpp>
// #include <symbol/symbolTable.hpp>

class SymbolTable;

class Function : public Evaluable, public std::enable_shared_from_this<Function>
{
private:
    std::vector<std::pair<std::shared_ptr<Variable>, std::shared_ptr<Evaluable>>> params;
    std::shared_ptr<CompoundStatement> compoundStatement;
    std::shared_ptr<RVal> returnVal;
    std::shared_ptr<SymbolTable> corospondingSymbolTable;
    std::string name;

public:
    Function(std::string, std::vector<std::pair<std::shared_ptr<Variable>, std::shared_ptr<Evaluable>>>, std::shared_ptr<CompoundStatement>);
    std::string getName();
    std::vector<std::pair<std::shared_ptr<Variable>, std::shared_ptr<Evaluable>>> getParams();
    std::shared_ptr<CompoundStatement> getCompoundStatement();
    std::shared_ptr<RVal> getReturnVal();
    void setCorospondingSymbolTable(std::shared_ptr<SymbolTable>);
    std::shared_ptr<SymbolTable> getCorospondingSymbolTable();
    std::shared_ptr<RVal> acceptVisitor(Visitor *) override;
    std::shared_ptr<Function> getSharedPtr();
};