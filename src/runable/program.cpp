#include <runable/program.hpp>
#include <visitor/visitor.hpp>

Program::Program(std::shared_ptr<CompoundStatement> compoundStatement) : compoundStatement(compoundStatement) {}

std::shared_ptr<CompoundStatement> Program::getCompoundStatement()
{
    return this->compoundStatement;
}

void Program::acceptVisitor(Visitor *visitor)
{
    visitor->visitProgram(this);
}