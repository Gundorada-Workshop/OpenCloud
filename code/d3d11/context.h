#pragma once

namespace d3d11
{
  bool create(bool factory_debug, bool device_debug);
  void destroy();
}

extern d3d11::com_ptr<IDXGIFactory2> g_dxgi_factory2;
extern d3d11::com_ptr<ID3D11Device> g_d3d11_device;

extern d3d11::com_ptr<ID3D11DeviceContext> g_d3d11_device_context;
extern d3d11::com_ptr<ID3D11DeviceContext> g_d3d11_device_context_deferred;