cmake_minimum_required(VERSION 3.26.4)

project(pl)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE token)
target_link_libraries(main PRIVATE lexer)
target_link_libraries(main PRIVATE rValConst)
target_link_libraries(main PRIVATE evaluable)

