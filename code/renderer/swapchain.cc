#include "common/debug.h"
#include "common/log.h"

#include "renderer/context.h"
#include "renderer/swapchain.h"

set_log_channel("D3D11");

namespace renderer::d3d11
{
  swapchain::swapchain(com_ptr<IDXGISwapChain1> dxgi_swap_chain)
    : m_native_handle(std::move(dxgi_swap_chain))
  {
    DXGI_SWAP_CHAIN_DESC1 desc;
    m_native_handle->GetDesc1(&desc);

    m_size.x = desc.Width;
    m_size.y = desc.Height;
  }

  swapchain::~swapchain() = default;

  std::unique_ptr<swapchain> swapchain::create(HWND hwnd, const texture::data_format fmt)
  {
    assert_panic(g_d3d11_device);
    assert_panic(g_dxgi_factory);

    com_ptr<IDXGIFactory7> factory7;
    assert_panic(SUCCEEDED(g_dxgi_factory.query_to(IID_PPV_ARGS(factory7.addressof()))));

    UINT flags = 0;
    BOOL tearing_supported{ FALSE };
    if (SUCCEEDED(factory7->CheckFeatureSupport(DXGI_FEATURE_PRESENT_ALLOW_TEARING, &tearing_supported, sizeof(BOOL))))
    {
      if (tearing_supported)
        flags |= DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
    }

    DXGI_SWAP_CHAIN_DESC1 desc =
    {
      .Width      = 0,
      .Height     = 0,
      .Format     = to_dxgi_format(fmt),
      .Stereo     = FALSE,
      .SampleDesc =
      {
        .Count   = 1,
        .Quality = 0
      },
      .BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_BACK_BUFFER,
      .BufferCount = 2,
      .Scaling     = DXGI_SCALING_NONE,
      .SwapEffect  = DXGI_SWAP_EFFECT_FLIP_DISCARD,
      .AlphaMode   = DXGI_ALPHA_MODE_UNSPECIFIED,
      .Flags       = flags
    };

    com_ptr<IDXGISwapChain1> dxgi_swapchain;
    if (FAILED(factory7->CreateSwapChainForHwnd(g_d3d11_device.get(), hwnd, &desc, nullptr, nullptr, dxgi_swapchain.addressof())))
    {
      log_error("Failed to create swapchain");

      return nullptr;
    }

    auto out = std::make_unique<swapchain>(dxgi_swapchain);

    out->m_tearing_enabled = tearing_supported;

    if (!out)
    {
      log_error("Failed to allocate swapchain");

      return nullptr;
    }

    return out;
  }

  bool swapchain::present(const uint interval)
  {
    constexpr DXGI_PRESENT_PARAMETERS params =
    {
      .DirtyRectsCount = 0,
      .pDirtyRects     = NULL,
      .pScrollRect     = NULL,
      .pScrollOffset   = NULL
    };

    UINT flags = 0;
    if (m_tearing_enabled)
      flags |= DXGI_PRESENT_ALLOW_TEARING;

    if (FAILED(m_native_handle->Present1(interval, 0, &params)))
      return false;

    return recreate_render_target();
  }

  bool swapchain::resize(const uvec2 new_size)
  {
    const auto dxgi_format = to_dxgi_format(m_back_buffer->format());

    destroy_render_target();

    UINT flags = 0;
    if (m_tearing_enabled)
      flags |= DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;

    if (FAILED(m_native_handle->ResizeBuffers(2, new_size.x, new_size.y, dxgi_format, flags)))
      return false;

    m_size = new_size;

    return recreate_render_target();
  }

  bool swapchain::recreate_render_target()
  {
    com_ptr<ID3D11Texture2D1> texture;
    if(FAILED(m_native_handle->GetBuffer(0, IID_PPV_ARGS(texture.addressof()))))
      return false;

    D3D11_TEXTURE2D_DESC1 desc;
    texture->GetDesc1(&desc);

    const D3D11_RENDER_TARGET_VIEW_DESC rtv_desc =
    {
      .Format        = desc.Format,
      .ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D,
      .Texture2D =
      {
        .MipSlice   = 0
      }
    };

    com_ptr<ID3D11RenderTargetView> rtv;
    g_d3d11_device->CreateRenderTargetView(texture.get(), &rtv_desc, rtv.addressof());

    std::array<f32, 4> color =
    {
      1.0f, 0.0f, 1.0f, 1.0f
    };

    g_d3d11_immediate_context->ClearRenderTargetView(rtv.get(), color.data());

    std::array rtvs =
    {
      rtv.get()
    };

    g_d3d11_immediate_context->OMGetRenderTargets(static_cast<UINT>(rtvs.size()), rtvs.data(), nullptr);

    m_back_buffer = texture::from_existing(std::move(texture), nullptr, std::move(rtv), nullptr);

    if (!m_back_buffer)
      return false;

    return true;
  }

  void swapchain::destroy_render_target()
  {
    m_back_buffer.reset();
  }
}
