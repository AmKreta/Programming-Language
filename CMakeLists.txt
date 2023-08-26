cmake_minimum_required(VERSION 3.26.4)

project(pl)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE token)
target_link_libraries(main PRIVATE lexer)
target_link_libraries(main PRIVATE exception)
target_link_libraries(main PRIVATE rVal)
target_link_libraries(main PRIVATE evaluable)
target_link_libraries(main PRIVATE runable)
target_link_libraries(main PRIVATE parser)
target_link_libraries(main PRIVATE interpreter)
target_link_libraries(main PRIVATE symbol)
target_link_libraries(main PRIVATE operation)
target_link_libraries(main PRIVATE utility)
target_link_libraries(main PRIVATE modules)
target_link_libraries(main PRIVATE callStack)
target_link_libraries(main PRIVATE scope)
