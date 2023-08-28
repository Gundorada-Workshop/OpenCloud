#include "common/log.h"

#include "vk/api.h"
#include "vk/helpers.h"

set_log_channel("vk");

namespace vk
{
  api::api() = default;
  api::~api() = default;

  VkInstance api::create_instance()
  {
    const auto api_version = vk::enumerate_instance_version();

    const VkApplicationInfo app =
    {
      .sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
      .pNext              = VK_NULL_HANDLE,
      .pApplicationName   = "Open Cloud",
      .applicationVersion = VK_MAKE_API_VERSION(0, 0, 1, 0),
      .pEngineName        = "Open Cloud Engine",
      .engineVersion      = VK_MAKE_API_VERSION(0, 0, 1, 0),
      .apiVersion         = api_version.value_or(VK_API_VERSION_1_0)
    };

    log_info("Api Version: {}.{}", VK_VERSION_MAJOR(app.apiVersion), VK_API_VERSION_MINOR(app.apiVersion));

    static constexpr std::array<VkValidationFeatureEnableEXT, 3> validation_features =
    {
      VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT,
      VK_VALIDATION_FEATURE_ENABLE_DEBUG_PRINTF_EXT,
      VK_VALIDATION_FEATURE_ENABLE_SYNCHRONIZATION_VALIDATION_EXT
    };

    VkValidationFeaturesEXT validation_ext =
    {
      .sType                          = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
      .pNext                          = VK_NULL_HANDLE,
      .enabledValidationFeatureCount  = static_cast<u32>(validation_features.size()),
      .pEnabledValidationFeatures     = validation_features.data(),
      .disabledValidationFeatureCount = 0,
      .pDisabledValidationFeatures    = VK_NULL_HANDLE
    };

    VkInstanceCreateInfo create_info =
    {
      .sType            = VK_STRUCTURE_TYPE_APPLICATION_INFO,
      .pNext            = VK_NULL_HANDLE,
      .flags            = 0,
      .pApplicationInfo = &app,
    };

    vk::append_structure_to_chain(&create_info, &validation_ext);

    VkInstance instance{ VK_NULL_HANDLE };
    const VkResult res = vkCreateInstance(&create_info, VK_NULL_HANDLE, &instance);

    if (VK_FAILED(res))
    {
      log_error("Failed to create instance: {}", res);

      return VK_NULL_HANDLE;
    }

    return instance;
  }
}