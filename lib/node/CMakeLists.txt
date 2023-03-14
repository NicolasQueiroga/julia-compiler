add_library(binop ${CMAKE_CURRENT_SOURCE_DIR}/binop/binop.cpp)
target_include_directories(binop PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(intval ${CMAKE_CURRENT_SOURCE_DIR}/intval/intval.cpp)
target_include_directories(intval PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(unop ${CMAKE_CURRENT_SOURCE_DIR}/unop/unop.cpp)
target_include_directories(unop PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(noop ${CMAKE_CURRENT_SOURCE_DIR}/noop/noop.cpp)
target_include_directories(noop PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})