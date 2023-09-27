export const ScopesTypes = [
    {
        title: 'Global Scope',
        defination: "Variables declared outside of any function or code block have a global scope. They can be accessed from anywhere in the program. However, it's considered good practice to minimize the use of global variables to avoid unintended side effects."
    },
    {
        title: 'Local Scope',
        defination: 'Variables declared within a function or code block have local scope. They are accessible only within that specific function or block. Local variables are often used to store temporary data or function parameters.'
    },
    {
        title: "Function Scope",
        defination: "In many programming languages, each function creates its own scope. Variables declared inside a function are limited to that function's scope and are not accessible from outside."
    },
    {
        title: "Lexical Scope",
        defination: "Lexical scope, also known as static scope, is a scope determined by the physical structure of the code. It means that the scope of a variable is determined by where it is declared in the source code, not where it is called or executed."
    },
    {
        title: "Shadowing",
        defination: "Shadowing occurs when a variable declared in an inner scope has the same name as a variable in an outer scope. In such cases, the inner variable 'shadows' the outer one, making the outer variable temporarily inaccessible within the inner scope."
    }
]