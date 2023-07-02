// SPDX-License-Identifier: MIT

#pragma once
#include <numbers>

#include "common/types.h"

namespace common::math
{
  // negate a value
  template<typename T>
  constexpr T negate(T val)
  {
    return -val;
  }

  // constant pi
  constexpr f32 pi()
  {
    return std::numbers::pi_v<f32>;
  }

  // constant pi2
  constexpr f32 pi2()
  {
    return pi() * 2.0f;
  }

  // convert degrees to radians
  constexpr f32 deg_to_rad(const f32 deg)
  {
    return deg * pi() / 180.0f;
  }

  // convert radians to degrees
  constexpr f32 rad_to_deg(const f32 rad)
  {
    return rad * 180.0f / pi();
  }
}