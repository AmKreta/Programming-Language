#include <symbol/symbolTableBuilder.hpp>
#include <modules/console.hpp>
#include <evaluable/rValueConstFactory.hpp>
#include <exception/exceptionFactory.hpp>
#include <symbol/symbolFactory.hpp>
#include <typeinfo>

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
    auto symbols = this->currentSymbolTable->getSymbolsMap();
    auto hoistedSymbol = symbols.find(function->getName());
    if (hoistedSymbol != symbols.end() && hoistedSymbol->second == nullptr)
        this->currentSymbolTable->replaceSymbol(function->getName(), funSymbol);
    else
        this->currentSymbolTable->addSymbol(function->getName(), funSymbol);
    // building symbol table for new execution context
    auto symbolTableBuilder = SymbolTableBuilder(function->getSharedPtr(), std::make_shared<SymbolTable>(this->currentSymbolTable));
    symbolTableBuilder.buildForFunction(function->getSharedPtr());
    return nullptr;
}

std::shared_ptr<RVal> SymbolTableBuilder::visitClassDecleration(ClassDecleration *classDecleration)
{
    auto classDeclConst = RValConstFactory::createClassDeclerationConstSharedPtr(classDecleration->getSharedPtr());
    auto classSymbol = SymbolFactory::createClassSymbol(this->currentSymbolTable->getScopeLevel(), classDeclConst);
    this->currentSymbolTable->addSymbol(classDecleration->getName(), classSymbol);
    auto symbolTableBuilder = SymbolTableBuilder(classDecleration->getSharedPtr(), std::make_shared<SymbolTable>(this->currentSymbolTable));
    symbolTableBuilder.buildForClass(classDecleration->getSharedPtr());
    return nullptr;
}

std::shared_ptr<RVal> SymbolTableBuilder::visitInstance(Instance *instance)
{
    return nullptr;
}

std::shared_ptr<RVal> SymbolTableBuilder::visitBridgeFnExpr(BridgeFnExpr *bridgeFnExpr)
{
    return nullptr;
}

std::shared_ptr<RVal> SymbolTableBuilder::visitDotOperator(DotOperator *dotOperator)
{
    auto instanceExpr = dotOperator->getInstanceExpr()->acceptVisitor(this);
    // auto instanceConst = std::dynamic_pointer_cast<InstanceConst>(instanceExpr);
    //  if (!instanceConst)
    //      throw ExceptionFactory::create("dot operator can only be used with instances");
    //  auto instance = instanceConst->getData();
    //  auto classSymbol = instance->getClassSymbol();
    //  auto classDeclConst = std::dynamic_pointer_cast<ClassDeclerationConst>(classSymbol->getValue());
    //  auto classDecl = classDeclConst->getData();
    //  auto classSymbolTable = classDecl->getCorospondingSymbolTable();
    //  auto symbolTableBuilder = SymbolTableBuilder(classDecl, std::make_shared<SymbolTable>(this->currentSymbolTable));
    //  symbolTableBuilder.resolveInstanceMember(dotOperator);
    return nullptr;
}

std::shared_ptr<RVal> SymbolTableBuilder::visitNew(New *newObj)
{
    auto className = newObj->getClassName();
    this->currentSymbolTable->getSymbol(className);
    auto args = newObj->getArgs();
    for (auto arg : args)
        arg->acceptVisitor(this);
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

std::shared_ptr<SymbolTable> SymbolTableBuilder::buildForClass(std::shared_ptr<ClassDecleration> classDecleration)
{
    classDecleration->setCorospondingSymbolTable(this->rootSymbolTable);
    auto &members = classDecleration->getMembers();
    // adding all functions in scope
    for (auto [name, fn] : members)
        if (name != "constructor")
            this->rootSymbolTable->addSymbol(name, nullptr);

    // adding a temp instance
    auto className = classDecleration->getName();
    auto classSymbol = this->rootSymbolTable->getEnclosingScope()->getSymbol(className);
    auto tempInstance = std::make_shared<Instance>(classSymbol, classDecleration->getDataMembers());
    auto tempInstanceConst = RValConstFactory::createInstanceConstSharedPtr(tempInstance);
    this->rootSymbolTable->addSymbol("this", SymbolFactory::createVarSymbol(this->rootSymbolTable->getScopeLevel(), tempInstanceConst));

    // adding data members
    auto constructorFn = members.find("constructor");
    if (constructorFn != members.end())
    {
        // adding data members to symbol table
        auto constructor = constructorFn->second;
        auto statements = constructor->getCompoundStatement();
        auto statementList = statements->getStatementList();
        for (auto statement : statementList)
        {
            auto expressionStatement = std::dynamic_pointer_cast<ExpressionStatement>(statement);
            if (!expressionStatement)
                continue;
            auto expression = expressionStatement->getExpression();
            auto binaryOp = std::dynamic_pointer_cast<BinaryOperation>(expression);
            if (!binaryOp)
                continue;
            if (binaryOp->getOperation() != Token::Type::ASSIGNMENT)
                continue;
            auto leftChild = binaryOp->getLeftChild();
            auto dotOperator = std::dynamic_pointer_cast<DotOperator>(leftChild);
            if (!dotOperator)
                continue;
            auto instanceExpr = dotOperator->getInstanceExpr();
            auto var = std::dynamic_pointer_cast<Variable>(instanceExpr);
            auto instanceName = var->getVarName();
            if (instanceName != "this")
                continue;
            auto instanceMember = dotOperator->getMember();
            var = std::dynamic_pointer_cast<Variable>(instanceMember);
            if (!var)
                continue;
            auto memberName = var->getVarName();
            classDecleration->setDataMember(memberName);
        }
        constructor->acceptVisitor(this);
    }

    for (auto [name, fn] : members)
        if (name != "constructor")
            fn->acceptVisitor(this);
    return this->rootSymbolTable;
}

std::shared_ptr<RVal> SymbolTableBuilder::resolveInstanceMember(DotOperator *dotOperator)
{
    // only called with class symbol as root symbol table,
    // so this member is already present in root symbol table
    // or we get error if it's not present
    // auto member = dotOperator->getMember()->acceptVisitor(this);
    // return member;
    return nullptr;
}