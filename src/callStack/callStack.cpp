#include <callStack/callStack.hpp>

CallStack::CallStack(std::shared_ptr<SymbolTable> symbolTable) : scopes({std::make_shared<Scope>(symbolTable)}), activeScopeIndex(0) {}

void CallStack::pushScope()
{
    auto currentScope = this->scopes[this->activeScopeIndex];
    auto corospondingST = currentScope->getCorospondingSymbolTable()->getChildren()[childIndex];
    auto scope = std::make_shared<Scope>(corospondingST);
    this->scopes.push_back(scope);
    this->activeScopeIndex = corospondingST->getScopeLevel();
}

void CallStack::popScope()
{
    // call this whenever you exit a scope
    // garbadge collect vars, functions declerations, class declerations here
    this->incrementChildIndex();
    this->scopes.pop_back();
    auto activeScope = this->scopes.at(-1);
    this->activeScopeIndex = activeScope->getCorospondingSymbolTable()->getScopeLevel();
}

void CallStack::skipCurrentSymbokTableChildIndex()
{
    // in case you need to skip one child of current symbol table
    // eg if and else are two different scopes, but only one needs to execute
    // so one of them needs to be skipped
    // to keep Activation Record and corosponding symbol table in sync

    auto scope = this->scopes.at(-1);
    auto corospondingST = scope->getCorospondingSymbolTable();
    auto enclosingST = corospondingST->getEnclosingScope();
    auto siblings = enclosingST->getChildren(); // siblings of corosponding symbol table

    if (this->childIndex + 1 == siblings.size())
    {
        // ie all sibling scope has been covered
        this->childIndex = 0;
        this->popScope();
    }
    else
        // yet to visit all sibling
        this->childIndex++;
}

void CallStack::incrementChildIndex()
{
    auto scope = this->scopes.at(-1);
    auto corospondingST = scope->getCorospondingSymbolTable();
    auto enclosingST = corospondingST->getEnclosingScope();
    auto siblings = enclosingST->getChildren(); // siblings of corosponding symbol table

    if (this->childIndex + 1 == siblings.size())
        // ie all sibling scope has been covered
        this->childIndex = 0;
    else
        // yet to visit all sibling
        this->childIndex++;
}