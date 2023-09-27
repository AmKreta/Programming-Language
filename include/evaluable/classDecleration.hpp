#pragma once
#include <evaluable/evaluable.hpp>
#include <evaluable/function.hpp>
#include <rVal/rVal.hpp>
#include <symbol/symbolTable.hpp>
#include <evaluable/rValueConstFactory.hpp>

class ClassDecleration : public Evaluable, public std::enable_shared_from_this<ClassDecleration>
{
private:
    std::string name;
    std::unordered_map<std::string, std::shared_ptr<Function>> members;
    std::unordered_map<std::string, std::shared_ptr<RVal>> dataMembers;
    std::shared_ptr<SymbolTable> corospondingSymbolTable;

public:
    ClassDecleration(std::string, std::unordered_map<std::string, std::shared_ptr<Function>>);
    std::string getName();
    std::unordered_map<std::string, std::shared_ptr<Function>> &getMembers();
    std::unordered_map<std::string, std::shared_ptr<RVal>> &getDataMembers();
    void setDataMember(std::string, std::shared_ptr<RVal> val = RValConstFactory::createUndefinedConstSharedPtr());
    std::shared_ptr<RVal> acceptVisitor(Visitor *);
    std::shared_ptr<ClassDecleration> getSharedPtr();
    std::shared_ptr<SymbolTable> getCorospondingSymbolTable();
    void setCorospondingSymbolTable(std::shared_ptr<SymbolTable>);
};