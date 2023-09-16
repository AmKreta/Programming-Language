#include <symbol/symbolTableBuilder.hpp>
#include <modules/console.hpp>
#include <evaluable/rValueConstFactory.hpp>
#include <exception/exceptionFactory.hpp>
#include <symbol/symbolFactory.hpp>

SymbolTableBuilder::SymbolTableBuilder(Parser parser) : ast(parser.parse()), rootSymbolTable(nullptr), currentSymbolTable(nullptr) {}

SymbolTableBuilder::SymbolTableBuilder(std::shared_ptr<AstNode> ast, std::shared_ptr<SymbolTable> rootSymbolTable) : ast(ast), rootSymbolTable(rootSymbolTable), currentSymbolTable(rootSymbolTable) {}

std::shared_ptr<RVal> SymbolTableBuilder::visitRValConst(RVal *rValConst)
{
    return nullptr;
}

std::shared_ptr<RVal> SymbolTableBuilder::visitArrayAst(ArrayAst *arrayAst)
{
    RValPointerArray arr;
    for (auto children : arrayAst->getChildren())
        arr.push_back(children->acceptVisitor(this));
    return nullptr;
}

std::shared_ptr<RVal> SymbolTableBuilder::visitMapAst(MapAst *mapAst)
{
    RValPointerMap map;
    for (auto &[key, val] : mapAst->getEntries())
        map.insert(std::pair(key->acceptVisitor(this), val->acceptVisitor(this)));
    return nullptr;
}

std::shared_ptr<RVal> SymbolTableBuilder::visitUnaryOperation(UnaryOperation *unaryOperation)
{
    auto child = unaryOperation->getChild() ? unaryOperation->getChild()->acceptVisitor(this) : nullptr;
    return nullptr;
}

std::shared_ptr<RVal> SymbolTableBuilder::visitBinaryOperation(BinaryOperation *binaryOperation)
{
    auto op = binaryOperation->getOperation();
    auto left = binaryOperation->getLeftChild() ? binaryOperation->getLeftChild()->acceptVisitor(this) : nullptr;
    auto right = binaryOperation->getRightChild() ? binaryOperation->getRightChild()->acceptVisitor(this) : nullptr;
    return nullptr;
}

std::shared_ptr<RVal> SymbolTableBuilder::visitConditionalOperation(ConditionalOperation *conditionalOperation)
{
    auto condition = conditionalOperation->getCondition()->acceptVisitor(this);
    conditionalOperation->get_if()->acceptVisitor(this);
    conditionalOperation->get_else()->acceptVisitor(this);
    return nullptr;
}

std::shared_ptr<RVal> SymbolTableBuilder::visitIndexing(Indexing *indexing)
{
    auto val = indexing->getVal()->acceptVisitor(this);
    auto index = indexing->getIndex()->acceptVisitor(this);
    return nullptr;
}

// check if var exists in symbol table
std::shared_ptr<RVal> SymbolTableBuilder::visitVariable(Variable *variable)
{
    auto name = variable->getVarName();
    auto res = this->currentSymbolTable->getSymbol(name);
    if (this->currentSymbolTable->getSymbolsMap().find(name) == this->currentSymbolTable->getSymbolsMap().end() &&
        res->getScopeLevel() != this->currentSymbolTable->getScopeLevel())
    {
        // ie it exists in enclosing scope
        // adding a refrence
        this->currentSymbolTable->addSymbol(name, res);
    }
    return nullptr;
}

void SymbolTableBuilder::visitPrint(Print *print)
{
    auto &args = print->getArgs();
    for (auto arg : args)
        arg->acceptVisitor(this);
}

std::shared_ptr<RVal> SymbolTableBuilder::visitFunctionCall(FunctionCall *functionCall)
{
    auto fnConst = functionCall->getFunction()->acceptVisitor(this);
    return nullptr;
}

std::shared_ptr<RVal> SymbolTableBuilder::visitFunction(Function *function)
{
    auto fnConst = RValConstFactory::createFunctionConstSharedPtr(function->getSharedPtr());
    auto funSymbol = SymbolFactory::createFuncSymbol(this->currentSymbolTable->getScopeLevel(), fnConst);
    this->currentSymbolTable->addSymbol(function->getName(), funSymbol);
    // building symbol table for new execution context
    auto symbolTableBuilder = SymbolTableBuilder(function->getSharedPtr(), std::make_shared<SymbolTable>(this->currentSymbolTable));
    symbolTableBuilder.buildForFunction(function->getSharedPtr());
    return nullptr;
}

