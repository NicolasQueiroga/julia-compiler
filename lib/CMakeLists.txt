add_library(token ${CMAKE_CURRENT_SOURCE_DIR}/token/token.cpp)
target_include_directories(token PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(tokenizer ${CMAKE_CURRENT_SOURCE_DIR}/tokenizer/tokenizer.cpp)
target_include_directories(tokenizer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_library(parser ${CMAKE_CURRENT_SOURCE_DIR}/parser/parser.cpp)
target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_library(prepro ${CMAKE_CURRENT_SOURCE_DIR}/prepro/prepro.cpp)
target_include_directories(prepro PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(symboltable ${CMAKE_CURRENT_SOURCE_DIR}/symboltable/symboltable.cpp)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/node)

target_link_libraries(tokenizer PUBLIC token)
target_link_libraries(parser PUBLIC tokenizer prepro binop intval unop noop block identifier assignment print)