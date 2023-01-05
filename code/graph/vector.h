#pragma once
#include "common/types.h"
#include "common/bits.h"

#include "graph/_vector/_vector_cxp.h"
#include "graph/_vector/_vector_sse.h"

namespace graph
{
  template<usize size>
  concept is_vec_2 = (size >= 2);

  template<usize size>
  concept is_vec_3 = (size >= 3);

  template<usize size>
  concept is_vec_4 = (size >= 4);

  template<typename type, usize size>
  struct __declspec(align(16)) vector
  {
    // underlying implementation details
    using impl_simd = detail::vector_impl_sse<type>;
    using impl_cxpr = detail::vector_impl_cxp<type>;

    using simd_type = impl_simd::traits::type;
    using cxpr_type = impl_cxpr::traits::type;

    using vector_type = vector<type, size>;

    using vector2_type = vector<type, 2>;
    using vector3_type = vector<type, 3>;
    using vector4_type = vector<type, 4>;

    static constexpr usize one_mask = (1 << size) - 1;

    using enum detail::element;

    // default construct
    // zero in all components
    inline constexpr vector()
    {
      if (std::is_constant_evaluated())
        data.a = impl_cxpr::set(static_cast<type>(0));
      else
        data.v = impl_simd::set(static_cast<type>(0));
    }

    // construct from the underlying SSE type
    inline constexpr vector(const simd_type& val)
    {
      data.v = val;
    }

    // construct from underlying array type
    inline constexpr vector(const cxpr_type& val)
    {
      data.a = val;
    }

    // construct from one scalar
    // sets all the emements of the vector to the value
    template<typename u = type>
    inline constexpr vector(const u& a)
    {
      if (std::is_constant_evaluated())
        data.a = impl_cxpr::set(a);
      else
        data.v = impl_simd::set(a);
    }

    // construct from two scalars
    // repeats the two values across the vector
    template<typename u = type>
    requires is_vec_2<size>
    inline constexpr vector(const u& a, const u& b)
    {
      if (std::is_constant_evaluated())
        data.a = impl_cxpr::set(a, b);
      else
        data.v = impl_simd::set(a, b);
    }

    // construct from three scalars
    // sets the first 3 elements to their respective values
    // if the vector has 4 elements the last element is set to 1
    template<typename u = type>
    requires is_vec_3<size>
    inline constexpr vector(const u& a, const u& b, const u& c)
    {
      if (std::is_constant_evaluated())
        data.a = impl_cxpr::set(a, b, c, static_cast<type>(1));
      else
        data.v = impl_simd::set(a, b, c, static_cast<type>(1));
    }

    // construct from four scalars
    // sets all elements to their respective values
    template<typename u = type>
    requires is_vec_4<size>
    inline constexpr vector(const u& a, const u& b, const u& c, const u& d)
    {
      if (std::is_constant_evaluated())
        data.a = impl_cxpr::set(a, b, c, d);
      else
        data.v = impl_simd::set(a, b, c, d);
    }

    // construct from a vector2
    // repeats the first two elements of the vector2 across the vector
    template<typename u = type>
    requires is_vec_2<size>
    inline constexpr vector(const vector2_type& xy)
    {
      // TODO: optimize
      if (std::is_constant_evaluated())
        data.a = impl_cxpr::set(xy.x(), xy.y());
      else
        data.v = impl_simd::set(xy.x(), xy.y());
    }

    // construct from two vector2s
    // sets the first vector to the xy components and the second to the zw components
    template<typename u = type>
    requires is_vec_4<size>
    inline constexpr vector(const vector2_type& xy, const vector2_type& zw)
    {
      // TODO: optimize
      if (std::is_constant_evaluated())
        data.a = impl_cxpr::set(xy.x(), xy.y(), zw.x(), zw.y());
      else
        data.v = impl_simd::set(xy.x(), xy.y(), zw.x(), zw.y());
    }

    // construct from a vector3 and a scalar
    // sets the components of the vector3 to xyz and the scalar to w
    template<typename u = type>
    requires is_vec_4<size>
    inline constexpr vector(const vector3_type& xyz, const u& w) 
    {
      // TODO: opitmize
      if (std::is_constant_evaluated())
        data.a = impl_cxpr::set(xyz.x(), xyz.y(), xyz.x(), w);
      else
        data.v = impl_simd::set(xyz.x(), xyz.y(), xyz.x(), w);
    }

