add_library(parser STATIC 
parser.cpp 
assignmentParser.cpp 
bitwiseExpressionParser.cpp 
expressionParser.cpp 
factorExpressionParser.cpp 
logicalExpressionParser.cpp 
mathemeticalExpressionParser.cpp 
relationalExpression.cpp 
ternaryParser.cpp 
runable.cpp 
forLoopParser.cpp 
whileLoopParser.cpp
functionParser.cpp)
target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)