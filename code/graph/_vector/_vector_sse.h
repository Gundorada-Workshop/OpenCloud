#pragma once
#if defined(_MSC_VER)
  #include <intrin.h>
#elif defined(__GNUG__) || defined(__clang__)
  #include <immintrin.h>
  #include <avxintrin.h>
#else
  static_assert(false, "Not implemented");
#endif

#include "common/types.h"
#include "common/bits.h"

#include "graph/_vector/_vector_common.h"

namespace graph::detail
{
  constexpr uint shuffle_mask(element e0, element e1, element e2, element e3)
  {
    return (common::to_underlying(e0) << 0) |
           (common::to_underlying(e1) << 2) |
           (common::to_underlying(e2) << 4) |
           (common::to_underlying(e3) << 6);
  }

  consteval uint shuffle_mask_repeat(element el)
  {
    return shuffle_mask(el, el, el, el);
  }

  template<typename type>
  concept integral_vector = std::same_as<type, __m128i>;

  template<typename type>
  concept single_precision_float_vector = std::same_as<type, __m128>;

  template<typename type>
  struct vector_traits_sse;

  template<>
  struct vector_traits_sse<f32>
  {
    using type = __m128;
  };

  template<>
  struct vector_traits_sse<f64>
  {
    using type = __m128;
  };

  template<>
  struct vector_traits_sse<u32>
  {
    using type = __m128i;
  };

  template<>
  struct vector_traits_sse<s32>
  {
    using type = __m128i;
  };

  template<typename type>
  struct vector_impl_sse
  {
    using traits = vector_traits_sse<type>;

    static constexpr usize elements = sizeof(traits::type) / sizeof(type);

    // broadcast integral value
    template<typename u = type, typename v = typename traits::type>
    requires integral_vector<v>
    static inline v set(const u& a)
    {
      return _mm_set1_epi32(a);
    }

    // broadcast single precision float value
    template<typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline v set(const u& a)
    {
      return _mm_set_ps1(a);
    }

    // repeat integral values a and b across vector
    template<typename u = type, typename v = typename traits::type>
    requires integral_vector<v>
    static inline v set(const u& a, const u& b)
    {
      return _mm_setr_epi32(a, b, a, b);
    }

    // repeat single precision float values a and b across vector
    template<typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline v set(const u& a, const u& b)
    {
      return _mm_setr_ps(a, b, a, b);
    }

    // set integral values a, b, c, d to x, y, z, w respectively
    template<typename u = type, typename v = typename traits::type>
    requires integral_vector<v>
    static inline v set(const u& a, const u& b, const u& c, const u& d)
    {
      return _mm_setr_epi32(a, b, c, d);
    }

    // set single precision float values a, b, c, d to x, y, z, w respectively
    template<typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline v set(const u& a, const u& b, const u&  c, const u& d)
    {
      return _mm_setr_ps(a, b, c, d);
    }

    // extract integral value el from vector
    template<element el, typename u = type, typename v = typename traits::type>
    requires integral_vector<v>
    static inline u extract(const v& a)
    {
      return _mm_cvtsi128_si32(_mm_shuffle_epi32(a, shuffle_mask_repeat(el)));
    }

    // extract single precision float value el from vector 
    template<element el, typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline u extract(const v& a)
    {
      return _mm_cvtss_f32(_mm_permute_ps(a, shuffle_mask_repeat(el)));
    }

    // swizzle integral vector (shuffle across one register)
    template<element e0, element e1, element e2, element e3, typename u = type, typename v = typename traits::type>
    requires integral_vector<v>
    static inline v swizzle(const v& a)
    {
      return _mm_shuffle_epi32(a, shuffle_mask(e0, e1, e2, e3));
    }

    // swizzle single precision floating point vector (shuffle across one vector)
    template<element e0, element e1, element e2, element e3, typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline v swizzle(const v& a)
    {
      return _mm_permute_ps(a, shuffle_mask(e0, e1, e2, e3));
    }

    // shuffle single precision float vectors a and b
    template< element e0, element e1, element e2, element e3, typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline v shuffle(const v& a, const v& b)
    {
      return _mm_shuffle_ps(a, b, shuffle_mask(e0, e1, e2, e3));
    }

    // add two single precision float vectors
    template<typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline v add(const v& lhs, const v& rhs)
    {
      return _mm_add_ps(lhs, rhs);
    }

    // add two integral vectors
    template<typename u = type, typename v = typename traits::type>
    requires integral_vector<v>
    static inline v add(const v& lhs, const v& rhs)
    {
      return _mm_add_epi32(lhs, rhs);
    }

    // subtract two single precision float vectors
    template<typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline v sub(const v& lhs, const v& rhs)
    {
      return _mm_sub_ps(lhs, rhs);
    }

