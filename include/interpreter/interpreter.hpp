#pragma once

#include <visitor/visitor.hpp>
#include <parser/parser.hpp>
#include <callStack/callStack.hpp>
#include <astNode/astNode.hpp>
#include <evaluable/function.hpp>

class Interpreter : public Visitor
{
private:
    std::shared_ptr<AstNode> astNode;
    CallStack callStack;
    bool hasReturned;
public:
    Interpreter(Parser*, CallStack);
    Interpreter(std::shared_ptr<AstNode>, CallStack);
    std::shared_ptr<RVal> visitRValConst(RVal *) override;
    std::shared_ptr<RVal> visitUnaryOperation(UnaryOperation *) override;
    std::shared_ptr<RVal> visitBinaryOperation(BinaryOperation *) override;
    std::shared_ptr<RVal> visitArrayAst(ArrayAst *) override;
    std::shared_ptr<RVal> visitMapAst(MapAst *) override;
    std::shared_ptr<RVal> visitConditionalOperation(ConditionalOperation *) override;
    std::shared_ptr<RVal> visitIndexing(Indexing *) override;
    std::shared_ptr<RVal> visitVariable(Variable *) override;
    std::shared_ptr<RVal> visitFunction(Function *) override;
    std::shared_ptr<RVal> visitFunctionCall(FunctionCall *) override;
    void visitVarDecleration(VarDecleration *) override;
    void visitIfElse(IfElse *) override;
    void visitProgram(Program *) override;
    void visitCompoundStatement(CompoundStatement *) override;
    void visitExpressionStatement(ExpressionStatement *) override;
    void visitForLoop(ForLoop *) override;
    void visitWhileLoop(WhileLoop *) override;
    void visitReturn(Return*) override;
    void visitPrint(Print* ) override;
    CallStack &getCallStack();
    void interpret();
};