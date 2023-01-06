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