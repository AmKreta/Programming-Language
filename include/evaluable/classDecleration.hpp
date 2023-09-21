#pragma once
#include <evaluable/evaluable.hpp>
#include <evaluable/function.hpp>
#include <rVal/rVal.hpp>
#include <symbol/symbolTable.hpp>

class ClassDecleration : public Evaluable, public std::enable_shared_from_this<ClassDecleration>
{
private:
    std::string name;
    std::unordered_map<std::string, std::shared_ptr<Function>> members;
    std::shared_ptr<SymbolTable> corospondingSymbolTable;

public:
    ClassDecleration(std::string, std::unordered_map<std::string, std::shared_ptr<Function>>);
    std::string getName();
    std::unordered_map<std::string, std::shared_ptr<Function>>& getMembers();
    std::shared_ptr<RVal> acceptVisitor(Visitor *);
    std::shared_ptr<ClassDecleration> getSharedPtr();
    std::shared_ptr<SymbolTable> getCorospondingSymbolTable();
    void setCorospondingSymbolTable(std::shared_ptr<SymbolTable>);
};