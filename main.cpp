#include <iostream>
#include <token/token.hpp>
#include <lexer/lexer.hpp>

int main()
{
    std::string input{" let a:number = 10;\n\
    if(a==10)\n\
        return 20;\n\
    for(let i:number=0; i<10;i++){\n\
        ley y:string = 'Amk is the best';\n\
        y=i;\n\
    }\n\
    "};

    Lexer lexer{input};

    for (auto a = lexer.getNextToken(); a.getTokenType() != Token::Type::END_OF_FILE; a = lexer.getNextToken())
    {
        std::cout << a<<std::endl;
    }

    return 0;
}