    // new vector from underlying SSE type
    static inline constexpr vector_type from(const simd_type& val)
    {
      return vector_type{ val };
    }

    // new vector from one scalar
    template<typename u = type>
    static inline constexpr vector_type from(const u& a)
    {
      return vector_type{ a };
    }

    // new vector from two scalars
    template<typename u = type>
    requires is_vec_2<size>
    static inline constexpr vector_type from(const u& a, const u& b)
    {
      return vector_type{ a, b };
    }

    // new vector from three scalars
    template<typename u = type>
    requires is_vec_3<size>
    static inline constexpr vector_type from(const u& a, const u& b, const u& c)
    {
      return vector_type{ a, b, c };
    }

    // new vector from four scalars
    template<typename u = type>
    requires is_vec_4<size>
    static inline constexpr vector_type from(const u& a, const u& b, const u& c, const u& d)
    {
      return vector_type{ a, b, c, d };
    }

    // zero constant
    // all components are 1
    static inline constexpr vector_type zero()
    {
      return vector_type::from(static_cast<type>(0));
    }

    // one constant
    // all components are 1
    static inline constexpr vector_type one()
    {
      return vector_type::from(static_cast<type>(1));
    }

    // min constant
    // all components are the min value of the underlying type
    static inline constexpr vector_type min()
    {
      return vector_type::from(std::numeric_limits<type>::min());
    }

    // max constant
    // all components are the max value of the underlying type
    static inline constexpr vector_type max()
    {
      return vector_type::from(std::numeric_limits<type>::max());
    }

    // access the first component
    template<typename u = type>
    inline constexpr u x() const
    {
      if (std::is_constant_evaluated())
        return impl_cxpr::extract<_x>(data.a);
      else
        return impl_simd::extract<_x>(data.v);
    }

    // access the second component
    template<typename u = type>
    requires is_vec_2<size>
    inline constexpr u y() const
    {
      if (std::is_constant_evaluated())
        return impl_cxpr::extract<_y>(data.a);
      else
        return impl_simd::extract<_y>(data.v);
    }

    // access the third component
    template<typename u = type>
    requires is_vec_3<size>
    inline constexpr u z() const
    {
      if (std::is_constant_evaluated())
        return impl_cxpr::extract<_z>(data.a);
      else
        return impl_simd::extract<_z>(data.v);
    }

    // access the forth component
    template<typename u = type>
    requires is_vec_4<size>
    inline constexpr u w() const
    {
      if (std::is_constant_evaluated())
        return impl_cxpr::extract<_w>(data.a);
      else
        return impl_simd::extract<_w>(data.v);
    }

    // assignment by vector
    inline constexpr vector_type& operator =(const vector_type& rhs)
    {
      data.v = rhs.data.v;
      return *this;
    }

    // assignment by simd type
    inline constexpr vector_type& operator =(const simd_type& rhs)
    {
      data.v = rhs;
      return *this;
    }

    // assignment by array
    inline constexpr vector_type& operator =(const cxpr_type& rhs)
    {
      data.a = rhs;
      return *this;
    }

    // addition by vector
    inline constexpr vector_type operator +=(const vector_type& rhs)
    {
      *this = *this + rhs;
      return *this;
    }

    // increment by vector
    inline constexpr vector_type operator ++(int)
    {
      vector_type tmp = *this;
      *this += type{ 1 };
      return tmp;
    }

    // increment by vector
    inline constexpr vector_type& operator ++()
    {
      *this += type{ 1 };
      return *this;
    }

    // subtraction by vector
    inline constexpr vector_type& operator -=(const vector_type& rhs)
    {
      *this = *this - rhs;
      return *this;
    }

    // decrement by vector
    inline constexpr vector_type operator --(int)
    {
      vector_type tmp = *this;
      *this -= type{ 1 };
      return tmp;
    }

    // decrement by vector
    inline constexpr vector_type& operator --()
    {
      *this -= type{ 1 };
      return *this;
    }

    // multiplication by vector
    inline constexpr vector_type& operator *=(const vector_type& rhs)
    {
      *this = *this * rhs;
      return *this;
    }

    // division by vector
    inline constexpr vector_type& operator /=(const vector_type& rhs)
    {
      *this = *this / rhs;
      return *this;
    }