    // subtract two integral vectors
    template<typename u = type, typename v = typename traits::type>
    requires integral_vector<v>
    static inline v sub(const v& lhs, const v& rhs)
    {
      return _mm_sub_epi32(lhs, rhs);
    }

    // divide two single precision float vectors
    template<typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline v div(const v& lhs, const v& rhs)
    {
      return _mm_div_ps(lhs, rhs);
    }

    // divide two signed integral vectors
    template<typename u = type, typename v = typename traits::type>
    requires integral_vector<v> && std::signed_integral<u>
    static inline v div(const v& lhs, const v& rhs)
    {
      return _mm_div_epi32(lhs, rhs);
    }

    // divide two unsigned integral vectors
    template<typename u = type, typename v = typename traits::type>
    requires integral_vector<v> && std::unsigned_integral<u>
    static inline v div(const v& lhs, const v& rhs)
    {
      return _mm_div_epu32(lhs, rhs);
    }

    // multiply two single precision float vectors
    template<typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline v mul(const v& lhs, const v& rhs)
    {
      return _mm_mul_ps(lhs, rhs);
    }

    // multiply two signed integral vectors
    template<typename u = type, typename v = typename traits::type>
    requires integral_vector<v> && std::signed_integral<u>
    static inline v mul(const v& lhs, const v& rhs)
    {
      return _mm_mul_epi32(lhs, rhs);
    }

    // multiply two unsigned integral vectors 
    template<typename u = type, typename v = typename traits::type>
    requires integral_vector<v> && std::unsigned_integral<u>
    static inline v mul(const v& lhs, const v& rhs)
    {
      return _mm_mul_epu32(lhs, rhs);
    }

    // single precision packed floating point fused multiply add
    // (a * b) + c
    template<typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline v madd(const v& a, const v& b, const v& c)
    {
      return _mm_fmadd_ps(a, b, c);
    }

    // signed integral multiply add
    // (a * b) + c
    template<typename u = type, typename v = typename traits::type>
    requires integral_vector<v> && std::signed_integral<u>
    static inline v madd(const v& a, const v& b, const v& c)
    {
      return _mm_add_epi32(_mm_mul_epi32(a, b), c);
    }

    // unsigned integer multiply add
    // (a * b) + c
    template<typename u = type, typename v = typename traits::type>
    requires integral_vector<v> && std::unsigned_integral<u>
    static inline v madd(const v& a, const v& b, const v& c)
    {
      return _mm_add_epi32(_mm_mul_epu32(a, b), c);
    }

    // single precision float vector dot product
    template<usize size, typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline u dot(const v& lhs, const v& rhs)
    {
      // select relevant elements, broadcast to x
      constexpr usize mask = ((1 << size) - 1) << 4 | 0x1;

      return _mm_cvtss_f32(_mm_dp_ps(lhs, rhs, mask));
    }

    // single precision float vector cross product
    template<typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline v cross(const v& lhs, const v& rhs)
    {
      // https://geometrian.com/programming/tutorials/cross-product/index.php

      using enum element;

      const auto lhs_yzx = _mm_permute_ps(lhs, shuffle_mask(_y, _z, _x, _w));
      const auto rhs_zxy = _mm_permute_ps(rhs, shuffle_mask(_z, _x, _y, _w));

      // prod = lhs.yzx() * rhs.xyz()
      const auto prod = _mm_mul_ps(lhs_yzx, rhs);
      const auto prod_yzx = _mm_permute_ps(prod, shuffle_mask(_y, _z, _x, _w));

      // (lhs.yzx() * rhs.zxy()) - prod.yzx()
      return _mm_fmsub_ps(lhs_yzx, rhs_zxy, prod_yzx);
    }

    // calculate the magnitude of a single precision float vector
    template<usize size, typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline u mag(const v& a)
    {
      // http://fastcpp.blogspot.com/2012/02/calculating-length-of-3d-vector-using.html

      // select relevant elements, broadcast to x
      constexpr usize mask = ((1 << size) - 1) << 4 | 0x1;

      const auto dot_product = _mm_dp_ps(a, a, mask);

      // faster but less accurate
      // const auto inverse_dot_product = _mm_rsqrt_ss(dot_product);
      // const auto res = _mm_mul_ss(dot_product, inverse_dot_product);

      const auto res = _mm_sqrt_ps(dot_product);

      return _mm_cvtss_f32(res);
    }

    // calculate the magnitude squared of a single precision float vector
    template<usize size, typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline u mag2(const v& a)
    {
      // select relevant elements, broadcast to x
      constexpr usize mask = ((1 << size) - 1) << 4 | 0x1;

      return _mm_cvtss_f32(_mm_dp_ps(a, a, mask));
    }

