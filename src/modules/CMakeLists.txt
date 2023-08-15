add_library(modules STATIC console.cpp)
target_include_directories(modules PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)