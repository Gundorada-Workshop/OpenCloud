cmake_minimum_required(VERSION 3.20)

project(OpenCloudData)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE
  "hd.h"
  "img.h"
  "pak.h"
  "iso/datetime.h"
  "iso/dirent.h"
  "iso/dual_endian.h"
  "iso/stream.h"
  "iso/types.h"
  "iso/volume.h"

  "iso/stream.cc"
)

target_link_libraries(${PROJECT_NAME} PRIVATE ProjectConfiguration PUBLIC fmt::fmt)