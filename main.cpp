#include <iostream>
#include <token/token.hpp>
#include <lexer/lexer.hpp>
#include <interpreter/interpreter.hpp>
#include <symbol/symbolTableBuilder.hpp>
#include <callStack/callStack.hpp>

void run(std::string input)
{
    Lexer lexer{input};
    Parser parser{lexer};
    SymbolTableBuilder stb{parser};
    auto st = stb.build();
    // st->print();
    CallStack callStack{st};
    Interpreter interpreter{&parser, callStack};
    std::cout << std::endl
              << input
              << std::endl
              << std::endl;
    interpreter.interpret();
    std::cout << std::endl
              << std::endl;
    // std::cout << std::endl
    //           << "\ncontent of symbol table\n"
    //           << std::endl;
    // interpreter.getCallStack().getGlobalScope()->print();
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
    // run("'Hello' + ' ' + 'world';");
    // run("(5 ** ( 2 + 1 ) ) / ( 200 - 25 * 3 );");
    // run("+\"123\";");
    // run("let a= -'123';");
    // run("[1+2, 2**10, 3, \"Hello world\", [4], [5, 6, 'I am AMK']];");
    // run("{'a':1, 2:3, [1]:'hello'};");
    // run("true || false;");
    // run("false || false;");
    // run("!(8 >= 5 + 3);");
    // run("!(8 > 5 + 3);");
    // run("2 | 3;");
    // run("2 << 3 + 5;");
    // run("5 == 2 + 3 ? true ? 'this is true' : 'this is false' : false;");
    // run("if(true){ let a = 5; } else { let b = 10; }");
    // run("if(false){ let a = 5; } else { let b = 10; }");
    // run("let a = 11;\n\nlet message = a % 2 == 1\n  ? ['the no. is even']\n  : {'res' : 'the no. is odd'};\n\nlet c;\nif (message[0] == 'the no. is even')\n  {c = message[0]; let d = 5;}\nelse\n  {c = message['res']; let f='amk';}");
    // run("let a = ['Amk']; let b = a[0] == 'Amk';");
    // run("let i=0;\nlet j=1;\nfor(; j <= 4; j = j+1 ){\n  i = i*10 + j;\n}");
    // run("let i=0;");
    // run("let a = [1, 2, 3, 4, 5];\na[0] = {'name':'Amresh'};\na[0]['name'] = 'Amk';\nlet b;\nb = {'Foo':'Baar'};\nb['Foo'] = 'Foo What ?';");
    // run("let a=0; if(a==0) a=5; if(a==4){ a = a+3;} else { a = a+8;}");
    // run("let a = 0, b=0;\nwhile(a<2){\n  let c = 0; \n  while(c<2){\n    b = b+1;\n    c = c+1;\n  }\n  while(c<4){\n    b = b+1;\n    c = c+1;\n  }\n  a=a+1;\n}");
    // run("if(true)if(true){}else if(true){} else{}");
    // run("let a=0; function amk(){ let b=0; while(b<10){ a=a+10; b=b+1;} } amk();");
    //run("let b=0;\nlet fn = function(){\n  let c = 100;\n  return function(){\n    return c;\n  };\n};\nb = fn()();\nprint('value of b is ', b);");
    //run("print('Amk is great !')");
    // run("for(let i=0;i<10;i=i+1){\n  for(let j=0;j<=i;j=j+1){\n    print('*');\n  }\n  for(let j=i+1;j<20-i;j=j+1){\n    print(' ');\n  }\n  for(let j=0;j<=i;j=j+1){\n    print('*');\n  }\n  print('\n');}");
    // run("function heart(){\n\
    //         let size=10;\n\
    //         for(let i=0;i<5;i=i+1){\n\
    //             for(let s=5;s>=i;s=s-1)\n\
    //                 print(' ');\n\
    //             print('*');\n\
    //             for(let s=0;s<i;s=s+1)\n\
    //                 print('  ');\n\
    //             print('*');\n\
    //             for(let s=5-i+2;s>=i;s=s-1)\n\
    //                 print(' ');\n\
    //             print('*');\n\
    //             for(let s=0;s<i;s=s+1)\n\
    //                 print('  ');\n\
    //             print('*');\n\
    //             print('\n');\n\
    //         }\n\
    //     }\n\
    //     heart();\n\
    //     for(let i=0;i<=10;i = i+1){\n\
    //         for(let s=0;s<=i;s=s+1)\n\
    //             print(' ');\n\
    //         print('*');\n\
    //         for(let s=i;s<20-i;s=s+1)\n\
    //             print(' ');\n\
    //         print('*');\n\
    //         print('\n');\n\
    //     }");
    std::cout << std::endl;
    return 0;
}