#include <dxgi.h>

#include <array>

#include "common/debug.h"
#include "common/helpers.h"

#include "graph/texture.h"

namespace d3d11
{
  ALWAYS_INLINE DXGI_FORMAT abstract_to_dxgi_format(graph::texture::data_format format)
  {
    assert_panic(format < graph::texture::data_format::max);

    static constexpr std::array dxgi_format_map =
    {
      DXGI_FORMAT_UNKNOWN,
      DXGI_FORMAT_R8G8B8A8_UNORM,
      DXGI_FORMAT_B8G8R8A8_UNORM,
      DXGI_FORMAT_B5G6R5_UNORM,
      DXGI_FORMAT_R8_UNORM,
      DXGI_FORMAT_D16_UNORM
    };

    return dxgi_format_map[common::to_underlying(format)];
  }

  ALWAYS_INLINE graph::texture::data_format dxgi_format_to_abstract(DXGI_FORMAT format)
  {
    switch (format)
    {
    case DXGI_FORMAT_R8G8B8A8_UNORM:
      return graph::texture::data_format::rgba8;
    case DXGI_FORMAT_B8G8R8A8_UNORM:
      return graph::texture::data_format::bgra8;
    case DXGI_FORMAT_B5G6R5_UNORM:
      return graph::texture::data_format::rgb565;
    case DXGI_FORMAT_R8_UNORM:
      return graph::texture::data_format::r8;
    case DXGI_FORMAT_D16_UNORM:
      return graph::texture::data_format::d16;
    }

    return graph::texture::data_format::unknown;
  }

  class texture : graph::texture
  {
  public:
    static std::unique_ptr<graph::texture> create(const create_info& config);
  };
}