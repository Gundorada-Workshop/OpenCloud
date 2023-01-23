cmake_minimum_required(VERSION 3.20)

project(OpenCloudCommon)

add_library(${PROJECT_NAME} STATIC)
target_sources(
    ${PROJECT_NAME}
    PRIVATE
    "clock.cc"
    "console_logger.cc"
    "console.cc"
    "data_stream.cc"
    "debug.cc"
    "dynamic_library.cc"
    "file_helpers.cc"
    "log.cc"
    "strings.cc"
    "synchro.cc"
    
    "aligned_allocator.h"
    "bits.h"
    "clock.h"
    "console_logger.h"
    "console.h"
    "constants.h"
    "data_stream.h"
    "debug.h"
    "dynamic_library.h"
    "file_helpers.h"
    "helpers.h"
    "log.h"
    "macros.h"
    "math.h"
    "platform.h"
    "scoped_function.h"
    "strings.h"
    "synchro.h"
    "types.h"
    "window_handle.h"
)

target_link_libraries(${PROJECT_NAME} PRIVATE ProjectConfiguration PUBLIC fmt::fmt)

# Include pthread for Linux
IF (UNIX)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)
ENDIF (UNIX)
