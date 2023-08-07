add_library(lexer STATIC lexer.cpp)
target_include_directories(lexer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../include)