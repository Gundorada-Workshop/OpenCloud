#pragma once
#include <memory>
#include <string>

#include <glm/glm.hpp>

#include <d3d11_4.h>
#include <wil/com.h>

#include "common/types.h"
#include "host/texture.h"

#include "renderer/types.h"

namespace renderer::d3d11
{
  class texture : public host::texture
  {
  public:
    explicit texture(const create_info& config, com_ptr<ID3D11Texture2D1> existing, com_ptr<ID3D11ShaderResourceView> srv,
      com_ptr<ID3D11RenderTargetView> rtv, com_ptr<ID3D11DepthStencilView> dsv);

    ~texture();

    // create a new texture
    static std::unique_ptr<texture> create(const create_info& config);

    // create a texture from an existing d3d handle
    static std::unique_ptr<texture> from_existing(com_ptr<ID3D11Texture2D1> existing, com_ptr<ID3D11ShaderResourceView> srv = nullptr,
      com_ptr<ID3D11RenderTargetView> rtv = nullptr, com_ptr<ID3D11DepthStencilView> dsv = nullptr);

  private:
    // texture 2d handle
    com_ptr<ID3D11Texture2D1> m_native_handle{ nullptr };

    // handle to a shader resource view
    com_ptr<ID3D11ShaderResourceView> m_shader_resource_view{ nullptr };

    // handle to a render target view
    com_ptr<ID3D11RenderTargetView> m_render_target_view{ nullptr };

    // handle to a depth stencil view
    com_ptr<ID3D11DepthStencilView> m_depth_stencil_view{ nullptr };
  };
}
