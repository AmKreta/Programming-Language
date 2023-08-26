#include <symbol/symbolTableBuilder.hpp>
#include <symbol/varSymbol.hpp>

SymbolTableBuilder::SymbolTableBuilder(Parser parser) : parser(parser), rootSymbolTable(nullptr), currentSymbolTable(nullptr) {}

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
    auto res = this->currentSymbolTable->getVarSymbol(name);
    if (this->currentSymbolTable->getVarSymbolsMap().find(name) == this->currentSymbolTable->getVarSymbolsMap().end() &&
        res->getScopeLevel() != this->currentSymbolTable->getScopeLevel())
    {
        // ie it exists in enclosing scope
        // adding a refrence
        this->currentSymbolTable->addVarSymbol(name, res);
    }
    return nullptr;
}

// add vars to symbol table
void SymbolTableBuilder::visitVarDecleration(VarDecleration *varDecleration)
{
    auto declerations = varDecleration->getDeclerations();
    for (auto &[name, rVal] : declerations)
    {
        auto symbol = std::make_shared<VarSymbol>("instanceOf", this->currentSymbolTable->getScopeLevel());
        this->currentSymbolTable->addVarSymbol(name, symbol);
    }
}

// add a new scope here
void SymbolTableBuilder::visitIfElse(IfElse *ifElse)
{
    this->pushScope();
    auto condition = ifElse->getCondition()->acceptVisitor(this);
    ifElse->getIfBlock()->acceptVisitor(this);
    this->popScope();

    this->pushScope();
    ifElse->getElseBlock()->acceptVisitor(this);
    this->popScope();
}

// add a new scope here
void SymbolTableBuilder::visitForLoop(ForLoop *forLoop)
{
    this->pushScope();
    forLoop->getInitializations()->acceptVisitor(this);
    forLoop->getStatementList()->acceptVisitor(this);
    forLoop->getUpdates()->acceptVisitor(this);
    this->popScope();
}

// add a new scope here
void SymbolTableBuilder::visitWhileLoop(WhileLoop *whileLoop)
{
    this->pushScope();
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
    auto statementList = compoundStatement->getStatementList();
    for (auto statement : statementList)
        statement->acceptVisitor(this);
}

void SymbolTableBuilder::visitProgram(Program *program)
{
    // just traverse all the statements
    auto compoundStatement = program->getCompoundStatement();
    compoundStatement->acceptVisitor(this);
}

void SymbolTableBuilder::pushScope()
{
    auto symbolTableChild = std::make_shared<SymbolTable>(this->currentSymbolTable);
    this->currentSymbolTable->getChildren().push_back(symbolTableChild);
    this->currentSymbolTable = symbolTableChild;
}

void SymbolTableBuilder::popScope()
{
    this->currentSymbolTable = this->currentSymbolTable->getEnclosingScope();
}

std::shared_ptr<SymbolTable> SymbolTableBuilder::build()
{
    this->rootSymbolTable = std::make_shared<SymbolTable>();
    this->currentSymbolTable = this->rootSymbolTable;
    auto ast = parser.parse();
    ast->acceptVisitor(this);
    return this->rootSymbolTable;
}