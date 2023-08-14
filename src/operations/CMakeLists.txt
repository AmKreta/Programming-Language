add_library(operation STATIC mathemeticalOperation.cpp)
target_include_directories(operation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)