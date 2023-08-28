#include "vk/loader.h"
#include "vk/helpers.h"

#include "common/log.h"

set_log_channel("vk");

namespace vk
{
  bool load_base_library()
  {
    const auto res = volkInitialize();

    if (VK_FAILED(res))
    {
      log_error("Failed to load vulkan library: {}", res);

      return false;
    }

    return true;
  }

  bool load_instance_functions(VkInstance instance)
  {
    volkLoadInstance(instance);

    return true;
  }

  bool load_device_functions(VkDevice device)
  {
    volkLoadDevice(device);

    return true;
  }
}