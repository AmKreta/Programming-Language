add_library(runable STATIC statement.cpp varDecleration.cpp program.cpp)
target_include_directories(runable PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../include)