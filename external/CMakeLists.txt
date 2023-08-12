add_subdirectory("fmt")
add_subdirectory("simdjson")
add_subdirectory("Vulkan-Headers")
add_subdirectory("volk")

target_link_libraries(volk PUBLIC Vulkan::Headers)