    #include "graph/_vector/_vector_swizzle.inl"

    union
    {
      simd_type v;
      cxpr_type a;

      std::array<f64, 2> _f64;
      std::array<u64, 2> _u64;
      std::array<s64, 2> _s64;

      std::array<f32, 4> _f32;
      std::array<u32, 4> _u32;
      std::array<s32, 4> _s32;

      std::array<u16, 8> _u16;
      std::array<s16, 8> _s16;

      std::array<u8, 16> _u8;
      std::array<s8, 16> _s8;
    } data;
  };

  template<typename type, usize size>
  inline constexpr vector<type, size> operator +(const vector<type, size>& lhs, const vector<type, size>& rhs)
  {
    if (std::is_constant_evaluated())
      return detail::vector_impl_cxp<type>::add(lhs.data.a, rhs.data.a);
    else
      return detail::vector_impl_sse<type>::add(lhs.data.v, rhs.data.v);
  }

  template<typename type, usize size>
  inline constexpr vector<type, size> operator +(const vector<type, size>& lhs, const type& rhs)
  {
    const auto other = vector<type, size>{ rhs };

    if (std::is_constant_evaluated())
      return detail::vector_impl_cxp<type>::add(lhs.data.a, other.data.a);
    else
      return detail::vector_impl_sse<type>::add(lhs.data.v, other.data.v);
  }

  template<typename type, usize size>
  inline constexpr vector<type, size> operator -(const vector<type, size>& lhs, const vector<type, size>& rhs)
  {
    if (std::is_constant_evaluated())
      return detail::vector_impl_cxp<type>::sub(lhs.data.a, rhs.data.a);
    else
      return detail::vector_impl_sse<type>::sub(lhs.data.v, rhs.data.v);
  }

  template<typename type, usize size>
  inline constexpr vector<type, size> operator -(const vector<type, size>& lhs, const type& rhs)
  {
    const auto other = vector<type, size>{ rhs };

    if (std::is_constant_evaluated())
      return detail::vector_impl_cxp<type>::sub(lhs.data.a, other.data.a);
    else
      return detail::vector_impl_sse<type>::sub(lhs.data.v, other.data.v);
  }

  // non-uniform scaling
  // compact 3x3 diagonal scaling matrix
  template<typename type, usize size>
  inline constexpr vector<type, size> operator *(const vector<type, size>& lhs, const vector<type, size>& rhs)
  {
    if (std::is_constant_evaluated())
      return detail::vector_impl_cxp<type>::mul(lhs.data.a, rhs.data.a);
    else
      return detail::vector_impl_sse<type>::mul(lhs.data.v, rhs.data.v);
  }

  // uniform scaling
  template<typename type, usize size>
  inline constexpr vector<type, size> operator *(const vector<type, size>& lhs, const type& rhs)
  {
    const auto other = vector<type, size>{ rhs };

    if (std::is_constant_evaluated())
      return detail::vector_impl_cxp<type>::mul(lhs.data.a, other.data.a);
    else
      return detail::vector_impl_sse<type>::mul(lhs.data.v, other.data.v);
  }

  template<typename type, usize size>
  inline constexpr vector<type, size> operator /(const vector<type, size>& lhs, const vector<type, size>& rhs)
  {
    if (std::is_constant_evaluated())
      return detail::vector_impl_cxp<type>::div(lhs.data.a, rhs.data.a);
    else
      return detail::vector_impl_sse<type>::div(lhs.data.v, rhs.data.v);
  }

  template<typename type, usize size>
  inline constexpr vector<type, size> operator /(const vector<type, size>& lhs, const type& rhs)
  {
    const auto other = vector<type, size>{ rhs };

    if (std::is_constant_evaluated())
      return detail::vector_impl_cxp<type>::div(lhs.data.a, other.data.a);
    else
      return detail::vector_impl_sse<type>::div(lhs.data.v, other.data.v);
  }

  template<typename type, usize size>
  inline constexpr vector<type, size> operator ==(const vector<type, size>& lhs, const vector<type, size>& rhs)
  {
    if (std::is_constant_evaluated())
      return detail::vector_impl_cxp<type>::equal(lhs.data.a, rhs.data.a);
    else
      return detail::vector_impl_sse<type>::equal(lhs.data.v, rhs.data.v);
  }

