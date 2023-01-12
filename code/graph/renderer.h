#pragma once
#include <memory>

#include "graph/texture.h"

namespace graph
{
  class renderer
  {
  public:
    using texture_create_info = texture::create_info;

  public:
    virtual std::unique_ptr<texture> create_texture_from_config(const texture_create_info& config) = 0;
  };
}

extern std::unique_ptr<graph::renderer> g_renderer;