#include <iostream>
#include <token/token.hpp>
#include <lexer/lexer.hpp>
#include <interpreter/interpreter.hpp>
#include <symbol/symbolFactory.hpp>

void run(std::string input){
    Lexer lexer{input};
    Parser parser{lexer};
    Interpreter interpreter{parser};
    std::cout<<std::endl<<input<<" ----------> "<<" ";
    interpreter.interpret();
    std::cout<<std::endl;
}

int main()
{
    run("'Hello' + ' ' + 'world'");
    run("(5 ** ( 2 + 1 ) ) / ( 200 - 25 * 3 )");
    run("+\"123\"");
    run("-'123'");
    return 0;
}