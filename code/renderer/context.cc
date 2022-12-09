#include <algorithm>
#include <type_traits>

#include <d3dcompiler.h>

#include "common/log.h"
#include "common/strings.h"
#include "common/scoped_function.h"
#include "common/dynamic_library.h"

#include "renderer/context.h"
#include "renderer/texture.h"

set_log_channel("D3D11");

using namespace common;

renderer::d3d11::com_ptr<IDXGIFactory> g_dxgi_factory;
renderer::d3d11::com_ptr<ID3D11Device> g_d3d11_device;

renderer::d3d11::com_ptr<ID3D11DeviceContext> g_d3d11_immediate_context;
renderer::d3d11::com_ptr<ID3D11DeviceContext> g_d3d11_deferred_context;

namespace renderer::d3d11
{
  static dynamic_library s_dxgi_library("dxgi.dll");
  static dynamic_library s_d3d11_library("d3d11.dll");

  using PFN_DXGI_CREATE_FACTORY_2 = std::add_pointer_t<HRESULT(UINT Flags, REFIID riid, void** ppFactory)>;

  static HRESULT create_factory(bool debug)
  {
    PFN_DXGI_CREATE_FACTORY_2 create_factory_fn = s_dxgi_library.load_pfn_type<PFN_DXGI_CREATE_FACTORY_2>("CreateDXGIFactory2");

    UINT flags = 0;
    if (debug)
    {
      log_info("Enabling DXGIFactory debugging");

      flags |= DXGI_CREATE_FACTORY_DEBUG;
    }

    const auto res = create_factory_fn(flags, IID_PPV_ARGS(g_dxgi_factory.addressof()));

    // try without debugging
    if (debug && FAILED(res))
    {
      log_warn("Failed to create debug DXGI factory, trying without debugging");

      return create_factory_fn(0, IID_PPV_ARGS(g_dxgi_factory.addressof()));
    }

    return res;
  }

  static HRESULT create_device(bool debug)
  {
    PFN_D3D11_CREATE_DEVICE create_device_fn = s_d3d11_library.load_pfn_type<PFN_D3D11_CREATE_DEVICE>("D3D11CreateDevice");
    if (!create_device_fn)
      panicf("Failed to load d3d11");

    com_ptr<IDXGIFactory7> factory7;
    assert_panic(SUCCEEDED(g_dxgi_factory.query_to(IID_PPV_ARGS(factory7.addressof()))));

    UINT current_adapter_id = 0;

    com_ptr<IDXGIAdapter1> adapter;
    while (factory7->EnumAdapters1(current_adapter_id, adapter.addressof()) != DXGI_ERROR_NOT_FOUND)
    {
      scoped_function increment([&]() {
        ++current_adapter_id;
      });

      com_ptr<IDXGIAdapter4> adapter4;
      if (FAILED(adapter.query_to(IID_PPV_ARGS(adapter4.addressof()))))
      {
        log_warn("Failed to query adapter4 interface for adapter index {}", current_adapter_id);

        continue;
      }

      DXGI_ADAPTER_DESC3 adapter_description;
      if (FAILED(adapter4->GetDesc3(&adapter_description)))
      {
        log_warn("Failed to get adapter description for adapter index {}", current_adapter_id);

        continue;
      }

      log_info("Selected adapter:");
      log_info(" {}", adapter_description);

      break;
    }

    if (!adapter)
      log_warn("No suitable DXGI adapter found");

    UINT flags = 0;
    if (debug)
    {
      log_info("Enabling device debug layer");
      flags |= D3D11_CREATE_DEVICE_DEBUG;
    }

    static constexpr std::array feature_levels =
    {
      D3D_FEATURE_LEVEL_12_0,
      D3D_FEATURE_LEVEL_12_1,
      D3D_FEATURE_LEVEL_12_2
    };

    const auto res = create_device_fn(adapter.get(), D3D_DRIVER_TYPE_UNKNOWN, NULL, flags,
      feature_levels.data(), static_cast<UINT>(feature_levels.size()), D3D11_SDK_VERSION,
      g_d3d11_device.addressof(), NULL, g_d3d11_immediate_context.addressof());

    // try again without debugging
    if (debug && FAILED(res))
    {
      log_warn("Failed to create D3D11 device with debugging, trying again without");

      return create_device_fn(adapter.get(), D3D_DRIVER_TYPE_UNKNOWN, NULL, 0,
        feature_levels.data(), static_cast<UINT>(feature_levels.size()), D3D11_SDK_VERSION,
        g_d3d11_device.addressof(), NULL, g_d3d11_immediate_context.addressof());
    }

    return res;
  }

  static HRESULT create_deferred_context()
  {
    return g_d3d11_device->CreateDeferredContext(0, g_d3d11_deferred_context.addressof());
  }

  bool create(bool debug_factory, bool debug_device)
  {
    if (FAILED(create_factory(debug_factory)))
    {
      log_error("Failed to create DXGI factory");

      return false;
    }

    if (FAILED(create_device(debug_device)))
    {
      log_error("Failed to create D3D11 device");

      return false;
    }

    if (FAILED(create_deferred_context()))
    {
      log_error("Failed to create deferred context");

      return false;
    }

    return true;
  }

  void destroy()
  {
    g_d3d11_deferred_context.reset();
    g_d3d11_immediate_context.reset();

    g_d3d11_device.reset();
    g_dxgi_factory.reset();
  }
}
