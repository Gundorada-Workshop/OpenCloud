#pragma once
#include "common/types.h"

#include "renderer/types.h"
#include "renderer/texture.h"

namespace renderer::d3d11
{
  class swapchain
  {
  public:
    swapchain(com_ptr<IDXGISwapChain1> dxgi_swapchain);
    ~swapchain();

    // create a new swapchain
    static std::unique_ptr<swapchain> create(HWND hwnd, const texture::data_format fmt);

    // present
    bool present(const uint interval);

    // resize the swapchain
    bool resize(const uvec2 new_size);

    // get the back buffer
    inline texture* backbuffer()
    {
      return m_back_buffer.get();
    }

    // get the size
    inline uvec2 size()
    {
      return m_size;
    }

  private:
    // current size
    uvec2 m_size;

    // native d3d swapchain
    com_ptr<IDXGISwapChain1> m_native_handle{ };

    // backbuffer
    std::unique_ptr<texture> m_back_buffer;

    // whether to allow tearing (vrr) in window mode
    bool m_tearing_enabled{ false };

  private:
    bool recreate_render_target();
    void destroy_render_target();
  };
}
