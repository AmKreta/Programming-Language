#pragma once

#include<runable/compoundStatement.hpp>
#include<runable/runable.hpp>
#include<vector>

class Program : public Runable{
    private:
        std::shared_ptr<CompoundStatement> compoundStatement;
    public:
        Program(std::shared_ptr<CompoundStatement>);
        std::shared_ptr<CompoundStatement> getCompoundStatement();
        void acceptVisitor(Visitor*) override;
};