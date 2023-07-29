cmake_minimum_required(VERSION 3.20)

PROJECT(OpenCloud)

include(.cmake/ProjectConfiguration.cmake)

add_subdirectory("external/fmt")
add_subdirectory("external/simdjson")

add_subdirectory("code")

# Notes
# sudo apt install g++-10 : C++20 headers
# sudo ./cmake-3.25.1-linux-x86_64.sh --skip-license --exclude-subdir --prefix=/usr : install cmake from release script
