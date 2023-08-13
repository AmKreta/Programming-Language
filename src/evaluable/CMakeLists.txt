add_library(evaluable STATIC unaryOperation.cpp binaryOperation.cpp rValConstFactory.cpp)
target_include_directories(evaluable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)