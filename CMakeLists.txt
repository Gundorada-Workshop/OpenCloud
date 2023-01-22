cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)

PROJECT(OpenCloud)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native") # Enable SSE/AVX
add_subdirectory("external/fmt")
add_subdirectory("code")

# Notes
# sudo apt install g++-10 : C++20 headers
# sudo ./cmake-3.25.1-linux-x86_64.sh --skip-license --exclude-subdir --prefix=/usr : install cmake from release script
