#include "common/log.h"

#include "renderer/shader.h"

set_log_channel("D3D11");

namespace renderer::d3d11
{
  com_ptr<ID3D11VertexShader> create_vertex_shader_from_bytecode(com_ptr<ID3D11Device> device, const void* bytecode, const usize bytecode_byte_count)
  {
    com_ptr<ID3D11VertexShader> vs;
    if (FAILED(device->CreateVertexShader(bytecode, bytecode_byte_count, nullptr, vs.addressof())))
    {
      log_error("Failed to compile vertex shader");

      return {};
    }

    return vs;
  }

  com_ptr<ID3D11PixelShader> create_pixel_shader_from_bytecode(com_ptr<ID3D11Device> device, const void* bytecode, const usize bytecode_byte_count)
  {
    com_ptr<ID3D11PixelShader> ps;
    if (FAILED(device->CreatePixelShader(bytecode, bytecode_byte_count, nullptr, ps.addressof())))
    {
      log_error("Failed to compile pixel shader");

      return {};
    }

    return ps;
  }


  com_ptr<ID3D11GeometryShader> create_geometry_shader_from_bytecode(com_ptr<ID3D11Device> device, const void* bytecode, const usize bytecode_byte_count)
  {
    com_ptr<ID3D11GeometryShader> gs;
    if (FAILED(device->CreateGeometryShader(bytecode, bytecode_byte_count, nullptr, gs.addressof())))
    {
      log_error("Failed to compile geometry shader");

      return {};
    }

    return gs;
  }


  com_ptr<ID3D11ComputeShader> create_compute_shader_from_bytecode(com_ptr<ID3D11Device> device, const void* bytecode, const usize bytecode_byte_count)
  {
    com_ptr<ID3D11ComputeShader> cs;
    if (FAILED(device->CreateComputeShader(bytecode, bytecode_byte_count, nullptr, cs.addressof())))
    {
      log_error("Failed to compile compute shader");

      return {};
    }

    return cs;
  }
}
