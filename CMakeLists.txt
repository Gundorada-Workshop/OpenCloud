cmake_minimum_required(VERSION 3.20)

PROJECT(OpenCloud)

include(.cmake/ProjectConfiguration.cmake)

add_subdirectory("external")
add_subdirectory("code")
add_subdirectory("opencloud")