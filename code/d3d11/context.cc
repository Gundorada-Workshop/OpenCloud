#include <dxgi1_6.h>
#include <d3d11_4.h>

#include "common/debug.h"
#include "common/dynamic_library.h"

#include "d3d11/helpers.h"
#include "d3d11/context.h"

namespace d3d11
{
  using pfn_dxgi_create_factory = std::add_pointer_t<decltype(CreateDXGIFactory2)>;
  using pfn_d3d11_create_device = std::add_pointer_t<decltype(D3D11CreateDevice)>;

  static common::dynamic_library s_dxgi_library{ "dxgi.dll" };
  static common::dynamic_library s_d3d11_library{ "d3d11.dll" };

  static HRESULT create_dxgi_factory(bool debug)
  {
    const auto dxgi_create_factory =
      s_dxgi_library.load_pfn_type<pfn_dxgi_create_factory>("CreateDXGIFactory2");

    assert_panic(dxgi_create_factory);

    UINT flags = 0;
    if (debug)
      flags |= DXGI_CREATE_FACTORY_DEBUG;

    return dxgi_create_factory(flags, IID_PPV_ARGS(g_dxgi_factory2.addressof()));
  }

  static HRESULT create_d3d11_device_and_contexts(bool debug)
  {
    const auto d3d11_create_device =
      s_d3d11_library.load_pfn_type<pfn_d3d11_create_device>("D3D11CreateDevice");

    assert_panic(d3d11_create_device);

    UINT flags = 0;
    if (debug)
      flags |= D3D11_CREATE_DEVICE_DEBUG;

    static constexpr std::array feature_levels =
    {
      D3D_FEATURE_LEVEL_12_0,
      D3D_FEATURE_LEVEL_12_1,
      D3D_FEATURE_LEVEL_12_2
    };

    auto res = d3d11_create_device(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags,
      feature_levels.data(), static_cast<UINT>(feature_levels.size()), D3D11_SDK_VERSION,
      g_d3d11_device.addressof(), nullptr, g_d3d11_device_context.addressof());

    // try without flags
    if (FAILED(res))
    {
      res = d3d11_create_device(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
        feature_levels.data(), static_cast<UINT>(feature_levels.size()), D3D11_SDK_VERSION,
        g_d3d11_device.addressof(), nullptr, g_d3d11_device_context.addressof());
    }

    if (SUCCEEDED(res))
      res = g_d3d11_device->CreateDeferredContext(0, g_d3d11_device_context_deferred.addressof());

    return res;
  }

  bool create(bool factory_debug, bool device_debug)
  {
    if (FAILED(create_dxgi_factory(factory_debug)))
      return false;

    if (FAILED(create_d3d11_device_and_contexts(device_debug)))
      return false;

    return true;
  }
}

d3d11::com_ptr<IDXGIFactory2> g_dxgi_factory2{ nullptr };
d3d11::com_ptr<ID3D11Device> g_d3d11_device{ nullptr };

d3d11::com_ptr<ID3D11DeviceContext> g_d3d11_device_context{ nullptr };
d3d11::com_ptr<ID3D11DeviceContext> g_d3d11_device_context_deferred{ nullptr };