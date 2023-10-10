cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)

######################
# BUILD DEPENDENCIES #
######################
add_subdirectory("version")
add_subdirectory("common")
#add_subdirectory("script")
add_subdirectory("graph")
add_subdirectory("engine")
add_subdirectory("host")

##############################
# BUILD OPENCLOUD EXECUTABLE #
##############################
# Enable and IF-guard when host is ported
#SET(
#    SOURCES
#    "host/linuxmain.cc"
#)

#PROJECT(OpenCloudExe)
#add_executable(${PROJECT_NAME} ${SOURCES})

#find_package(X11 REQUIRED)
#target_link_libraries(${PROJECT_NAME} PRIVATE ${X11_LIBRARIES})
#target_include_directories(${PROJECT_NAME} PRIVATE ${X11_INCLUDE_DIR})

#find_package(OpenGL REQUIRED)
#target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::OpenGL OpenGL::GLX OpenGL::GLU)
#target_include_directories(${PROJECT_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})

# Puts the names of non-static functions into the link tables so the generated backtrace
# is actually readable
#IF (CMAKE_BUILD_TYPE MATCHES Debug)
#    IF (("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang") OR ("${CMAKE_CXX_COMPILER_ID}" #STREQUAL "GNU"))
#        target_link_options(${PROJECT_NAME} PRIVATE "-rdynamic")
#    ENDIF()
#ENDIF()