    // calculate the distance between two single precision float vectors
    template<usize size, typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline u distance(const v& a, const v& b)
    {
      // select relevant elements, broadcast to x
      constexpr usize mask = ((1 << size) - 1) << 4 | 0x1;

      const auto delta = _mm_sub_ps(a, b);

      const auto dot_product = _mm_dp_ps(delta, delta, mask);

      // fast but less accurate
      // const auto inverse_dot_product = _mm_rsqrt_ss(dot_product);
      // const auto res = _mm_mul_ss(dot_product, inverse_dot_product);

      const auto res = _mm_sqrt_ps(dot_product);

      return _mm_cvtss_f32(res);
    }

    // calculate the distance squared between two single precision float vectors
    template<usize size, typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline u distance2(const v& a, const v& b)
    {
      // select relevant elements, broadcast to first element in result
      constexpr usize mask = ((1 << size) - 1) << 4 | 0x1;

      const auto delta = _mm_sub_ps(a, b);

      return _mm_cvtss_f32(_mm_dp_ps(delta, delta, mask));
    }

    // normalize a vector (make it's magnitude 1) given a size
    template<usize size, typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline v norm(const v& a)
    {
      // http://fastcpp.blogspot.com/2012/02/calculating-length-of-3d-vector-using.html
      // 
      // faster but less accurate
      // const auto dot_product = _mm_dp_ps(v, v, mask);
      // const auto inverse_dot_product = _mm_rsqrt_ps(dot_product);
      // 
      // return _mm_mul_ps(v, inverse_dot_product);

      // select relevant elements, broadcast to all elements in result
      constexpr usize mask = ((1 << size) - 1) << 4 | 0xF;

      const auto dot_product = _mm_dp_ps(a, a, mask);
      const auto square_root = _mm_sqrt_ps(dot_product);

      return _mm_div_ps(a, square_root);
    }

    // normalize a vector (make it's magnitude 1) given a size
    template<usize size, typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline v norm2(const v& a)
    {
      // select relevant elements, broadcast to all elements in result
      constexpr usize mask = ((1 << size) - 1) << 4 | 0xF;

      return _mm_sqrt_ps(_mm_dp_ps(a, a, mask));
    }

    // calculate the absolute value of a single precision float vector
    template<typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline v abs(const v& a)
    {
      return _mm_andnot_ps(_mm_set1_ps(-0.0f), a);
    }

    // check if single precision float vectors a lhs and rhs are equal
    // returns a mask of elements where this is true
    template<typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline v equal(const v& lhs, const v& rhs)
    {
      return _mm_cmpeq_ps(lhs, rhs);
    }

    // check if integral vectors lhs and rhs are equal
    // returns a mask of elements where this is true
    template<typename u = type, typename v = typename traits::type>
    requires integral_vector<v>
    static inline v equal(const v& lhs, const v& rhs)
    {
      return _mm_cmpeq_epi32(lhs, rhs);
    }

    // check if single precision float vector lsh is less than rhs
    // returns a mask of elements where this is true
    template<typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline v less_than(const v& lhs, const v& rhs)
    {
      return _mm_cmplt_ps(lhs, rhs);
    }

    // check if single precision float vector lsh is less or equal to than rhs
    // returns a mask of elements where this is true
    template<typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline v less_than_equal(const v& lhs, const v& rhs)
    {
      return _mm_cmple_ps(lhs, rhs);
    }

    // check if single precision float vector lsh is greater than rhs
    // returns a mask of elements where this is true
    template<typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline v greater_than(const v& lhs, const v& rhs)
    {
      return _mm_cmpgt_ps(lhs, rhs);
    }

    // check if single precision float vector lsh is greater or equal to than rhs
    // returns a mask of elements where this is true
    template<typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline v greater_than_equal(const v& lhs, const v& rhs)
    {
      return _mm_cmpge_ps(lhs, rhs);
    }

    // returns a single precision float vector that represents the max values between lhs and rhs
    template<typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline v max(const v& lhs, const v& rhs)
    {
      return _mm_max_ps(lhs, rhs);
    }

    // returns a single precision float vector that represents the min values between lhs and rhs
    template<typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline v min(const v& lhs, const v& rhs)
    {
      return _mm_min_ps(lhs, rhs);
    }

    // blend two single precision float vectors a and b based on mask
    template<typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline v blend(const v& a, const v& b, const v& mask)
    {
      return _mm_blendv_ps(a, b, mask);
    }

    // check if any values are true in a single precision float mask
    template<usize size, typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline bool any(const v& mask)
    {
      constexpr usize one_mask = (1 << size) - 1;

      return (_mm_movemask_ps(mask) & one_mask);
    }

    // check if all values are true in a single precision float mask
    template<usize size, typename u = type, typename v = typename traits::type>
    requires single_precision_float_vector<v>
    static inline bool all(const v& mask)
    {
      constexpr usize one_mask = (1 << size) - 1;

      return (_mm_movemask_ps(mask) & one_mask) == one_mask;
    }
  };
}