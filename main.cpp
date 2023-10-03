#include <iostream>
#include <token/token.hpp>
#include <lexer/lexer.hpp>
#include <interpreter/interpreter.hpp>
#include <symbol/symbolTableBuilder.hpp>
#include <callStack/callStack.hpp>
#include <chrono>
#include <fstream>
#include <filesystem>
#include <bootstrap/bootstrap.hpp>

void run(std::string input)
{
    input = Bootstrap::bootstrapArray()+ Bootstrap::bootstrapMap() + Bootstrap::bootstrapString() + input;
    // std::cout << std::endl
    //           << input
    //           << std::endl
    //           << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    Lexer lexer{input};
    Parser parser{lexer};
    SymbolTableBuilder stb{parser};
    auto st = stb.build();
    //st->print();
    CallStack callStack{st};
    Interpreter interpreter{&parser, callStack};
    interpreter.interpret();
    std::cout << std::endl
              << std::endl;
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "executed successfully in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " millisecond ........" << std::endl
              << std::endl;
    // // std::cout << std::endl
    // //           << "\ncontent of symbol table\n"
    // //           << std::endl;
    // // interpreter.getCallStack().getGlobalScope()->print();
}

void printTokens(std::string input)
{
    Lexer lexer{input};
    for (auto token = lexer.getNextToken(); token.getTokenType() != Token::Type::END_OF_FILE; token = lexer.getNextToken())
        std::cout << token << std::endl;
}

int main()
{
    std::filesystem::path cwd = std::filesystem::current_path();
    std::fstream file;
    file.open(cwd / ".." / "program.txt", std::ios::in);
    if (!file)
        std::cout << "File not created!";
    else
    {
        std::string content((std::istreambuf_iterator<char>(file)),
                            (std::istreambuf_iterator<char>()));
        run(content);
        file.close();
    }
    return 0;
}