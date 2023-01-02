#pragma once
#include <numbers>

#include "common/types.h"

#include "common/math/_vector.h"
//#include "common/math/_matrix.h"

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

  //template<typename type, usize rows, usize columns>
  //inline matrix<type, rows, columns> matrix_transpose(const matrix<type, rows, columns>& m)
  //{
  //  // we need a mat that is of transposed size
  //  // for symetrical matrices this will just be the same mat

  //  //auto xy0xy1 = _mm_shuffle_ps(m.rows[0].v, m.rows[1].v, _MM_SHUFFLE(1, 0, 1, 0));
  //  //auto zw0zw1 = _mm_shuffle_ps(m.rows[0].v, m.rows[1].v, _MM_SHUFFLE(3, 2, 3, 2));

  //  //auto xy2xy3 = _mm_shuffle_ps(m.rows[2].v, m.rows[3].v, _MM_SHUFFLE(1, 0, 1, 0));
  //  //auto zw2zw3 = _mm_shuffle_ps(m.rows[2].v, m.rows[3].v, _MM_SHUFFLE(3, 2, 3, 2));

  //  matrix<type, rows, columns> out;
  //  //out.rows[0].v = _mm_shuffle_ps(xy0xy1, xy2xy3, _MM_SHUFFLE(2, 0, 2, 0));
  //  //out.rows[1].v = _mm_shuffle_ps(xy0xy1, xy2xy3, _MM_SHUFFLE(3, 1, 3, 1));
  //  //out.rows[2].v = _mm_shuffle_ps(zw0zw1, zw2zw3, _MM_SHUFFLE(2, 0, 2, 0));
  //  //out.rows[3].v = _mm_shuffle_ps(zw0zw1, zw2zw3, _MM_SHUFFLE(3, 1, 3, 1));

  //  return out;
  //}
}