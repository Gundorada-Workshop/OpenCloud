add_custom_command(
  OUTPUT version.cc
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMAND ruby ${CMAKE_CURRENT_SOURCE_DIR}/gen.rb ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/version.cc.tpl ${CMAKE_CURRENT_BINARY_DIR}/version.cc
)

add_library(version
  version.h
  version.cc
)

target_link_libraries(version PRIVATE
  ProjectConfiguration
)