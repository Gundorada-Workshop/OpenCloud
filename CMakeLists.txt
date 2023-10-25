cmake_minimum_required(VERSION 3.20)

PROJECT(OpenCloud)

# include our default build config
include(.cmake/ProjectConfiguration.cmake)

# add external libraries
add_subdirectory("external")

# add the main code directory
add_subdirectory("code")
