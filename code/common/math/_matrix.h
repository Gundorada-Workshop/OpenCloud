#pragma once
#include <array>

#include "common/types.h"
#include "common/math/_vector.h"

namespace common::math
{
  //template<typename type, usize row_count, usize column_count>
  //struct matrix
  //{
  //  using vector_type = vector<type, column_count>;
  //  using storage_type = vector_type::storage_type;

  //  std::array<storage_type, row_count> rows;
  //};

  //template<typename type, usize rows, usize columns>
  //static inline vector<type, columns> operator*(const vector<type, columns>& v, const matrix<type, rows, columns>& m)
  //{
  //  using enum detail::element;

  //  std::array swizzle_matrix =
  //  {
  //    detail::vector_swizzle<type, _x, _x, _x, _x>::swizzle(v.data.v),
  //    detail::vector_swizzle<type, _y, _y, _y, _y>::swizzle(v.data.v),
  //    detail::vector_swizzle<type, _z, _z, _z, _z>::swizzle(v.data.v),
  //    detail::vector_swizzle<type, _w, _w, _w, _w>::swizzle(v.data.v)
  //  };

  //  auto res = vector<type, columns>::zero();

  //  for (usize i = 0; i < rows; ++i)
  //    res.data.v = detail::vector_math<type>::madd(swizzle_matrix[i].v, m.rows[i].v, res.data.v);

  //  return res;
  //}
}