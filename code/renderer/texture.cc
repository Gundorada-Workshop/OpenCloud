#include "common/log.h"

#include "renderer/texture.h"
#include "renderer/context.h"

set_log_channel("D3D11");

using namespace common;

namespace renderer::d3d11
{
  texture::~texture() = default;

  texture::texture(const create_info& config, com_ptr<ID3D11Texture2D1> existing, com_ptr<ID3D11ShaderResourceView> srv,
    com_ptr<ID3D11RenderTargetView> rtv, com_ptr<ID3D11DepthStencilView> dsv)
    : host::texture(config)
    , m_native_handle{ std::move(existing) }
    , m_shader_resource_view{ std::move(srv) }
    , m_render_target_view{ std::move(rtv) }
    , m_depth_stencil_view{ std::move(dsv) }
  {
  }

  std::unique_ptr<texture> texture::create(const create_info& config)
  {
    assert_panic(g_d3d11_device);

    // these will crash d3d
    assert_panic(config.width >= 1);
    assert_panic(config.height >= 1);
    assert_panic(config.width <= D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION);
    assert_panic(config.height <= D3D11_REQ_TEXTURE2D_U_OR_V_DIMENSION);

    const auto d3d11_bind_flags = to_d3d11_bind_flags(config.flags);
    const auto dxgi_format = to_dxgi_format(config.format);

    D3D11_TEXTURE2D_DESC1 desc =
    {
      .Width      = static_cast<UINT>(config.width),
      .Height     = static_cast<UINT>(config.height),
      .MipLevels  = static_cast<UINT>(config.levels),
      .ArraySize  = static_cast<UINT>(config.layers),
      .Format     = dxgi_format,
      .SampleDesc =
      {
        .Count   = static_cast<UINT>(config.samples),
        .Quality = 0
      },
      .BindFlags      = d3d11_bind_flags,
      .CPUAccessFlags = 0,
      .MiscFlags      = 0,
      .TextureLayout  = D3D11_TEXTURE_LAYOUT_UNDEFINED
    };

    com_ptr<ID3D11Device5> device5;
    assert_panic(SUCCEEDED(g_d3d11_device.query_to(IID_PPV_ARGS(device5.addressof()))));

    com_ptr<ID3D11Texture2D1> tex;
    if (FAILED(device5->CreateTexture2D1(&desc, nullptr, tex.addressof())))
      return nullptr;

    com_ptr<ID3D11ShaderResourceView> srv;
    if (d3d11_bind_flags & D3D11_BIND_SHADER_RESOURCE)
    {
      const D3D11_SHADER_RESOURCE_VIEW_DESC srv_desc =
      {
        .Format        = dxgi_format,
        .ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D,
        .Texture2D =
        {
          .MostDetailedMip = 0,
          .MipLevels       = 0
        }
      };

      if(FAILED(device5->CreateShaderResourceView(tex.get(), &srv_desc, srv.addressof())))
        return nullptr;
    }

    com_ptr<ID3D11RenderTargetView> rtv;
    if (d3d11_bind_flags & D3D11_BIND_RENDER_TARGET)
    {
      const D3D11_RENDER_TARGET_VIEW_DESC rtv_desc =
      {
        .Format        = dxgi_format,
        .ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D,
        .Texture2D =
        {
          .MipSlice   = 0
        }
      };

      if(FAILED(device5->CreateRenderTargetView(tex.get(), &rtv_desc, rtv.addressof())))
        return nullptr;
    }

    com_ptr<ID3D11DepthStencilView> dsv;
    if (d3d11_bind_flags & D3D11_BIND_DEPTH_STENCIL)
    {
      const D3D11_DEPTH_STENCIL_VIEW_DESC dsv_desc =
      {
        .Format        = dxgi_format,
        .ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D,
        .Texture2D =
        {
          .MipSlice = 0
        }
      };

      if (FAILED(device5->CreateDepthStencilView(tex.get(), &dsv_desc, dsv.addressof())))
        return nullptr;
    }

    auto out = std::make_unique<texture>(config, std::move(tex), std::move(srv), std::move(rtv), std::move(dsv));
    if (!out)
      return nullptr;

    return out;
  }

  std::unique_ptr<texture> texture::from_existing(com_ptr<ID3D11Texture2D1> existing, com_ptr<ID3D11ShaderResourceView> srv,
    com_ptr<ID3D11RenderTargetView> rtv, com_ptr<ID3D11DepthStencilView> dsv)
  {
    assert_panic(g_d3d11_device);
    assert_panic(existing);

    com_ptr<ID3D11Texture2D1> texture1;
    assert_panic(SUCCEEDED(existing.query_to(IID_PPV_ARGS(texture1.addressof()))));

    D3D11_TEXTURE2D_DESC1 desc;
    texture1->GetDesc1(&desc);

    bind_flags flags{ bind_flags::none };

    if (desc.BindFlags & D3D11_BIND_SHADER_RESOURCE)
      flags |= bind_flags::shader_resource;

    if (desc.BindFlags & D3D11_BIND_RENDER_TARGET)
      flags |= bind_flags::render_target;

    if (desc.BindFlags & D3D11_BIND_DEPTH_STENCIL)
      flags |= bind_flags::depth_stencil;

    create_info config =
    {
      .width   = desc.Width,
      .height  = desc.Height,
      .layers  = desc.ArraySize,
      .levels  = desc.MipLevels,
      .samples = desc.SampleDesc.Count,
      .format  = to_texture_format(desc.Format),
      .flags   = flags
    };

    auto out = std::make_unique<texture>(config, std::move(existing), std::move(srv), std::move(rtv), std::move(dsv));
    if (!out)
      return nullptr;

    return out;
  }
}
