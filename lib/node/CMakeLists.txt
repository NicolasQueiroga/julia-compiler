add_library(binop ${CMAKE_CURRENT_SOURCE_DIR}/binop/binop.cpp)
target_include_directories(binop PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

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

add_library(identifier ${CMAKE_CURRENT_SOURCE_DIR}/identifier/identifier.cpp)
target_include_directories(identifier PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../symboltable)
target_link_libraries(identifier PUBLIC symboltable)

add_library(print ${CMAKE_CURRENT_SOURCE_DIR}/print/print.cpp)
target_include_directories(print PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})