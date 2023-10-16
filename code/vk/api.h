#pragma once
#include <volk.h>

#include <vector>

#include "graph/api.h"

#include "common/strings.h"
#include "common/dictionary.h"

namespace vk
{
  class api : public graph::api
  {
  public:
    api();
    ~api();

    static VkInstance create_instance();
  };
}