  template<typename type, usize size>
  inline constexpr vector<type, size> operator ==(const vector<type, size>& lhs, type& rhs)
  {
    const auto other = vector<type, size>{ rhs };

    if (std::is_constant_evaluated())
      return detail::vector_impl_cxp<type>::equal(lhs.data.a, other.data.a);
    else
      return detail::vector_impl_sse<type>::equal(lhs.data.v, other.data.v);
  }

  template<typename type, usize size>
  inline constexpr vector<type, size> operator <(const vector<type, size>& lhs, const vector<type, size>& rhs)
  {
    if (std::is_constant_evaluated())
      return detail::vector_impl_cxp<type>::less_than(lhs.data.a, rhs.data.a);
    else
      return detail::vector_impl_sse<type>::less_than(lhs.data.v, rhs.data.v);
  }

  template<typename type, usize size>
  inline constexpr vector<type, size> operator <(const vector<type, size>& lhs, const type& rhs)
  {
    const auto other = vector<type, size>{ rhs };

    if (std::is_constant_evaluated())
      return detail::vector_impl_cxp<type>::less_than(lhs.data.a, other.data.a);
    else
      return detail::vector_impl_sse<type>::less_than(lhs.data.v, other.data.v);
  }

  template<typename type, usize size>
  inline constexpr vector<type, size> operator <=(const vector<type, size>& lhs, const vector<type, size>& rhs)
  {
    if (std::is_constant_evaluated())
      return detail::vector_impl_cxp<type>::less_than_equal(lhs.data.a, rhs.data.a);
    else
      return detail::vector_impl_sse<type>::less_than_equal(lhs.data.v, rhs.data.v);
  }

  template<typename type, usize size>
  inline constexpr vector<type, size> operator <=(const vector<type, size>& lhs, const type& rhs)
  {
    const auto other = vector<type, size>{ rhs };

    if (std::is_constant_evaluated())
      return detail::vector_impl_cxp<type>::less_than_equal(lhs.data.a, other.data.a);
    else
      return detail::vector_impl_sse<type>::less_than_equal(lhs.data.v, other.data.v);
  }

  template<typename type, usize size>
  inline constexpr vector<type, size> operator >(const vector<type, size>& lhs, const vector<type, size>& rhs)
  {
    if (std::is_constant_evaluated())
      return detail::vector_impl_cxp<type>::greater_than(lhs.data.a, rhs.data.a);
    else
      return detail::vector_impl_sse<type>::greater_than(lhs.data.v, rhs.data.v);
  }

  template<typename type, usize size>
  inline constexpr vector<type, size> operator >(const vector<type, size>& lhs, const type& rhs)
  {
    const auto other = vector<type, size>{ rhs };

    if (std::is_constant_evaluated())
      return detail::vector_impl_cxp<type>::greater_than(lhs.data.a, other.data.a);
    else
      return detail::vector_impl_sse<type>::greater_than(lhs.data.v, other.data.v);
  }

  template<typename type, usize size>
  inline constexpr vector<type, size> operator >=(const vector<type, size>& lhs, const vector<type, size>& rhs)
  {
    if (std::is_constant_evaluated())
      return detail::vector_impl_cxp<type>::greater_than_equal(lhs.data.a, rhs.data.a);
    else
      return detail::vector_impl_sse<type>::greater_than_equal(lhs.data.v, rhs.data.v);
  }

  template<typename type, usize size>
  inline constexpr vector<type, size> operator >=(const vector<type, size>& lhs, const type& rhs)
  {
    const auto other = vector<type, size>{ rhs };

    if (std::is_constant_evaluated())
      return detail::vector_impl_cxp<type>::greater_than_equal(lhs.data.a, other.data.a);
    else
      return detail::vector_impl_sse<type>::greater_than_equal(lhs.data.v, other.data.v);
  }
}

template<typename type>
using vector2 = graph::vector<type, 2>;

template<typename type>
using vector3 = graph::vector<type, 3>;

template<typename type>
using vector4 = graph::vector<type, 4>;

using vec2 = vector2<f32>;
using vec3 = vector3<f32>;
using vec4 = vector4<f32>;

using uvec2 = vector2<u32>;
using uvec3 = vector3<u32>;
using uvec4 = vector4<u32>;

using ivec2 = vector2<s32>;
using ivec3 = vector3<s32>;
using ivec4 = vector4<s32>;
