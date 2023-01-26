cmake_minimum_required(VERSION 3.20)

project(OpenCloudGraph)

set(
    SOURCES
    "texture_pool.cc"
    "texture.cc"
)

set(
    HEADERS
    "matrix.h"
    "rectangle.h"
    "renderer.h"
    "texture_pool.h"
    "texture.h"
    "vector.h"
    "_vector/_vector_common.h"
    "_vector/_vector_cxp.h"
    "_vector/_vector_sse.h"
)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE ProjectConfiguration OpenCloudCommon)
