#include <runable/compoundStatement.hpp>
#include <visitor/visitor.hpp>


CompoundStatement::CompoundStatement(std::vector<std::shared_ptr<Statement>> statementList) : statementList(statementList) {}

std::vector<std::shared_ptr<Statement>> CompoundStatement::getStatementList()
{
    return this->statementList;
}

void CompoundStatement::acceptVisitor(Visitor *visitor)
{
    visitor->visitCompoundStatement(this);
}