void SymbolTableBuilder::visitReturn(Return *ret)
{
    auto expr = ret->getExpr();
    expr->acceptVisitor(this);
}

// add vars to symbol table
void SymbolTableBuilder::visitVarDecleration(VarDecleration *varDecleration)
{
    auto &declerations = varDecleration->getDeclerations();
    for (auto &[name, rVal] : declerations)
    {
        auto symbol = SymbolFactory::createVarSymbol(this->currentSymbolTable->getScopeLevel());
        this->currentSymbolTable->addSymbol(name, symbol);
    }
}

// add a new scope here
void SymbolTableBuilder::visitIfElse(IfElse *ifElse)
{
    auto condition = ifElse->getCondition()->acceptVisitor(this);
    this->pushScope();
    ifElse->getIfBlock()->acceptVisitor(this);
    this->popScope();

    this->pushScope();
    ifElse->getElseBlock()->acceptVisitor(this);
    this->popScope();
}

// add a new scope here
void SymbolTableBuilder::visitForLoop(ForLoop *forLoop)
{
    this->pushScope(true);
    forLoop->getInitializations()->acceptVisitor(this);
    forLoop->getStatementList()->acceptVisitor(this);
    forLoop->getUpdates()->acceptVisitor(this);
    this->popScope();
}

// add a new scope here
void SymbolTableBuilder::visitWhileLoop(WhileLoop *whileLoop)
{
    this->pushScope(true);
    whileLoop->getCondition()->acceptVisitor(this);
    whileLoop->getCompoundStatement()->acceptVisitor(this);
    this->popScope();
}

void SymbolTableBuilder::visitExpressionStatement(ExpressionStatement *expressionStatement)
{
    auto expr = expressionStatement->getExpression();
    expr->acceptVisitor(this);
}

void SymbolTableBuilder::visitCompoundStatement(CompoundStatement *compoundStatement)
{
    auto &statementList = compoundStatement->getStatementList();
    for (auto statement : statementList)
        statement->acceptVisitor(this);
}

void SymbolTableBuilder::visitProgram(Program *program)
{
    // just traverse all the statements
    auto compoundStatement = program->getCompoundStatement();
    compoundStatement->acceptVisitor(this);
}

void SymbolTableBuilder::pushScope(bool isLoop)
{
    auto symbolTableChild = std::make_shared<SymbolTable>(this->currentSymbolTable, !isLoop);
    this->currentSymbolTable->getChildren().push_back(symbolTableChild);
    this->currentSymbolTable = symbolTableChild;
}

void SymbolTableBuilder::popScope()
{
    this->currentSymbolTable = this->currentSymbolTable->getEnclosingScope();
}

std::shared_ptr<SymbolTable> SymbolTableBuilder::build()
{
    if (!rootSymbolTable)
    {
        this->rootSymbolTable = std::make_shared<SymbolTable>();
        this->currentSymbolTable = this->rootSymbolTable;
    }
    auto runable = std::dynamic_pointer_cast<Runable>(this->ast);
    if (runable)
    {
        runable->acceptVisitor(this);
        return this->rootSymbolTable;
    }
    auto evaluable = std::dynamic_pointer_cast<Evaluable>(this->ast);
    throw ExceptionFactory::create("while building symbol table got evaluble , expected runable");
}

std::shared_ptr<SymbolTable> SymbolTableBuilder::buildForFunction(std::shared_ptr<Function> function)
{
    function->setCorospondingSymbolTable(this->rootSymbolTable);
    auto &params = function->getParams();
    for (auto &[variable, expr] : params)
    {
        auto name = variable->getVarName();
        auto symbol = SymbolFactory::createVarSymbol(this->rootSymbolTable->getScopeLevel());
        this->currentSymbolTable->addSymbol(name, symbol);
    }
    auto statementList = function->getCompoundStatement();
    statementList->acceptVisitor(this);
    return this->rootSymbolTable;
}