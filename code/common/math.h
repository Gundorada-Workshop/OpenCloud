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

  // calculate vector distance between two vectors
  template<usize size, typename type>
  inline type vector_distance(const vec<type, size>& a, const vec<type, size>& b)
  {
    return glm::distance<size, type>(a, b);
  }

  // normalize a vector
  template<usize size, typename type>
  inline vec<type, size> vector_normalize(const vec<type, size>& a)
  {
    return glm::normalize<size, type>(a);
  }

  // calculate the length of a vector
  template<usize size, typename type>
  inline type vector_length(const vec<type, size>& a)
  {
    return glm::length<size, type>(a);
  }

  // calculate the dot product of two vectors
  template<usize size, typename type>
  inline type vector_dot_product(const vec<type, size>& a, const vec<type, size>& b)
  {
    return glm::dot<size, type>(a, b);
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
