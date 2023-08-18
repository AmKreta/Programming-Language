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
              << input << " ----------> "
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
    run("'Hello' + ' ' + 'world'");
    run("(5 ** ( 2 + 1 ) ) / ( 200 - 25 * 3 )");
    run("+\"123\"");
    run("-'123'");
    run("[1+2, 2**10, 3, \"Hello world\", [4], [5, 6, 'I am AMK']]");
    run("{'a':1, 2:3, [1]:'hello'}");
    run("true || false");
    run("false || false");
    run("true && true");
    run("5 == 5");
    run("8 >= 5+3");
    run("!(8 >= 5 + 3)");
    run("!(8 > 5 + 3)");
    run("2 | 3");
    run("2 << 3 + 5");
    run("5 == 2 + 3 ? true ? 'this is true' : 'this is false' : false");
    std::cout << std::endl;
    return 0;
}