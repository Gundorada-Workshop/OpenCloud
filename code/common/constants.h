#pragma once
#include <limits>

#include "types.h"

namespace common::constants
{
  template<typename type>
  using limits = std::numeric_limits<type>;

  // unsigned max
  constexpr usize u8_max  = limits<u8>::max();
  constexpr usize u16_max = limits<u16>::max();
  constexpr usize u32_max = limits<u32>::max();
  constexpr usize u64_max = limits<u64>::max();

  // unsigned min
  constexpr usize u8_min  = limits<u8>::min();
  constexpr usize u16_min = limits<u16>::min();
  constexpr usize u32_min = limits<u32>::min();
  constexpr usize u64_min = limits<u64>::min();

  // signed max
  constexpr usize s8_max  = limits<s8>::max();
  constexpr usize s16_max = limits<s16>::max();
  constexpr usize s32_max = limits<s32>::max();
  constexpr usize s64_max = limits<s64>::max();

  // signed min
  constexpr usize s8_min  = limits<s8>::min();
  constexpr usize s16_min = limits<s16>::min();
  constexpr usize s32_min = limits<s32>::min();
  constexpr usize s64_min = limits<s64>::min();

  // float max
  constexpr f32 f32_max = limits<f32>::max();
  constexpr f64 f64_max = limits<f64>::max();

  // float min
  constexpr f32 f32_min = limits<f32>::min();
  constexpr f64 f64_min = limits<f64>::min();

  // quick and dirty wrapper
  template<typename vector_type>
  struct vector_constants
  {
    using type = vector_type::value_type;

    static constexpr vector_type zero()
    {
      return vector_type{ 0 };
    }

    static constexpr vector_type one()
    {
      return vector_type{ 1 };
    }

    static constexpr vector_type min()
    {
      return vector_type{ limits<type>::min() };
    }

    static constexpr vector_type max()
    {
      return vector_type{ limits<type>::max() };
    }
  };

  // zero
  constexpr vec2 vec2_zero = vector_constants<vec2>::zero();
  constexpr vec3 vec3_zero = vector_constants<vec3>::zero();
  constexpr vec4 vec4_zero = vector_constants<vec4>::zero();

  constexpr ivec2 ivec2_zero = vector_constants<ivec2>::zero();
  constexpr ivec3 ivec3_zero = vector_constants<ivec3>::zero();
  constexpr ivec4 ivec4_zero = vector_constants<ivec4>::zero();

  constexpr uvec2 uvec2_zero = vector_constants<uvec2>::zero();
  constexpr uvec3 uvec3_zero = vector_constants<uvec3>::zero();
  constexpr uvec4 uvec4_zero = vector_constants<uvec4>::zero();

  // one
  constexpr vec2 vec2_one = vector_constants<vec2>::one();
  constexpr vec3 vec3_one = vector_constants<vec3>::one();
  constexpr vec4 vec4_one = vector_constants<vec4>::one();

  constexpr ivec2 ivec2_one = vector_constants<ivec2>::one();
  constexpr ivec3 ivec3_one = vector_constants<ivec3>::one();
  constexpr ivec4 ivec4_one = vector_constants<ivec4>::one();

  constexpr uvec2 uvec2_one = vector_constants<uvec2>::one();
  constexpr uvec3 uvec3_one = vector_constants<uvec3>::one();
  constexpr uvec4 uvec4_one = vector_constants<uvec4>::one();

  // min
  constexpr vec2 vec2_min = vector_constants<vec2>::min();
  constexpr vec3 vec3_min = vector_constants<vec3>::min();
  constexpr vec4 vec4_min = vector_constants<vec4>::min();

  constexpr ivec2 ivec2_min = vector_constants<ivec2>::min();
  constexpr ivec3 ivec3_min = vector_constants<ivec3>::min();
  constexpr ivec4 ivec4_min = vector_constants<ivec4>::min();

  constexpr uvec2 uvec2_min = vector_constants<uvec2>::min();
  constexpr uvec3 uvec3_min = vector_constants<uvec3>::min();
  constexpr uvec4 uvec4_min = vector_constants<uvec4>::min();

  // max
  constexpr vec2 vec2_max = vector_constants<vec2>::max();
  constexpr vec3 vec3_max = vector_constants<vec3>::max();
  constexpr vec4 vec4_max = vector_constants<vec4>::max();

  constexpr ivec2 ivec2_max = vector_constants<ivec2>::max();
  constexpr ivec3 ivec3_max = vector_constants<ivec3>::max();
  constexpr ivec4 ivec4_max = vector_constants<ivec4>::max();

  constexpr uvec2 uvec2_max = vector_constants<uvec2>::max();
  constexpr uvec3 uvec3_max = vector_constants<uvec3>::max();
  constexpr uvec4 uvec4_max = vector_constants<uvec4>::max();

  // glm just does this I guess
  constexpr matrix4 identity_matrix{ 1.0f };
  constexpr matrix4 zero_matrix{ 0.0f };
}
