#pragma once

#include <dxgi1_6.h>
#include <d3d11_4.h>

#include <wil/com.h>

#include "common/types.h"
#include "common/debug.h"
#include "common/strings.h"

#include "host/texture.h"

namespace renderer::d3d11
{
  // I don't want to type out com_ptr_nothrow every time
  // we don't have exceptions so this is the version we use
  template<typename T>
  using com_ptr = wil::com_ptr_nothrow<T>;

  inline DXGI_FORMAT to_dxgi_format(host::texture::data_format fmt)
  {
    assert_panic(fmt < host::texture::data_format::max);

    static constexpr std::array dxgi_format_map =
    {
      DXGI_FORMAT_UNKNOWN,
      DXGI_FORMAT_R8G8B8A8_UNORM,
      DXGI_FORMAT_B8G8R8A8_UNORM,
      DXGI_FORMAT_B5G6R5_UNORM,
      DXGI_FORMAT_R8_UNORM,
      DXGI_FORMAT_D16_UNORM
    };

    return dxgi_format_map[std::to_underlying(fmt)];
  }

  inline host::texture::data_format to_texture_format(DXGI_FORMAT fmt)
  {
    switch (fmt)
    {
    case DXGI_FORMAT_R8G8B8A8_UNORM:
      return host::texture::data_format::rgba8;
    case DXGI_FORMAT_B8G8R8A8_UNORM:
      return host::texture::data_format::bgra8;
    case DXGI_FORMAT_B5G6R5_UNORM:
      return host::texture::data_format::rgb565;
    case DXGI_FORMAT_R8_UNORM:
      return host::texture::data_format::r8;
    case DXGI_FORMAT_D16_UNORM:
      return host::texture::data_format::d16;
    }

    return host::texture::data_format::unknown;
  }

  inline UINT to_d3d11_bind_flags(host::texture::bind_flags bflags)
  {
    UINT d3d_bind_flags = 0;
    if (static_cast<bool>(bflags & host::texture::bind_flags::shader_resource))
      d3d_bind_flags |= D3D11_BIND_SHADER_RESOURCE;

    if (static_cast<bool>(bflags & host::texture::bind_flags::render_target))
      d3d_bind_flags |= D3D11_BIND_RENDER_TARGET;

    if (static_cast<bool>(bflags & host::texture::bind_flags::depth_stencil))
      d3d_bind_flags |= D3D11_BIND_DEPTH_STENCIL;

    return d3d_bind_flags;
  }
}

template<>
struct fmt::formatter<DXGI_ADAPTER_DESC3> : formatter<std::string_view>
{
  auto format(const DXGI_ADAPTER_DESC3& desc, format_context& ctx)
  {
    constexpr std::string_view tpl =
    {
      "DXGI_ADAPTER_DESC3(desc: {}, vendor: {}, device: {}, subsystem: {}, rev: {}, vram: {}, sram: {}, ssram: {})"
    };

    const auto utf8_description = common::strings::to_utf8(desc.Description);

    if (!utf8_description)
      panicf("Failed to convert DXGI adapter description");

    return fmt::format_to(ctx.out(), tpl, *utf8_description, desc.VendorId, desc.DeviceId, desc.SubSysId, desc.Revision, desc.DedicatedVideoMemory, desc.DedicatedSystemMemory, desc.SharedSystemMemory);
  }
};