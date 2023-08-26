#pragma once

#include <scope/scope.hpp>

class CallStack
{
private:
    std::vector<std::shared_ptr<Scope>> scopes;
    int activeScopeIndex; // index of active scope
    int childIndex = 0;
public:
    CallStack(std::shared_ptr<SymbolTable>);
    void pushScope();
    void popScope();                         // on pop increment currentSymbolTableChild
    void skipCurrentSymbokTableChildIndex(); // in case of if-else only one of the scope is executed
    void incrementChildIndex();
};
