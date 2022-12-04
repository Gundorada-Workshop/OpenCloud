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

  // check if any respective component of a is greater than the components of b
  template<usize size, typename type>
  inline bool vector_any_greater_than(const vec<type, size>& a, const vec<type, size>& b)
  {
    return glm::any(glm::greaterThan<size, type>(a, b));
  }

  // check if any respective component of a is less than the components of b
  template<usize size, typename type>
  inline bool vector_any_less_than(const vec<type, size>& a, const vec<type, size>& b)
  {
    return glm::any(glm::lessThan<size, type>(a, b));
  }

  // check if any respective component of a is greater than or equal to the components of b
  template<usize size, typename type>
  inline bool vector_any_greater_than_equal(const vec<type, size>& a, const vec<type, size>& b)
  {
    return glm::any(glm::greaterThanEqual<size, type>(a, b));
  }

  // check if any respective component of a is less than or equal to the components of b
  template<usize size, typename type>
  inline bool vector_any_less_than_equal(const vec<type, size>& a, const vec<type, size>& b)
  {
    return glm::any(glm::lessThanEqual<size, type>(a, b));
  }

  // check if all respective components of a are greater than the components of b
  template<usize size, typename type>
  inline bool vector_all_greater_than(const vec<type, size>& a, const vec<type, size>& b)
  {
    return glm::all(glm::greaterThan<size, type>(a, b));
  }

  // check if all respective components of a are less than the components of b
  template<usize size, typename type>
  inline bool vector_all_less_than(const vec<type, size>& a, const vec<type, size>& b)
  {
    return glm::all(glm::lessThan<size, type>(a, b));
  }

  // check if all respective components of a are greater than or equal to the components of b
  template<usize size, typename type>
  inline bool vector_all_greater_than_equal(const vec<type, size>& a, const vec<type, size>& b)
  {
    return glm::all(glm::greaterThanEqual<size, type>(a, b));
  }

  // check if all respective components of a are less than or equal to the components of b
  template<usize size, typename type>
  inline bool vector_all_less_than_equal(const vec<type, size>& a, const vec<type, size>& b)
  {
    return glm::all(glm::lessThanEqual<size, type>(a, b));
  }

  inline vec3 vector_outer_product(const vec3& a, const vec3& b)
  {
    return {
      a.y * b.z - b.y * a.z,
      a.z * b.x - b.z * a.x,
      a.x * b.y - b.x * a.y
    };
  }
}
