cmake_minimum_required(VERSION 3.10)
project(compilador VERSION 1.1.0)

set(CMAKE_CXX_STANDARD 20)
set(GCC_COVERAGE_COMPILE_FLAGS "-g -Og -Wall -pedantic")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(main src/main.cpp)

add_library(parser SHARED ${CMAKE_CURRENT_SOURCE_DIR}/lib/parser/parser.cpp)
add_library(token SHARED ${CMAKE_CURRENT_SOURCE_DIR}/lib/token/token.cpp)
add_library(tokenizer SHARED ${CMAKE_CURRENT_SOURCE_DIR}/lib/tokenizer/tokenizer.cpp)

target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_include_directories(token PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_include_directories(tokenizer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_link_libraries(tokenizer PUBLIC token)
target_link_libraries(parser PUBLIC tokenizer)
target_link_libraries(main PUBLIC parser)