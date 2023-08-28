#pragma once

#include <volk.h>

namespace vk
{
  // load the vulkan library
  bool load_base_library();

  // load function pointers for the instance
  bool load_instance_functions(VkInstance instance);

  // load function pointers for the device
  bool load_device_functions(VkDevice device);
}