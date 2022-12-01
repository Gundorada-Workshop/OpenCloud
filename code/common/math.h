#pragma once
#include <numbers>
#include "common/types.h"

namespace common
{
  template<typename T>
  constexpr T negate(T val)
  {
    return -val;
  }

  constexpr f32 pi()
  {
    return std::numbers::pi_v<f32>;
  }

  constexpr f32 pi2()
  {
    return pi() * 2.0f;
  }

  constexpr f32 deg_to_rad(const f32 deg)
  {
    return deg * pi() / 180.0f;
  }

  constexpr f32 rad_to_deg(const f32 rad)
  {
    return rad * 180.0f / pi();
  }

  constexpr vec3 vector_outer_product(const vec3& a, const vec3& b)
  {
    return {
      a.y * b.z - b.y * a.z,
      a.z * b.x - b.z * a.x,
      a.x * b.y - b.x * a.y
    };
  }
}
