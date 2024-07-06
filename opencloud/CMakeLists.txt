PROJECT(OpenCloudExe)

IF (WIN32)
    add_executable(${PROJECT_NAME} WIN32)
    SET(mainfunc win32.cc)
ELSEIF(APPLE)
    message(FATAL_ERROR "Apple builds currently unsupported")
ELSEIF(UNIX AND NOT APPLE)
    add_executable(${PROJECT_NAME})
    SET(mainfunc unix.cc)
ELSE(WIN32)
    message(FATAL_ERROR "Unrecognised operating system")
ENDIF(WIN32)


target_sources(
    ${PROJECT_NAME}
    PRIVATE
    ${mainfunc}
)

target_link_libraries(${PROJECT_NAME} PRIVATE ProjectConfiguration OpenCloudCommon OpenCloudEngine OpenCloudHost OpenCloudScript OpenCloudGraph)