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

##############################
# BUILD OPENCLOUD EXECUTABLE #
##############################
PROJECT(OpenCloudExe)

IF (WIN32)
    add_executable(${PROJECT_NAME} WIN32)
    SET(mainfunc host/winmain.cc)
ELSEIF(APPLE)
    message(FATAL_ERROR "Apple builds currently unsupported")
ELSEIF(UNIX AND NOT APPLE)
    add_executable(${PROJECT_NAME})
    SET(mainfunc host/linuxmain.cc)
ELSE()
    message(FATAL_ERROR "Unrecognised operating system")
ENDIF()


target_sources(
    ${PROJECT_NAME}
    PRIVATE
    ${mainfunc}
)

target_link_libraries(${PROJECT_NAME} PRIVATE ProjectConfiguration OpenCloudCommon OpenCloudEngine OpenCloudHost OpenCloudScript OpenCloudGraph)
