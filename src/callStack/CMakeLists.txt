add_library(callStack STATIC callStack.cpp)
target_include_directories(callStack PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)