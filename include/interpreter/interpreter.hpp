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
    Interpreter(Parser *, CallStack);
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
    std::shared_ptr<RVal> visitClassDecleration(ClassDecleration *) override;
    std::shared_ptr<RVal> visitInstance(Instance *) override;
    std::shared_ptr<RVal> visitDotOperator(DotOperator *) override;
    std::shared_ptr<RVal> visitNew(New *) override;
    std::shared_ptr<RVal> getClassMember();
    void visitVarDecleration(VarDecleration *) override;
    void visitIfElse(IfElse *) override;
    void visitProgram(Program *) override;
    void visitCompoundStatement(CompoundStatement *) override;
    void visitExpressionStatement(ExpressionStatement *) override;
    void visitForLoop(ForLoop *) override;
    void visitWhileLoop(WhileLoop *) override;
    void visitReturn(Return *) override;
    void visitPrint(Print *) override;
    CallStack &getCallStack();
    void interpret(std::vector<std::shared_ptr<Evaluable>> args = {});
    std::shared_ptr<RVal> resolveInstanceMember(DotOperator *, std::shared_ptr<Instance>);
    std::shared_ptr<RVal> dotOperatorAssignment(std::shared_ptr<DotOperator>, std::shared_ptr<RVal>);
    std::shared_ptr<RVal> updateInstanceMember(std::shared_ptr<DotOperator>, std::shared_ptr<Instance>, std::shared_ptr<RVal>);
};