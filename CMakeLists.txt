cmake_minimum_required(VERSION 3.20)

PROJECT(OpenCloud)

# include our default build config
include(.cmake/ProjectConfiguration.cmake)

# add external libraries
add_subdirectory("external")

add_subdirectory("generators")

# add the main code directory
add_subdirectory("code")

# Notes
# sudo apt install g++-10 : C++20 headers
# sudo ./cmake-3.25.1-linux-x86_64.sh --skip-license --exclude-subdir --prefix=/usr : install cmake from release script
