#pragma once

#include <visitor/visitor.hpp>
#include <parser/parser.hpp>

class Interpreter : public Visitor
{
private:
    Parser parser;

public:
    Interpreter(Parser);
    std::shared_ptr<RVal> visitRValConst(RVal *) override;
    std::shared_ptr<RVal> visitUnaryOperation(UnaryOperation *) override;
    std::shared_ptr<RVal> visitBinaryOperation(BinaryOperation *) override;
    std::shared_ptr<RVal> visitArrayAst(ArrayAst *) override;
    std::shared_ptr<RVal> visitMapAst(MapAst *) override;
    std::shared_ptr<RVal> visitConditionalOperation(ConditionalOperation *) override;
    std::shared_ptr<RVal> visitVariable(Variable *) override;
    void visitVarDecleration(VarDecleration *) override;
    void visitProgram(Program *) override;
    void interpret();
};