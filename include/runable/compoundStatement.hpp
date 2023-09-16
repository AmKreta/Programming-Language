#pragma once

#include <runable/runable.hpp>
#include <runable/statement.hpp>



class CompoundStatement : public Runable
{
private:
    std::vector<std::shared_ptr<Statement>> statementList;

public:
    CompoundStatement(std::vector<std::shared_ptr<Statement>>);
    std::vector<std::shared_ptr<Statement>>& getStatementList();
    void acceptVisitor(Visitor *) override;
};