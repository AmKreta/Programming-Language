#pragma once

#include<statement/statement.hpp>
#include<runable/runable.hpp>
#include<vector>

class Program : public Runable{
    private:
        std::vector<std::shared_ptr<Statement>> statement_list;
    public:
        Program(std::vector<std::shared_ptr<Statement>>);
        std::vector<std::shared_ptr<Statement>> getStatementList();
        void acceptVisitor(Visitor*) override;
};