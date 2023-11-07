cmake_minimum_required(VERSION 3.26.4)

project(pl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_TOOLCHAIN_FILE /Users/amreshkumar/Desktop/emscripten/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s NO_DISABLE_EXCEPTION_CATCHING")

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
target_link_libraries(main PRIVATE bootstrap)

set_target_properties(main PROPERTIES LINK_FLAGS "--bind -s EXPORTED_RUNTIME_METHODS='[\"run\"]'")
set_target_properties(main PROPERTIES COMPILE_FLAGS "-s ALLOW_MEMORY_GROWTH=1 -s MODULARIZE=1")
target_compile_options(main PRIVATE -DJS_ONLY=ON)
target_compile_options(main PRIVATE -s WASM=1)
target_compile_options(main PRIVATE -O3)