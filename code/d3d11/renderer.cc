#include "d3d11/renderer.h"
#include "d3d11/texture.h"

namespace d3d11
{
  std::unique_ptr<graph::texture> renderer::create_texture_from_config(const texture_create_info& config)
  {
    return texture::create(config);
  }
}