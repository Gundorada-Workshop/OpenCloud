cmake_minimum_required(VERSION 3.20)

PROJECT(OpenCloudHost)

add_library(${PROJECT_NAME} STATIC)

if (UNIX AND NOT APPLE)
    target_sources(
        ${PROJECT_NAME}
        PRIVATE
        "host_interface_base.cc"
        "host_interface_x11.cc"
        "linux_pad_handler.cc"
        
        "host_interface_base.h" 
        "host_interface_x11.h"
        "pad_handler.h"
        "linux_pad_handler.h"
    )

    find_package(X11 REQUIRED)
    target_include_directories(${PROJECT_NAME} PUBLIC ${X11_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${X11_LIBRARIES} PRIVATE ProjectConfiguration OpenCloudCommon OpenCloudGraph)
endif (UNIX AND NOT APPLE)
