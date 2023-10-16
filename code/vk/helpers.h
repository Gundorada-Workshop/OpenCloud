#pragma once
#include <volk.h>
#include <fmt/format.h>

#include <optional>
#include <string_view>

#include "common/dictionary.h"
#include "common/strings.h"

namespace vk
{
  // convert a VkResult to a human readable string
  std::string_view result_to_string(VkResult res);

  // get the api version for the instance
  // returns nullopt on failure or 1.0 spec
  std::optional<u32> enumerate_instance_version();

  // get instance layers
  std::vector<VkLayerProperties> enumerate_instance_layer_properties();

  // get instance extensions
  std::vector<VkExtensionProperties> enumerate_instance_extension_properties();

  // get physical devices
  std::vector<VkPhysicalDevice> enumerate_physical_devices(VkInstance instance);

  // append a structure to a vk structure chain
  template<typename head_structure_type, typename type>
  void append_structure_to_chain(head_structure_type* head, type* structure)
  {
    VkBaseOutStructure* current = reinterpret_cast<VkBaseOutStructure*>(head);

    while (current->pNext)
    {
      const auto next = current->pNext;

      // we already have this structure in the chain
      if (next->sType == structure->sType)
      {
        return;
      }

      current = next;
    }

    current->pNext = reinterpret_cast<VkBaseOutStructure*>(structure);
  }
}

template<>
struct fmt::formatter<VkResult> : formatter<std::string_view>
{
  auto format(VkResult res, format_context& ctx)
  {
    constexpr std::string_view tpl =
    {
      "VkResult({})"
    };

    return fmt::format_to(ctx.out(), tpl, vk::result_to_string(res));
  }
};

#define VK_SUCCEEDED(res) res == VK_SUCCESS
#define VK_FAILED(res) res != VK_SUCCESS
