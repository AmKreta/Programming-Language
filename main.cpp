#include <iostream>
#include <token/token.hpp>
#include <lexer/lexer.hpp>
#include <interpreter/interpreter.hpp>

int main()
{
    // std::string input{" let a = 10;\n\
    // if(a==10)\n\
    //     return 20;\n\
    // for(let i=0; i<10;i++){\n\
    //     ley y = 'Amk is the best';\n\
    //     y=i;\n\
    // }\n\
    // "};

    // Lexer lexer{input};

    // for (auto a = lexer.getNextToken(); a.getTokenType() != Token::Type::END_OF_FILE; a = lexer.getNextToken())
    // {
    //     std::cout << a<<std::endl;
    // }

    std::string input{"2+2*5+(7**2)/(2+5)"};
    Lexer lexer{input};
    Parser parser{lexer};
    Interpreter interpreter{parser};
    std::cout << interpreter.interpret() << std::endl;
    return 0;
}