add_library(symbol STATIC symbol.cpp varSymbol.cpp)
target_include_directories(symbol PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)