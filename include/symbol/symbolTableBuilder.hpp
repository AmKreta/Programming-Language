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
    SymbolTableBuilder(std::shared_ptr<AstNode>, std::shared_ptr<SymbolTable>);

public:
    SymbolTableBuilder(Parser);
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
    void visitVarDecleration(VarDecleration *) override;
    void visitIfElse(IfElse *) override;
    void visitProgram(Program *) override;
    void visitCompoundStatement(CompoundStatement *) override;
    void visitExpressionStatement(ExpressionStatement *) override;
    void visitForLoop(ForLoop *) override;
    void visitWhileLoop(WhileLoop *) override;
    std::shared_ptr<SymbolTable> build();
    std::shared_ptr<SymbolTable> buildForFunction(Function *);
};