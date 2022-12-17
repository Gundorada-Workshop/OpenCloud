template<typename u = type>
requires is_vec_2<size>
inline constexpr vector2_type xx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _x, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _x, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector2_type xy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _y, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _y, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector2_type xz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _z, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _z, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector2_type xw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _w, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _w, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector2_type yx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _x, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _x, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector2_type yy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _y, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _y, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector2_type yz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _z, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _z, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector2_type yw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _w, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _w, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector2_type zx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _x, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _x, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector2_type zy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _y, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _y, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector2_type zz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _z, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _z, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector2_type zw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _w, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _w, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector2_type wx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _x, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _x, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector2_type wy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _y, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _y, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector2_type wz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _z, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _z, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector2_type ww() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _w, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _w, _x, _x>(data.v);
}
