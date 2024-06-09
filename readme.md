# Token Programming Language

**Docs** -> *https://token-programming-language.netlify.app/*

## How to run ?

 - clone the repo 
 - install cmake 
 - run mkdir build 
 - run cd build 
 - run cmake ../ 
 - run make 
 - run ./main
 
 Project structure
 -
- docs :- contains docs, written using angular framework
- include :- contain header files
- src:- contain defination of header files

Terminology
-

- **astNode** - parent class for all kind of nodes of ast tree
- **bootstrap** - a set of predefined function that can be called inside programming language, like       array.map, string.concat etc
- **callstack** - keeps track of current function and which node of symbol tree should be referenced as lookup table
- **evaluable** - something that can be evaluated like a expression
- **exception** - A class inherited from std::exception, to log customized error messages
- **interpreter** :- traverse through ast (using visitor pattern) and symbol tree, pushes/ pops new scopes in and out of callstack.
- **lexer** - used for tokenization of the the input.
- **modules** - a set of predefined functionalities, similar to js having console.log
- **operations** - kind of operations to be performed on nodes, like mathemetical, logical, boolean, ternary etc
- **parser** :- a traverse through token produced by lexer, do syntax analysis, and creates abstract syntax tree.
-  **rVal** - const values that can be assigned to a variable, eg array, number, functionExpression
- **runable** - something that can be run and which does something like a function call
- **symbol** - element of a symbol tree node, ie a var of a function or a class declared in program is stored as symbol in symbol tree
- **token** :- a token is a sequence of characters that are grouped into a single entity and represent a specific meaning
- **utility** :- helper function for bootstrap functions
- **visitor** :- a class based on visitor pattern used as base class for interpreter and symbolTreeBuilder

