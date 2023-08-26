#include <callStack/callStack.hpp>

CallStack::CallStack(std::shared_ptr<SymbolTable> symbolTable) : scopes({std::make_shared<Scope>(symbolTable)}), activeScopeIndex(0) {}

void CallStack::pushScope()
{

    auto currentScope = this->scopes[this->scopes.size() - 1];
    auto corospondingST = currentScope->getCorospondingSymbolTable();
    auto children = corospondingST->getChildren();
    auto scope = std::make_shared<Scope>(children[this->childIndex]);
    this->scopes.push_back(scope);
}

void CallStack::popScope()
{
    // call this whenever you exit a scope
    // garbadge collect vars, functions declerations, class declerations here
    this->incrementChildIndex();
    this->scopes.pop_back();
}

void CallStack::skipScope()
{
    // in case you need to skip one child of current symbol table
    // eg if and else are two different scopes, but only one needs to execute
    // so one of them needs to be skipped
    // to keep Activation Record and corosponding symbol table in sync

    this->incrementChildIndex();
}

void CallStack::incrementChildIndex()
{
    auto scope = this->scopes[this->scopes.size() - 1];
    auto corospondingST = scope->getCorospondingSymbolTable();
    auto siblings =  corospondingST->getChildren(); // siblings of corosponding symbol table

    if (this->childIndex + 1 < siblings.size())
        // yet to visit all sibling
        this->childIndex++;

    else
        // ie all sibling scope has been covered
        this->childIndex = 0;
}