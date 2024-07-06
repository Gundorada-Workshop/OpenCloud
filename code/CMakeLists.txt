cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)

######################
# BUILD DEPENDENCIES #
######################
add_subdirectory("version")
add_subdirectory("common")
add_subdirectory("data")
add_subdirectory("script")
add_subdirectory("graph")
add_subdirectory("engine")
add_subdirectory("host")
