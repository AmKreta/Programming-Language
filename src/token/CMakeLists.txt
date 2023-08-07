add_library(token STATIC token.cpp tokenFactory.cpp)
target_include_directories(token PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)