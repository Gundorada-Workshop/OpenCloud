template<typename u = type>
requires is_vec_2<size>
inline constexpr vector3_type xxx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _x, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _x, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector3_type xxy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _x, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _x, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector3_type xxz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _x, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _x, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type xxw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _x, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _x, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector3_type xyx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _y, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _y, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector3_type xyy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _y, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _y, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector3_type xyz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _y, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _y, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type xyw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _y, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _y, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector3_type xzx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _z, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _z, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector3_type xzy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _z, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _z, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector3_type xzz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _z, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _z, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type xzw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _z, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _z, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type xwx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _w, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _w, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type xwy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _w, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _w, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type xwz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _w, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _w, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type xww() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_x, _w, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_x, _w, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector3_type yxx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _x, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _x, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector3_type yxy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _x, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _x, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector3_type yxz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _x, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _x, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type yxw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _x, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _x, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector3_type yyx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _y, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _y, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_2<size>
inline constexpr vector3_type yyy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _y, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _y, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector3_type yyz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _y, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _y, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type yyw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _y, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _y, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector3_type yzx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _z, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _z, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector3_type yzy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _z, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _z, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector3_type yzz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _z, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _z, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type yzw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _z, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _z, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type ywx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _w, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _w, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type ywy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _w, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _w, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type ywz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _w, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _w, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type yww() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_y, _w, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_y, _w, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector3_type zxx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _x, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _x, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector3_type zxy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _x, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _x, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector3_type zxz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _x, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _x, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type zxw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _x, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _x, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector3_type zyx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _y, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _y, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector3_type zyy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _y, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _y, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector3_type zyz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _y, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _y, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type zyw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _y, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _y, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector3_type zzx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _z, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _z, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector3_type zzy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _z, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _z, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_3<size>
inline constexpr vector3_type zzz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _z, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _z, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type zzw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _z, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _z, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type zwx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _w, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _w, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type zwy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _w, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _w, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type zwz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _w, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _w, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type zww() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_z, _w, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_z, _w, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type wxx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _x, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _x, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type wxy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _x, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _x, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type wxz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _x, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _x, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type wxw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _x, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _x, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type wyx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _y, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _y, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type wyy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _y, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _y, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type wyz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _y, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _y, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type wyw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _y, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _y, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type wzx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _z, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _z, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type wzy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _z, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _z, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type wzz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _z, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _z, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type wzw() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _z, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _z, _w, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type wwx() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _w, _x, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _w, _x, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type wwy() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _w, _y, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _w, _y, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type wwz() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _w, _z, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _w, _z, _x>(data.v);
}

template<typename u = type>
requires is_vec_4<size>
inline constexpr vector3_type www() const
{
  if (std::is_constant_evaluated())
    return impl_cxpr::swizzle<_w, _w, _w, _x>(data.a);
  else
    return impl_simd::swizzle<_w, _w, _w, _x>(data.v);
}
