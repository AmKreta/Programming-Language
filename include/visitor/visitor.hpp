#pragma once

#include <evaluable/rValConst.hpp>
#include <evaluable/unaryOperation.hpp>
#include <evaluable/binaryOperation.hpp>
#include <evaluable/arrayAst.hpp>
#include <evaluable/mapAst.hpp>
#include <rVal/rVal.hpp>
#include <evaluable/conditionalOperator.hpp>
#include <evaluable/variable.hpp>
#include <evaluable/indexing.hpp>
#include <evaluable/function.hpp>
#include <evaluable/functionCall.hpp>
#include <evaluable/classDecleration.hpp>

#include <runable/program.hpp>
#include <runable/compoundStatement.hpp>
#include <runable/expressionStatement.hpp>
#include <runable/ifElse.hpp>
#include <runable/varDecleration.hpp>
#include <runable/forLoop.hpp>
#include <runable/whileLoop.hpp>
#include <runable/return.hpp>
#include <runable/print.hpp>

class Visitor
{
public:
    virtual std::shared_ptr<RVal> visitRValConst(RVal *) = 0;
    virtual std::shared_ptr<RVal> visitUnaryOperation(UnaryOperation *) = 0;
    virtual std::shared_ptr<RVal> visitBinaryOperation(BinaryOperation *) = 0;
    virtual std::shared_ptr<RVal> visitArrayAst(ArrayAst *) = 0;
    virtual std::shared_ptr<RVal> visitMapAst(MapAst *) = 0;
    virtual std::shared_ptr<RVal> visitVariable(Variable *) = 0;
    virtual std::shared_ptr<RVal> visitConditionalOperation(ConditionalOperation *) = 0;
    virtual std::shared_ptr<RVal> visitIndexing(Indexing *) = 0;
    virtual std::shared_ptr<RVal> visitFunction(Function *) = 0;
    virtual std::shared_ptr<RVal> visitFunctionCall(FunctionCall *) = 0;
    virtual std::shared_ptr<RVal> visitClassDecleration(ClassDecleration *) = 0;
    virtual void visitVarDecleration(VarDecleration *) = 0;
    virtual void visitIfElse(IfElse *) = 0;
    virtual void visitProgram(Program *) = 0;
    virtual void visitCompoundStatement(CompoundStatement *) = 0;
    virtual void visitExpressionStatement(ExpressionStatement *) = 0;
    virtual void visitForLoop(ForLoop *) = 0;
    virtual void visitWhileLoop(WhileLoop *) = 0;
    virtual void visitReturn(Return *) = 0;
    virtual void visitPrint(Print *) = 0;
    virtual ~Visitor() = default;
};