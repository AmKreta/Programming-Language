add_library(exception STATIC exception.cpp exceptionFactory.cpp)
target_include_directories(exception PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)