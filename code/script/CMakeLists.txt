cmake_minimum_required(VERSION 3.20)

project(OpenCloudScript)
add_library(${PROJECT_NAME} STATIC)

target_sources(
    ${PROJECT_NAME}
    PRIVATE
    "analyzer.cc"
    
    "analyzer.h"
    "bytecode.h"
    "file.h"
    "stack.h"
)

target_link_libraries(${PROJECT_NAME} PRIVATE ProjectConfiguration)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
endif()
