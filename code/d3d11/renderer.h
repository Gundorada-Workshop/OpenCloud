#include "graph/renderer.h"
#include "graph/texture.h"

namespace d3d11
{
  class renderer : graph::renderer
  {
    using graph::renderer::texture_create_info;

  public:
    std::unique_ptr<graph::texture> create_texture_from_config(const texture_create_info& config);
  };
}