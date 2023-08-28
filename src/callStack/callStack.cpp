#include <callStack/callStack.hpp>

CallStack::CallStack(std::shared_ptr<SymbolTable> symbolTable) : scopes({std::make_shared<Scope>(symbolTable)}), activeScopeIndex(0) {}

void CallStack::pushScope()
{

    auto currentScope = this->scopes[this->scopes.size() - 1];
    auto corospondingST = currentScope->getCorospondingSymbolTable();
    auto &children = corospondingST->getChildren();
    auto scope = std::make_shared<Scope>(*children.begin());
    this->scopes.push_back(scope);
}

void CallStack::popScope()
{
    // call this whenever you exit a scope
    // garbadge collect vars, functions declerations, class declerations here
    auto scope = this->scopes[this->scopes.size() - 1];
    auto corospondingST = scope->getCorospondingSymbolTable();
    auto enclosingScope = corospondingST->getEnclosingScope();
    if (enclosingScope)
    {
        auto &siblings = enclosingScope->getChildren(); // siblings of corosponding symbol table
        siblings.pop_front();
    }
    this->scopes.pop_back();
}

void CallStack::skipScope()
{
    // in case you need to skip one child of current symbol table
    // eg if and else are two different scopes, but only one needs to execute
    // so one of them needs to be skipped
    // to keep Activation Record and corosponding symbol table in sync
    auto scope = this->scopes[this->scopes.size() - 1];
    auto corospondingST = scope->getCorospondingSymbolTable();
    auto &siblings =  corospondingST->getChildren();

    siblings.pop_front();
}

std::shared_ptr<Scope> CallStack::getActivationRecord()
{
    return this->scopes[this->scopes.size() - 1];
}

std::shared_ptr<Scope> CallStack::getGlobalScope()
{
    return this->scopes[0];
}

CallStack::~CallStack(){
    // destroying global scope
    this->scopes.pop_back();
}