template<typename u = type>
requires is_vec_2<size>
inline constexpr vector4_type xxxx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _x, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _x, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector4_type xxxy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _x, _x, _y>(data.a);
  else
    return impl_simd::swizzle<_x, _x, _x, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type xxxz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _x, _x, _z>(data.a);
  else
    return impl_simd::swizzle<_x, _x, _x, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xxxw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _x, _x, _w>(data.a);
  else
    return impl_simd::swizzle<_x, _x, _x, _w>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector4_type xxyx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _x, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _x, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector4_type xxyy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _x, _y, _y>(data.a);
  else
    return impl_simd::swizzle<_x, _x, _y, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type xxyz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _x, _y, _z>(data.a);
  else
    return impl_simd::swizzle<_x, _x, _y, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xxyw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _x, _y, _w>(data.a);
  else
    return impl_simd::swizzle<_x, _x, _y, _w>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type xxzx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _x, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _x, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type xxzy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _x, _z, _y>(data.a);
  else
    return impl_simd::swizzle<_x, _x, _z, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type xxzz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _x, _z, _z>(data.a);
  else
    return impl_simd::swizzle<_x, _x, _z, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xxzw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _x, _z, _w>(data.a);
  else
    return impl_simd::swizzle<_x, _x, _z, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xxwx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _x, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _x, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xxwy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _x, _w, _y>(data.a);
  else
    return impl_simd::swizzle<_x, _x, _w, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xxwz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _x, _w, _z>(data.a);
  else
    return impl_simd::swizzle<_x, _x, _w, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xxww() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _x, _w, _w>(data.a);
  else
    return impl_simd::swizzle<_x, _x, _w, _w>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector4_type xyxx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _y, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _y, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector4_type xyxy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _y, _x, _y>(data.a);
  else
    return impl_simd::swizzle<_x, _y, _x, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type xyxz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _y, _x, _z>(data.a);
  else
    return impl_simd::swizzle<_x, _y, _x, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xyxw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _y, _x, _w>(data.a);
  else
    return impl_simd::swizzle<_x, _y, _x, _w>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector4_type xyyx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _y, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _y, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector4_type xyyy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _y, _y, _y>(data.a);
  else
    return impl_simd::swizzle<_x, _y, _y, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type xyyz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _y, _y, _z>(data.a);
  else
    return impl_simd::swizzle<_x, _y, _y, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xyyw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _y, _y, _w>(data.a);
  else
    return impl_simd::swizzle<_x, _y, _y, _w>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type xyzx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _y, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _y, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type xyzy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _y, _z, _y>(data.a);
  else
    return impl_simd::swizzle<_x, _y, _z, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type xyzz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _y, _z, _z>(data.a);
  else
    return impl_simd::swizzle<_x, _y, _z, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xyzw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _y, _z, _w>(data.a);
  else
    return impl_simd::swizzle<_x, _y, _z, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xywx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _y, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _y, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xywy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _y, _w, _y>(data.a);
  else
    return impl_simd::swizzle<_x, _y, _w, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xywz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _y, _w, _z>(data.a);
  else
    return impl_simd::swizzle<_x, _y, _w, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xyww() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _y, _w, _w>(data.a);
  else
    return impl_simd::swizzle<_x, _y, _w, _w>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type xzxx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _z, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _z, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type xzxy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _z, _x, _y>(data.a);
  else
    return impl_simd::swizzle<_x, _z, _x, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type xzxz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _z, _x, _z>(data.a);
  else
    return impl_simd::swizzle<_x, _z, _x, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xzxw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _z, _x, _w>(data.a);
  else
    return impl_simd::swizzle<_x, _z, _x, _w>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type xzyx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _z, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _z, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type xzyy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _z, _y, _y>(data.a);
  else
    return impl_simd::swizzle<_x, _z, _y, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type xzyz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _z, _y, _z>(data.a);
  else
    return impl_simd::swizzle<_x, _z, _y, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xzyw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _z, _y, _w>(data.a);
  else
    return impl_simd::swizzle<_x, _z, _y, _w>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type xzzx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _z, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _z, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type xzzy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _z, _z, _y>(data.a);
  else
    return impl_simd::swizzle<_x, _z, _z, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type xzzz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _z, _z, _z>(data.a);
  else
    return impl_simd::swizzle<_x, _z, _z, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xzzw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _z, _z, _w>(data.a);
  else
    return impl_simd::swizzle<_x, _z, _z, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xzwx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _z, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _z, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xzwy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _z, _w, _y>(data.a);
  else
    return impl_simd::swizzle<_x, _z, _w, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xzwz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _z, _w, _z>(data.a);
  else
    return impl_simd::swizzle<_x, _z, _w, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xzww() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _z, _w, _w>(data.a);
  else
    return impl_simd::swizzle<_x, _z, _w, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xwxx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _w, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _w, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xwxy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _w, _x, _y>(data.a);
  else
    return impl_simd::swizzle<_x, _w, _x, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xwxz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _w, _x, _z>(data.a);
  else
    return impl_simd::swizzle<_x, _w, _x, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xwxw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _w, _x, _w>(data.a);
  else
    return impl_simd::swizzle<_x, _w, _x, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xwyx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _w, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _w, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xwyy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _w, _y, _y>(data.a);
  else
    return impl_simd::swizzle<_x, _w, _y, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xwyz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _w, _y, _z>(data.a);
  else
    return impl_simd::swizzle<_x, _w, _y, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xwyw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _w, _y, _w>(data.a);
  else
    return impl_simd::swizzle<_x, _w, _y, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xwzx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _w, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _w, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xwzy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _w, _z, _y>(data.a);
  else
    return impl_simd::swizzle<_x, _w, _z, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xwzz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _w, _z, _z>(data.a);
  else
    return impl_simd::swizzle<_x, _w, _z, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xwzw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _w, _z, _w>(data.a);
  else
    return impl_simd::swizzle<_x, _w, _z, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xwwx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _w, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _w, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xwwy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _w, _w, _y>(data.a);
  else
    return impl_simd::swizzle<_x, _w, _w, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xwwz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _w, _w, _z>(data.a);
  else
    return impl_simd::swizzle<_x, _w, _w, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type xwww() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _w, _w, _w>(data.a);
  else
    return impl_simd::swizzle<_x, _w, _w, _w>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector4_type yxxx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _x, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _x, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector4_type yxxy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _x, _x, _y>(data.a);
  else
    return impl_simd::swizzle<_y, _x, _x, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type yxxz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _x, _x, _z>(data.a);
  else
    return impl_simd::swizzle<_y, _x, _x, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type yxxw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _x, _x, _w>(data.a);
  else
    return impl_simd::swizzle<_y, _x, _x, _w>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector4_type yxyx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _x, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _x, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector4_type yxyy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _x, _y, _y>(data.a);
  else
    return impl_simd::swizzle<_y, _x, _y, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type yxyz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _x, _y, _z>(data.a);
  else
    return impl_simd::swizzle<_y, _x, _y, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type yxyw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _x, _y, _w>(data.a);
  else
    return impl_simd::swizzle<_y, _x, _y, _w>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type yxzx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _x, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _x, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type yxzy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _x, _z, _y>(data.a);
  else
    return impl_simd::swizzle<_y, _x, _z, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type yxzz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _x, _z, _z>(data.a);
  else
    return impl_simd::swizzle<_y, _x, _z, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type yxzw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _x, _z, _w>(data.a);
  else
    return impl_simd::swizzle<_y, _x, _z, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type yxwx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _x, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _x, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type yxwy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _x, _w, _y>(data.a);
  else
    return impl_simd::swizzle<_y, _x, _w, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type yxwz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _x, _w, _z>(data.a);
  else
    return impl_simd::swizzle<_y, _x, _w, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type yxww() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _x, _w, _w>(data.a);
  else
    return impl_simd::swizzle<_y, _x, _w, _w>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector4_type yyxx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _y, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _y, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector4_type yyxy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _y, _x, _y>(data.a);
  else
    return impl_simd::swizzle<_y, _y, _x, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type yyxz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _y, _x, _z>(data.a);
  else
    return impl_simd::swizzle<_y, _y, _x, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type yyxw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _y, _x, _w>(data.a);
  else
    return impl_simd::swizzle<_y, _y, _x, _w>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector4_type yyyx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _y, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _y, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector4_type yyyy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _y, _y, _y>(data.a);
  else
    return impl_simd::swizzle<_y, _y, _y, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type yyyz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _y, _y, _z>(data.a);
  else
    return impl_simd::swizzle<_y, _y, _y, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type yyyw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _y, _y, _w>(data.a);
  else
    return impl_simd::swizzle<_y, _y, _y, _w>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type yyzx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _y, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _y, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type yyzy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _y, _z, _y>(data.a);
  else
    return impl_simd::swizzle<_y, _y, _z, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type yyzz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _y, _z, _z>(data.a);
  else
    return impl_simd::swizzle<_y, _y, _z, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type yyzw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _y, _z, _w>(data.a);
  else
    return impl_simd::swizzle<_y, _y, _z, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type yywx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _y, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _y, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type yywy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _y, _w, _y>(data.a);
  else
    return impl_simd::swizzle<_y, _y, _w, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type yywz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _y, _w, _z>(data.a);
  else
    return impl_simd::swizzle<_y, _y, _w, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type yyww() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _y, _w, _w>(data.a);
  else
    return impl_simd::swizzle<_y, _y, _w, _w>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type yzxx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _z, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _z, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type yzxy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _z, _x, _y>(data.a);
  else
    return impl_simd::swizzle<_y, _z, _x, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type yzxz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _z, _x, _z>(data.a);
  else
    return impl_simd::swizzle<_y, _z, _x, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type yzxw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _z, _x, _w>(data.a);
  else
    return impl_simd::swizzle<_y, _z, _x, _w>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type yzyx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _z, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _z, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type yzyy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _z, _y, _y>(data.a);
  else
    return impl_simd::swizzle<_y, _z, _y, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type yzyz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _z, _y, _z>(data.a);
  else
    return impl_simd::swizzle<_y, _z, _y, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type yzyw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _z, _y, _w>(data.a);
  else
    return impl_simd::swizzle<_y, _z, _y, _w>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type yzzx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _z, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _z, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type yzzy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _z, _z, _y>(data.a);
  else
    return impl_simd::swizzle<_y, _z, _z, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type yzzz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _z, _z, _z>(data.a);
  else
    return impl_simd::swizzle<_y, _z, _z, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type yzzw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _z, _z, _w>(data.a);
  else
    return impl_simd::swizzle<_y, _z, _z, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type yzwx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _z, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _z, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type yzwy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _z, _w, _y>(data.a);
  else
    return impl_simd::swizzle<_y, _z, _w, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type yzwz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _z, _w, _z>(data.a);
  else
    return impl_simd::swizzle<_y, _z, _w, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type yzww() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _z, _w, _w>(data.a);
  else
    return impl_simd::swizzle<_y, _z, _w, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type ywxx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _w, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _w, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type ywxy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _w, _x, _y>(data.a);
  else
    return impl_simd::swizzle<_y, _w, _x, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type ywxz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _w, _x, _z>(data.a);
  else
    return impl_simd::swizzle<_y, _w, _x, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type ywxw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _w, _x, _w>(data.a);
  else
    return impl_simd::swizzle<_y, _w, _x, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type ywyx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _w, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _w, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type ywyy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _w, _y, _y>(data.a);
  else
    return impl_simd::swizzle<_y, _w, _y, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type ywyz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _w, _y, _z>(data.a);
  else
    return impl_simd::swizzle<_y, _w, _y, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type ywyw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _w, _y, _w>(data.a);
  else
    return impl_simd::swizzle<_y, _w, _y, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type ywzx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _w, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _w, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type ywzy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _w, _z, _y>(data.a);
  else
    return impl_simd::swizzle<_y, _w, _z, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type ywzz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _w, _z, _z>(data.a);
  else
    return impl_simd::swizzle<_y, _w, _z, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type ywzw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _w, _z, _w>(data.a);
  else
    return impl_simd::swizzle<_y, _w, _z, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type ywwx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _w, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _w, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type ywwy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _w, _w, _y>(data.a);
  else
    return impl_simd::swizzle<_y, _w, _w, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type ywwz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _w, _w, _z>(data.a);
  else
    return impl_simd::swizzle<_y, _w, _w, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type ywww() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _w, _w, _w>(data.a);
  else
    return impl_simd::swizzle<_y, _w, _w, _w>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zxxx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _x, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _x, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zxxy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _x, _x, _y>(data.a);
  else
    return impl_simd::swizzle<_z, _x, _x, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zxxz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _x, _x, _z>(data.a);
  else
    return impl_simd::swizzle<_z, _x, _x, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zxxw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _x, _x, _w>(data.a);
  else
    return impl_simd::swizzle<_z, _x, _x, _w>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zxyx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _x, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _x, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zxyy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _x, _y, _y>(data.a);
  else
    return impl_simd::swizzle<_z, _x, _y, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zxyz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _x, _y, _z>(data.a);
  else
    return impl_simd::swizzle<_z, _x, _y, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zxyw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _x, _y, _w>(data.a);
  else
    return impl_simd::swizzle<_z, _x, _y, _w>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zxzx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _x, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _x, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zxzy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _x, _z, _y>(data.a);
  else
    return impl_simd::swizzle<_z, _x, _z, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zxzz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _x, _z, _z>(data.a);
  else
    return impl_simd::swizzle<_z, _x, _z, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zxzw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _x, _z, _w>(data.a);
  else
    return impl_simd::swizzle<_z, _x, _z, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zxwx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _x, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _x, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zxwy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _x, _w, _y>(data.a);
  else
    return impl_simd::swizzle<_z, _x, _w, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zxwz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _x, _w, _z>(data.a);
  else
    return impl_simd::swizzle<_z, _x, _w, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zxww() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _x, _w, _w>(data.a);
  else
    return impl_simd::swizzle<_z, _x, _w, _w>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zyxx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _y, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _y, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zyxy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _y, _x, _y>(data.a);
  else
    return impl_simd::swizzle<_z, _y, _x, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zyxz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _y, _x, _z>(data.a);
  else
    return impl_simd::swizzle<_z, _y, _x, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zyxw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _y, _x, _w>(data.a);
  else
    return impl_simd::swizzle<_z, _y, _x, _w>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zyyx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _y, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _y, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zyyy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _y, _y, _y>(data.a);
  else
    return impl_simd::swizzle<_z, _y, _y, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zyyz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _y, _y, _z>(data.a);
  else
    return impl_simd::swizzle<_z, _y, _y, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zyyw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _y, _y, _w>(data.a);
  else
    return impl_simd::swizzle<_z, _y, _y, _w>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zyzx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _y, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _y, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zyzy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _y, _z, _y>(data.a);
  else
    return impl_simd::swizzle<_z, _y, _z, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zyzz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _y, _z, _z>(data.a);
  else
    return impl_simd::swizzle<_z, _y, _z, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zyzw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _y, _z, _w>(data.a);
  else
    return impl_simd::swizzle<_z, _y, _z, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zywx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _y, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _y, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zywy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _y, _w, _y>(data.a);
  else
    return impl_simd::swizzle<_z, _y, _w, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zywz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _y, _w, _z>(data.a);
  else
    return impl_simd::swizzle<_z, _y, _w, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zyww() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _y, _w, _w>(data.a);
  else
    return impl_simd::swizzle<_z, _y, _w, _w>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zzxx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _z, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _z, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zzxy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _z, _x, _y>(data.a);
  else
    return impl_simd::swizzle<_z, _z, _x, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zzxz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _z, _x, _z>(data.a);
  else
    return impl_simd::swizzle<_z, _z, _x, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zzxw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _z, _x, _w>(data.a);
  else
    return impl_simd::swizzle<_z, _z, _x, _w>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zzyx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _z, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _z, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zzyy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _z, _y, _y>(data.a);
  else
    return impl_simd::swizzle<_z, _z, _y, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zzyz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _z, _y, _z>(data.a);
  else
    return impl_simd::swizzle<_z, _z, _y, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zzyw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _z, _y, _w>(data.a);
  else
    return impl_simd::swizzle<_z, _z, _y, _w>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zzzx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _z, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _z, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zzzy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _z, _z, _y>(data.a);
  else
    return impl_simd::swizzle<_z, _z, _z, _y>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector4_type zzzz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _z, _z, _z>(data.a);
  else
    return impl_simd::swizzle<_z, _z, _z, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zzzw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _z, _z, _w>(data.a);
  else
    return impl_simd::swizzle<_z, _z, _z, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zzwx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _z, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _z, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zzwy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _z, _w, _y>(data.a);
  else
    return impl_simd::swizzle<_z, _z, _w, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zzwz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _z, _w, _z>(data.a);
  else
    return impl_simd::swizzle<_z, _z, _w, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zzww() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _z, _w, _w>(data.a);
  else
    return impl_simd::swizzle<_z, _z, _w, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zwxx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _w, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _w, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zwxy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _w, _x, _y>(data.a);
  else
    return impl_simd::swizzle<_z, _w, _x, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zwxz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _w, _x, _z>(data.a);
  else
    return impl_simd::swizzle<_z, _w, _x, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zwxw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _w, _x, _w>(data.a);
  else
    return impl_simd::swizzle<_z, _w, _x, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zwyx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _w, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _w, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zwyy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _w, _y, _y>(data.a);
  else
    return impl_simd::swizzle<_z, _w, _y, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zwyz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _w, _y, _z>(data.a);
  else
    return impl_simd::swizzle<_z, _w, _y, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zwyw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _w, _y, _w>(data.a);
  else
    return impl_simd::swizzle<_z, _w, _y, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zwzx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _w, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _w, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zwzy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _w, _z, _y>(data.a);
  else
    return impl_simd::swizzle<_z, _w, _z, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zwzz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _w, _z, _z>(data.a);
  else
    return impl_simd::swizzle<_z, _w, _z, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zwzw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _w, _z, _w>(data.a);
  else
    return impl_simd::swizzle<_z, _w, _z, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zwwx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _w, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _w, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zwwy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _w, _w, _y>(data.a);
  else
    return impl_simd::swizzle<_z, _w, _w, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zwwz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _w, _w, _z>(data.a);
  else
    return impl_simd::swizzle<_z, _w, _w, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type zwww() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _w, _w, _w>(data.a);
  else
    return impl_simd::swizzle<_z, _w, _w, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wxxx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _x, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _x, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wxxy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _x, _x, _y>(data.a);
  else
    return impl_simd::swizzle<_w, _x, _x, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wxxz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _x, _x, _z>(data.a);
  else
    return impl_simd::swizzle<_w, _x, _x, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wxxw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _x, _x, _w>(data.a);
  else
    return impl_simd::swizzle<_w, _x, _x, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wxyx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _x, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _x, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wxyy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _x, _y, _y>(data.a);
  else
    return impl_simd::swizzle<_w, _x, _y, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wxyz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _x, _y, _z>(data.a);
  else
    return impl_simd::swizzle<_w, _x, _y, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wxyw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _x, _y, _w>(data.a);
  else
    return impl_simd::swizzle<_w, _x, _y, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wxzx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _x, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _x, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wxzy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _x, _z, _y>(data.a);
  else
    return impl_simd::swizzle<_w, _x, _z, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wxzz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _x, _z, _z>(data.a);
  else
    return impl_simd::swizzle<_w, _x, _z, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wxzw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _x, _z, _w>(data.a);
  else
    return impl_simd::swizzle<_w, _x, _z, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wxwx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _x, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _x, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wxwy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _x, _w, _y>(data.a);
  else
    return impl_simd::swizzle<_w, _x, _w, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wxwz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _x, _w, _z>(data.a);
  else
    return impl_simd::swizzle<_w, _x, _w, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wxww() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _x, _w, _w>(data.a);
  else
    return impl_simd::swizzle<_w, _x, _w, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wyxx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _y, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _y, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wyxy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _y, _x, _y>(data.a);
  else
    return impl_simd::swizzle<_w, _y, _x, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wyxz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _y, _x, _z>(data.a);
  else
    return impl_simd::swizzle<_w, _y, _x, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wyxw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _y, _x, _w>(data.a);
  else
    return impl_simd::swizzle<_w, _y, _x, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wyyx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _y, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _y, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wyyy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _y, _y, _y>(data.a);
  else
    return impl_simd::swizzle<_w, _y, _y, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wyyz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _y, _y, _z>(data.a);
  else
    return impl_simd::swizzle<_w, _y, _y, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wyyw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _y, _y, _w>(data.a);
  else
    return impl_simd::swizzle<_w, _y, _y, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wyzx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _y, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _y, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wyzy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _y, _z, _y>(data.a);
  else
    return impl_simd::swizzle<_w, _y, _z, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wyzz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _y, _z, _z>(data.a);
  else
    return impl_simd::swizzle<_w, _y, _z, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wyzw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _y, _z, _w>(data.a);
  else
    return impl_simd::swizzle<_w, _y, _z, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wywx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _y, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _y, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wywy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _y, _w, _y>(data.a);
  else
    return impl_simd::swizzle<_w, _y, _w, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wywz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _y, _w, _z>(data.a);
  else
    return impl_simd::swizzle<_w, _y, _w, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wyww() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _y, _w, _w>(data.a);
  else
    return impl_simd::swizzle<_w, _y, _w, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wzxx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _z, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _z, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wzxy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _z, _x, _y>(data.a);
  else
    return impl_simd::swizzle<_w, _z, _x, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wzxz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _z, _x, _z>(data.a);
  else
    return impl_simd::swizzle<_w, _z, _x, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wzxw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _z, _x, _w>(data.a);
  else
    return impl_simd::swizzle<_w, _z, _x, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wzyx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _z, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _z, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wzyy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _z, _y, _y>(data.a);
  else
    return impl_simd::swizzle<_w, _z, _y, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wzyz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _z, _y, _z>(data.a);
  else
    return impl_simd::swizzle<_w, _z, _y, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wzyw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _z, _y, _w>(data.a);
  else
    return impl_simd::swizzle<_w, _z, _y, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wzzx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _z, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _z, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wzzy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _z, _z, _y>(data.a);
  else
    return impl_simd::swizzle<_w, _z, _z, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wzzz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _z, _z, _z>(data.a);
  else
    return impl_simd::swizzle<_w, _z, _z, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wzzw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _z, _z, _w>(data.a);
  else
    return impl_simd::swizzle<_w, _z, _z, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wzwx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _z, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _z, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wzwy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _z, _w, _y>(data.a);
  else
    return impl_simd::swizzle<_w, _z, _w, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wzwz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _z, _w, _z>(data.a);
  else
    return impl_simd::swizzle<_w, _z, _w, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wzww() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _z, _w, _w>(data.a);
  else
    return impl_simd::swizzle<_w, _z, _w, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wwxx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _w, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _w, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wwxy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _w, _x, _y>(data.a);
  else
    return impl_simd::swizzle<_w, _w, _x, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wwxz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _w, _x, _z>(data.a);
  else
    return impl_simd::swizzle<_w, _w, _x, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wwxw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _w, _x, _w>(data.a);
  else
    return impl_simd::swizzle<_w, _w, _x, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wwyx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _w, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _w, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wwyy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _w, _y, _y>(data.a);
  else
    return impl_simd::swizzle<_w, _w, _y, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wwyz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _w, _y, _z>(data.a);
  else
    return impl_simd::swizzle<_w, _w, _y, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wwyw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _w, _y, _w>(data.a);
  else
    return impl_simd::swizzle<_w, _w, _y, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wwzx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _w, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _w, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wwzy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _w, _z, _y>(data.a);
  else
    return impl_simd::swizzle<_w, _w, _z, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wwzz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _w, _z, _z>(data.a);
  else
    return impl_simd::swizzle<_w, _w, _z, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wwzw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _w, _z, _w>(data.a);
  else
    return impl_simd::swizzle<_w, _w, _z, _w>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wwwx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _w, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _w, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wwwy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _w, _w, _y>(data.a);
  else
    return impl_simd::swizzle<_w, _w, _w, _y>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wwwz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _w, _w, _z>(data.a);
  else
    return impl_simd::swizzle<_w, _w, _w, _z>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector4_type wwww() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _w, _w, _w>(data.a);
  else
    return impl_simd::swizzle<_w, _w, _w, _w>(data.v);
}
