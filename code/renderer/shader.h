#pragma once
#include "renderer/types.h"

namespace renderer::d3d11
{
  // create a vertex shader
  com_ptr<ID3D11VertexShader> create_vertex_shader_from_bytecode(com_ptr<ID3D11Device> device, const void* bytecode, const usize bytecode_byte_count);

  // create a pixel shader
  com_ptr<ID3D11PixelShader> create_pixel_shader_from_bytecode(com_ptr<ID3D11Device> device, const void* bytecode, const usize bytecode_byte_count);

  // create a geometry shader
  com_ptr<ID3D11GeometryShader> create_geometry_shader_from_bytecode(com_ptr<ID3D11Device> device, const void* bytecode, const usize bytecode_byte_count);

  // create a compute shader
  com_ptr<ID3D11ComputeShader> create_compute_shader_from_bytecode(com_ptr<ID3D11Device> device, const void* bytecode, const usize bytecode_byte_count);
}
