cmake_minimum_required(VERSION 3.10)
project(compilador VERSION 1.1.0)

set(CMAKE_CXX_STANDARD 20)
set(GCC_COVERAGE_COMPILE_FLAGS "-g -Og -Wall -pedantic -O3")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(main src/main.cpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_link_libraries(main PUBLIC parser assembler)