#pragma once
#include <memory>
#include <vector>
#include "common/types.h"
#include "renderer/types.h"

namespace renderer::d3d11
{
  bool create(bool factory_debug, bool device_debug);
  void destroy();
}

extern renderer::d3d11::com_ptr<IDXGIFactory> g_dxgi_factory;
extern renderer::d3d11::com_ptr<ID3D11Device> g_d3d11_device;

extern renderer::d3d11::com_ptr<ID3D11DeviceContext> g_d3d11_immediate_context;
extern renderer::d3d11::com_ptr<ID3D11DeviceContext> g_d3d11_deferred_context;