#include <iostream>
#include <token/token.hpp>
#include <lexer/lexer.hpp>
#include <interpreter/interpreter.hpp>
#include <symbol/symbolFactory.hpp>

int main()
{
    std::string input1{"'Hello' + ' ' + 'world'"};
    Lexer lexer1{input1};
    Parser parser1{lexer1};
    Interpreter interpreter1{parser1};
    std::cout<<std::endl<<input1<<" ----------> "<<" ";
    interpreter1.interpret();
    std::cout<<std::endl;

    std::string input2{"(5 ** ( 2 + 1 ) ) / ( 200 - 25 * 3 )"};
    Lexer lexer2{input2};
    Parser parser2{lexer2};
    Interpreter interpreter2{parser2};
    std::cout<<std::endl<<input2<<" ----------> "<<" ";
    interpreter2.interpret();
    std::cout<<std::endl;
    return 0;
}