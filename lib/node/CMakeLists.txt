add_library(binop ${CMAKE_CURRENT_SOURCE_DIR}/binop/binop.cpp)
target_include_directories(binop PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

add_library(intval ${CMAKE_CURRENT_SOURCE_DIR}/intval/intval.cpp)
target_include_directories(intval PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(unop ${CMAKE_CURRENT_SOURCE_DIR}/unop/unop.cpp)
target_include_directories(unop PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(noop ${CMAKE_CURRENT_SOURCE_DIR}/noop/noop.cpp)
target_include_directories(noop PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(assignment ${CMAKE_CURRENT_SOURCE_DIR}/assignment/assignment.cpp)
target_include_directories(assignment PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../symboltable)
target_link_libraries(assignment PUBLIC symboltable)

add_library(block ${CMAKE_CURRENT_SOURCE_DIR}/block/block.cpp)
target_include_directories(block PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(if ${CMAKE_CURRENT_SOURCE_DIR}/if/if.cpp)
target_include_directories(if PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(readline ${CMAKE_CURRENT_SOURCE_DIR}/readline/readline.cpp)
target_include_directories(readline PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(while ${CMAKE_CURRENT_SOURCE_DIR}/while/while.cpp)
target_include_directories(while PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(print ${CMAKE_CURRENT_SOURCE_DIR}/print/print.cpp)
target_include_directories(print PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

add_library(identifier ${CMAKE_CURRENT_SOURCE_DIR}/identifier/identifier.cpp)
target_include_directories(identifier PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../symboltable)
target_link_libraries(identifier PUBLIC symboltable)

add_library(strval ${CMAKE_CURRENT_SOURCE_DIR}/strval/strval.cpp)
target_include_directories(strval PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(vardec ${CMAKE_CURRENT_SOURCE_DIR}/vardec/vardec.cpp)
target_include_directories(vardec PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../symboltable ${CMAKE_CURRENT_SOURCE_DIR}/../../include)