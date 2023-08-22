#include <iostream>
#include <token/token.hpp>
#include <lexer/lexer.hpp>
#include <interpreter/interpreter.hpp>
#include <symbol/symbolFactory.hpp>

void run(std::string input)
{
    Lexer lexer{input};
    Parser parser{lexer};
    Interpreter interpreter{parser};
    std::cout << std::endl
              << input
              << " ";
    interpreter.interpret();
    std::cout << std::endl;
}

void printTokens(std::string input)
{
    Lexer lexer{input};
    for (auto token = lexer.getNextToken(); token.getTokenType() != Token::Type::END_OF_FILE; token = lexer.getNextToken())
        std::cout << token << std::endl;
}

int main()
{
    // run one at a time
    // run(let a = "'Hello' + ' ' + 'world';");
    // run("let a = (5 ** ( 2 + 1 ) ) / ( 200 - 25 * 3 );");
    // run("let a = +\"123\";");
    // run("let a= -'123';");
    // run("let a = [1+2, 2**10, 3, \"Hello world\", [4], [5, 6, 'I am AMK']];");
    // run("let a = {'a':1, 2:3, [1]:'hello'};");
    // run("let a = true || false;");
    // run("let a = false || false;");
    // run("let a = !(8 >= 5 + 3);");
    // run("let a = !(8 > 5 + 3);");
    // run("let a = 2 | 3;");
    // run("let a = 2 << 3 + 5;");
    // run("let a = 5 == 2 + 3 ? true ? 'this is true' : 'this is false' : false;");
    // run("if(true){ let a = 5; } else { let b = 10; }");
    // run("if(false){ let a = 5; } else { let b = 10; }");
    run("let a = [1, 2.4, 'hello'], b = { a : 'this is object a'}, c = b[a];");
    std::cout << std::endl;
    return 0;
}