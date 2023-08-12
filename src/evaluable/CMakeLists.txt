add_library(evaluable STATIC numberConst.cpp unaryOperation.cpp binaryOperation.cpp)
target_include_directories(evaluable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)