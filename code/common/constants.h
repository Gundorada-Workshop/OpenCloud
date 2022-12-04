#pragma once
#include <limits>

#include "types.h"

namespace common::constants
{
  template<typename type>
  using limits = std::numeric_limits<type>;

  // unsigned max
  const usize u8_max  = limits<u8>::max();
  const usize u16_max = limits<u16>::max();
  const usize u32_max = limits<u32>::max();
  const usize u64_max = limits<u64>::max();

  // unsigned min
  const usize u8_min  = limits<u8>::min();
  const usize u16_min = limits<u16>::min();
  const usize u32_min = limits<u32>::min();
  const usize u64_min = limits<u64>::min();

  // signed max
  const usize s8_max  = limits<s8>::max();
  const usize s16_max = limits<s16>::max();
  const usize s32_max = limits<s32>::max();
  const usize s64_max = limits<s64>::max();

  // signed min
  const usize s8_min  = limits<s8>::min();
  const usize s16_min = limits<s16>::min();
  const usize s32_min = limits<s32>::min();
  const usize s64_min = limits<s64>::min();

  // float max
  const f32 f32_max = limits<f32>::max();
  const f64 f64_max = limits<f64>::max();

  // float min
  const f32 f32_min = limits<f32>::min();
  const f64 f64_min = limits<f64>::min();

  // quick and dirty wrapper
  template<typename vector_type>
  struct vector_constants
  {
    using type = vector_type::value_type;

    static const vector_type zero()
    {
      return vector_type{ 0 };
    }

    static const vector_type one()
    {
      return vector_type{ 1 };
    }

    static const vector_type min()
    {
      return vector_type{ limits<type>::min() };
    }

    static const vector_type max()
    {
      return vector_type{ limits<type>::max() };
    }
  };

  // zero
  const vec2 vec2_zero = vector_constants<vec2>::zero();
  const vec3 vec3_zero = vector_constants<vec3>::zero();
  const vec4 vec4_zero = vector_constants<vec4>::zero();

  const ivec2 ivec2_zero = vector_constants<ivec2>::zero();
  const ivec3 ivec3_zero = vector_constants<ivec3>::zero();
  const ivec4 ivec4_zero = vector_constants<ivec4>::zero();

  const uvec2 uvec2_zero = vector_constants<uvec2>::zero();
  const uvec3 uvec3_zero = vector_constants<uvec3>::zero();
  const uvec4 uvec4_zero = vector_constants<uvec4>::zero();

  // one
  const vec2 vec2_one = vector_constants<vec2>::one();
  const vec3 vec3_one = vector_constants<vec3>::one();
  const vec4 vec4_one = vector_constants<vec4>::one();

  const ivec2 ivec2_one = vector_constants<ivec2>::one();
  const ivec3 ivec3_one = vector_constants<ivec3>::one();
  const ivec4 ivec4_one = vector_constants<ivec4>::one();

  const uvec2 uvec2_one = vector_constants<uvec2>::one();
  const uvec3 uvec3_one = vector_constants<uvec3>::one();
  const uvec4 uvec4_one = vector_constants<uvec4>::one();

  // min
  const vec2 vec2_min = vector_constants<vec2>::min();
  const vec3 vec3_min = vector_constants<vec3>::min();
  const vec4 vec4_min = vector_constants<vec4>::min();

  const ivec2 ivec2_min = vector_constants<ivec2>::min();
  const ivec3 ivec3_min = vector_constants<ivec3>::min();
  const ivec4 ivec4_min = vector_constants<ivec4>::min();

  const uvec2 uvec2_min = vector_constants<uvec2>::min();
  const uvec3 uvec3_min = vector_constants<uvec3>::min();
  const uvec4 uvec4_min = vector_constants<uvec4>::min();

  // max
  const vec2 vec2_max = vector_constants<vec2>::max();
  const vec3 vec3_max = vector_constants<vec3>::max();
  const vec4 vec4_max = vector_constants<vec4>::max();

  const ivec2 ivec2_max = vector_constants<ivec2>::max();
  const ivec3 ivec3_max = vector_constants<ivec3>::max();
  const ivec4 ivec4_max = vector_constants<ivec4>::max();

  const uvec2 uvec2_max = vector_constants<uvec2>::max();
  const uvec3 uvec3_max = vector_constants<uvec3>::max();
  const uvec4 uvec4_max = vector_constants<uvec4>::max();

  // glm just does this I guess
  const matrix4 identity_matrix{ 1.0f };
  const matrix4 zero_matrix{ 0.0f };
}
