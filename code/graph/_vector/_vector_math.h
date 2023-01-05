#pragma once
#include "graph/vector.h"

namespace graph
{
  // compute the dot product of two vectors
  template<typename type, usize size>
  inline type vector_dot_product(const vector<type, size>& a, const vector<type, size>& b)
  {
    return detail::vector_impl_sse<type>::dot<size>(a.data.v, b.data.v);
  }

  // compute the cross product of two vectors
  template<typename type, usize size>
  inline vector<type, size> vector_cross_product(const vector<type, size>& a, const vector<type, size>& b)
  {
    return detail::vector_impl_sse<type>::cross(a.data.v, b.data.v);
  }

  // compute the magnitude of a vector
  template<typename type, usize size>
  inline type vector_magnitude(const vector<type, size>& a)
  {
    return detail::vector_impl_sse<type>::mag<size>(a.data.v);
  }

  // normalize a vector (make it's magnitude 1)
  template<typename type, usize size>
  inline vector<type, size> vector_normalize(const vector<type, size>& a)
  {
    return detail::vector_impl_sse<type>::norm<size>(a.data.v);
  }

  // compute the distance between two vectors
  template<typename type, usize size>
  inline type vector_distance(const vector<type, size>& a, const vector<type, size>& b)
  {
    return detail::vector_impl_sse<type>::distance<size>(a.data.v, b.data.v);
  }

  // compute the squared distance between two vectors
  template<typename type, usize size>
  inline type vector_distance_squared(const vector<type, size>& a, const vector<type, size>& b)
  {
    return detail::vector_impl_sse<type>::distance_squared<size>(a.data.v, b.data.v);
  }

  // returns a vector consisting of the maximum values of two vectors
  template<typename type, usize size>
  inline vector<type, size> vector_max(const vector<type, size>& a, const vector<type, size>& b)
  {
    return detail::vector_impl_sse<type>::max(a.data.v, b.data.v);
  }

  // returns a vector consisting of the minimum values of two vectors
  template<typename type, usize size>
  inline vector<type, size> vector_min(const vector<type, size>& a, const vector<type, size>& b)
  {
    return detail::vector_impl_sse<type>::min(a.data.v, b.data.v);
  }

  // compute the maximum values of two or more vectors
  template<typename type, usize size>
  inline vector<type, size> vector_max(std::initializer_list<vector<type, size>> ilist)
  {
    auto res = vector<type, size>::min();

    for (const auto& item : ilist)
      res = detail::vector_impl_sse<type>::max(res.data.v, item.data.v);

    return res;
  }

  // compute the minimum values of two or more vectors
  template<typename type, usize size>
  inline vector<type, size> vector_min(std::initializer_list<vector<type, size>> ilist)
  {
    auto res = vector<type, size>::max();

    for (const auto& item : ilist)
      res = detail::vector_impl_sse<type>::min(res.data.v, item.data.v);

    return res;
  }

  // find both the minimum and maximum values of two vectors
  // returns a pair with min as first and max as second
  template<typename type, usize size>
  inline std::pair<vector<type, size>, vector<type, size>> vector_minmax(const vector<type, size>& a, const vector<type, size>& b)
  {
    const auto min = detail::vector_impl_sse<type>::min(a.data.v, b.data.v);
    const auto max = detail::vector_impl_sse<type>::min(a.data.v, b.data.v);

    return { min, max };
  }

  // find both the minimum and maximum values of two or more vectors
  // returns a pair with min as first and max as second
  template<typename type, usize size>
  inline std::pair<vector<type, size>, vector<type, size>> vector_minmax(std::initializer_list<vector<type, size>> ilist)
  {
    auto min = vector<type, size>::max();
    auto max = vector<type, size>::min();

    for (const auto& item : ilist)
    {
      min = detail::vector_impl_sse<type>::min(min.data.v, item.data.v);
      max = detail::vector_impl_sse<type>::max(max.data.v, item.data.v);
    }

    return { min, max };
  }

  // compute the absolute values of a vector
  template<typename type, usize size>
  inline vector<type, size> vector_abs(const vector<type, size>& v)
  {
    return detail::vector_impl_sse<type>::abs(v.data.v);
  }

  // blend two vectors based on mask
  template<typename type, usize size>
  inline vector<type, size> vector_blend(const vector<type, size>& a, const vector<type, size>& b, const vector<type, size>& mask)
  {
    return detail::vector_impl_sse<type>::blend(a.data.v, b.data.v, mask.data.v);
  }

  template<typename type, usize size>
  inline bool vector_any(const vector<type, size>& mask)
  {
    return detail::vector_impl_sse<type>::any<size>(mask.data.v);
  }

  template<typename type, usize size>
  inline bool vector_all(const vector<type, size>& mask)
  {
    return detail::vector_impl_sse<type>::all<size>(mask.data.v);
  }
}