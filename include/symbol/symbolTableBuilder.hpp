#pragma once

#include <visitor/visitor.hpp>
#include <parser/parser.hpp>
#include <symbol/symbolTable.hpp>
#include <runable/runable.hpp>

class SymbolTableBuilder : public Visitor
{
private:
    std::shared_ptr<AstNode> ast;
    std::shared_ptr<SymbolTable> rootSymbolTable, currentSymbolTable;

public:
    SymbolTableBuilder(Parser);
    SymbolTableBuilder(std::shared_ptr<AstNode>, std::shared_ptr<SymbolTable>);
    void pushScope(bool isLoop = false); // add a new scope
    void popScope();                     // removes a scope
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
    std::shared_ptr<RVal> visitNew(New*) override;
    std::shared_ptr<RVal> visitBridgeFnExpr(BridgeFnExpr*) override;
    void visitVarDecleration(VarDecleration *) override;
    void visitIfElse(IfElse *) override;
    void visitProgram(Program *) override;
    void visitCompoundStatement(CompoundStatement *) override;
    void visitExpressionStatement(ExpressionStatement *) override;
    void visitForLoop(ForLoop *) override;
    void visitWhileLoop(WhileLoop *) override;
    void visitReturn(Return *) override;
    void visitPrint(Print *) override;
    std::shared_ptr<SymbolTable> build();
    std::shared_ptr<SymbolTable> buildForFunction(std::shared_ptr<Function>);
    std::shared_ptr<SymbolTable> buildForClass(std::shared_ptr<ClassDecleration>);
    std::shared_ptr<RVal> resolveInstanceMember(DotOperator *);
};