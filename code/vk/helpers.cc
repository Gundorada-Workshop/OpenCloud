#include "vk/helpers.h"

#include "common/log.h"

set_log_channel("vk");

namespace vk
{
  std::string_view result_to_string(VkResult res)
  {
    constexpr common::dictionary<VkResult, std::string_view, 45> mapping =
    {
      { VK_SUCCESS,                                            "VK_SUCCESS"                                            },
      { VK_NOT_READY,                                          "VK_NOT_READY"                                          },
      { VK_TIMEOUT,                                            "VK_TIMEOUT"                                            },
      { VK_EVENT_SET,                                          "VK_EVENT_SET"                                          },
      { VK_EVENT_RESET,                                        "VK_EVENT_RESET"                                        },
      { VK_INCOMPLETE,                                         "VK_INCOMPLETE"                                         },
      { VK_ERROR_OUT_OF_HOST_MEMORY,                           "VK_ERROR_OUT_OF_HOST_MEMORY"                           },
      { VK_ERROR_OUT_OF_DEVICE_MEMORY,                         "VK_ERROR_OUT_OF_DEVICE_MEMORY"                         },
      { VK_ERROR_INITIALIZATION_FAILED,                        "VK_ERROR_INITIALIZATION_FAILED"                        },
      { VK_ERROR_DEVICE_LOST,                                  "VK_ERROR_DEVICE_LOST"                                  },
      { VK_ERROR_MEMORY_MAP_FAILED,                            "VK_ERROR_MEMORY_MAP_FAILED"                            },
      { VK_ERROR_LAYER_NOT_PRESENT,                            "VK_ERROR_LAYER_NOT_PRESENT"                            },
      { VK_ERROR_EXTENSION_NOT_PRESENT,                        "VK_ERROR_EXTENSION_NOT_PRESENT"                        },
      { VK_ERROR_FEATURE_NOT_PRESENT,                          "VK_ERROR_FEATURE_NOT_PRESENT"                          },
      { VK_ERROR_INCOMPATIBLE_DRIVER,                          "VK_ERROR_INCOMPATIBLE_DRIVER"                          },
      { VK_ERROR_TOO_MANY_OBJECTS,                             "VK_ERROR_TOO_MANY_OBJECTS"                             },
      { VK_ERROR_FORMAT_NOT_SUPPORTED,                         "VK_ERROR_FORMAT_NOT_SUPPORTED"                         },
      { VK_ERROR_FRAGMENTED_POOL,                              "VK_ERROR_FRAGMENTED_POOL"                              },
      { VK_ERROR_UNKNOWN,                                      "VK_ERROR_UNKNOWN"                                      },
      { VK_ERROR_OUT_OF_POOL_MEMORY,                           "VK_ERROR_OUT_OF_POOL_MEMORY"                           },
      { VK_ERROR_INVALID_EXTERNAL_HANDLE,                      "VK_ERROR_INVALID_EXTERNAL_HANDLE"                      },
      { VK_ERROR_FRAGMENTATION,                                "VK_ERROR_FRAGMENTATION"                                },
      { VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS,               "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS"               },
      { VK_PIPELINE_COMPILE_REQUIRED,                          "VK_PIPELINE_COMPILE_REQUIRED"                          },
      { VK_ERROR_SURFACE_LOST_KHR,                             "VK_ERROR_SURFACE_LOST_KHR"                             },
      { VK_ERROR_NATIVE_WINDOW_IN_USE_KHR,                     "VK_ERROR_NATIVE_WINDOW_IN_USE_KHR"                     },
      { VK_SUBOPTIMAL_KHR,                                     "VK_SUBOPTIMAL_KHR"                                     },
      { VK_ERROR_OUT_OF_DATE_KHR,                              "VK_ERROR_OUT_OF_DATE_KHR"                              },
      { VK_ERROR_INCOMPATIBLE_DISPLAY_KHR,                     "VK_ERROR_INCOMPATIBLE_DISPLAY_KHR"                     },
      { VK_ERROR_VALIDATION_FAILED_EXT,                        "VK_ERROR_VALIDATION_FAILED_EXT"                        },
      { VK_ERROR_INVALID_SHADER_NV,                            "VK_ERROR_INVALID_SHADER_NV"                            },
      { VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR,                "VK_ERROR_IMAGE_USAGE_NOT_SUPPORTED_KHR"                },
      { VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR,       "VK_ERROR_VIDEO_PICTURE_LAYOUT_NOT_SUPPORTED_KHR"       },
      { VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR,    "VK_ERROR_VIDEO_PROFILE_OPERATION_NOT_SUPPORTED_KHR"    },
      { VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR,       "VK_ERROR_VIDEO_PROFILE_FORMAT_NOT_SUPPORTED_KHR"       },
      { VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR,        "VK_ERROR_VIDEO_PROFILE_CODEC_NOT_SUPPORTED_KHR"        },
      { VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR,          "VK_ERROR_VIDEO_STD_VERSION_NOT_SUPPORTED_KHR"          },
      { VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT, "VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT" },
      { VK_ERROR_NOT_PERMITTED_KHR,                            "VK_ERROR_NOT_PERMITTED_KHR"                            },
      { VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT,          "VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT"          },
      { VK_THREAD_IDLE_KHR,                                    "VK_THREAD_IDLE_KHR"                                    },
      { VK_THREAD_DONE_KHR,                                    "VK_THREAD_DONE_KHR"                                    },
      { VK_OPERATION_DEFERRED_KHR,                             "VK_OPERATION_DEFERRED_KHR"                             },
      { VK_OPERATION_NOT_DEFERRED_KHR,                         "VK_OPERATION_NOT_DEFERRED_KHR"                         },
      { VK_ERROR_INCOMPATIBLE_SHADER_BINARY_EXT,               "VK_ERROR_INCOMPATIBLE_SHADER_BINARY_EXT"               }
    };

    return mapping.find_or(res, "VK_ERROR_UNKNOWN");
  }

