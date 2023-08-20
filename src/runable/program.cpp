#include <runable/program.hpp>
#include <visitor/visitor.hpp>

Program::Program(std::vector<std::shared_ptr<Statement>> statement_list) : statement_list(statement_list) {}

std::vector<std::shared_ptr<Statement>> Program::getStatementList()
{
    return this->statement_list;
}

void Program::acceptVisitor(Visitor *visitor)
{
    visitor->visitProgram(this);
}