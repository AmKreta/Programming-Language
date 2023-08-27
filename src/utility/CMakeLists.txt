add_library(utility STATIC conversionFunctions.cpp toString.cpp)
target_include_directories(utility PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)