  std::optional<u32> enumerate_instance_version()
  {
    u32 instance_version{ 0 };

    if (!vkEnumerateInstanceVersion)
    {
      log_warn("vkEnumerateInstanceVersion not implemented");

      return std::nullopt;
    }

    const VkResult res = vkEnumerateInstanceVersion(&instance_version);
    if (VK_FAILED(res))
    {
      log_error("Failed to get instance version: {}", res);

      return std::nullopt;
    }

    return instance_version;
  }

  std::vector<VkLayerProperties> enumerate_instance_layer_properties()
  {
    u32 prop_count;

    VkResult res = vkEnumerateInstanceLayerProperties(&prop_count, VK_NULL_HANDLE);
    if (VK_FAILED(res))
    {
      log_error("Failed to enumerate instance layer properties (pass 1): {}", res);

      return {};
    }

    std::vector<VkLayerProperties> props{ prop_count };

    res = vkEnumerateInstanceLayerProperties(&prop_count, props.data());
    if (VK_FAILED(res))
    {
      log_error("Failed to enumerate instance layer properties (pass 2): {}", res);

      return {};
    }

    return props;
  }

  std::vector<VkExtensionProperties> enumerate_instance_extension_properties()
  {
    u32 prop_count;

    VkResult res = vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &prop_count, VK_NULL_HANDLE);
    if (VK_FAILED(res))
    {
      log_error("Failed to enumerate instance extension properties (pass 1): {}", res);

      return {};
    }

    std::vector<VkExtensionProperties> props{ prop_count };

    res = vkEnumerateInstanceExtensionProperties(VK_NULL_HANDLE, &prop_count, props.data());
    if (VK_FAILED(res))
    {
      log_error("Failed to enumerate instance extension properties (pass 2): {}", res);

      return {};
    }

    return props;
  }

  std::vector<VkPhysicalDevice> enumerate_physical_devices(VkInstance instance)
  {
    assert_panic(instance != VK_NULL_HANDLE);

    u32 device_count;

    VkResult res = vkEnumeratePhysicalDevices(instance, &device_count, VK_NULL_HANDLE);
    if (VK_FAILED(res))
    {
      log_error("Failed to enumerate physical devices (pass 1): {}", res);

      return {};
    }

    std::vector<VkPhysicalDevice> devices{ device_count };

    res = vkEnumeratePhysicalDevices(instance, &device_count, devices.data());
    if (VK_FAILED(res))
    {
      log_error("Failed to enumerate physical devices (pass 2): {}", res);

      return {};
    }

    return devices;
  }
}