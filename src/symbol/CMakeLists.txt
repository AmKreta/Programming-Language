add_library(symbol STATIC symbol.cpp symbolFactory.cpp symbolTable.cpp symbolTableBuilder.cpp)
target_include_directories(symbol PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)