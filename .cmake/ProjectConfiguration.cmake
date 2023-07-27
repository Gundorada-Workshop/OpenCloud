set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# interface used project-wide
add_library(ProjectConfiguration INTERFACE)

# global include directories
target_include_directories(ProjectConfiguration INTERFACE 
  ${PROJECT_SOURCE_DIR}/code
  # WIL for windows
  $<$<CXX_COMPILER_ID:MSVC>:${PROJECT_SOURCE_DIR}/external/wil/include>
)

# global features
target_compile_features(ProjectConfiguration INTERFACE cxx_std_20)

target_compile_options(ProjectConfiguration INTERFACE
  # warning level 4 utf8
  $<$<CXX_COMPILER_ID:MSVC>:/W4 /utf-8 -D_UNICODE -DUNICODE /Zc:wchar_t /permissive->
  # warning level all and extra
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -march=x86-64-v2 -mavx -mfma>
  # enable SIMD
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-march=x86-64-v2 -mavx -mfma>
)

# clang and gcc lack good support for std::format (feature has a lot of DRs)
# MSCV supports it pretty decently but let's use fmtlib everywhere anyway
target_link_libraries(ProjectConfiguration INTERFACE fmt::fmt)