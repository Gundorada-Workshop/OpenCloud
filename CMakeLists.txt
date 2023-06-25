cmake_minimum_required(VERSION 3.20)

PROJECT(OpenCloud)


add_library(ProjectConfiguration INTERFACE)

# global include directories
target_include_directories(ProjectConfiguration INTERFACE  "${PROJECT_SOURCE_DIR}/code")

# global features
target_compile_features(ProjectConfiguration INTERFACE cxx_std_23)

IF ((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=x86-64-v2 -mavx -mfma") # Enable SSE/AVX
ENDIF()
add_subdirectory("external/fmt")
add_subdirectory("external/simdjson")
add_subdirectory("code")

# Notes
# sudo apt install g++-10 : C++20 headers
# sudo ./cmake-3.25.1-linux-x86_64.sh --skip-license --exclude-subdir --prefix=/usr : install cmake from release script
