add_library(interpreter STATIC interpreter.cpp)
target_include_directories(interpreter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)