#pragma once
#include <array>

#include "common/types.h"
#include "graph/vector.h"

namespace graph
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

  //template<typename type, usize rows, usize columns>
  //inline matrix<type, rows, columns> matrix_transpose(const matrix<type, rows, columns>& m)
  //{
  //  // we need a mat that is of transposed size
  //  // for symetrical matrices this will just be the same mat

  //  //auto xy0xy1 = _mm_shuffle_ps(m.rows[0].v, m.rows[1].v, _MM_SHUFFLE(1, 0, 1, 0));
  //  //auto zw0zw1 = _mm_shuffle_ps(m.rows[0].v, m.rows[1].v, _MM_SHUFFLE(3, 2, 3, 2));

  //  //auto xy2xy3 = _mm_shuffle_ps(m.rows[2].v, m.rows[3].v, _MM_SHUFFLE(1, 0, 1, 0));
  //  //auto zw2zw3 = _mm_shuffle_ps(m.rows[2].v, m.rows[3].v, _MM_SHUFFLE(3, 2, 3, 2));

  //  matrix<type, rows, columns> out;
  //  //out.rows[0].v = _mm_shuffle_ps(xy0xy1, xy2xy3, _MM_SHUFFLE(2, 0, 2, 0));
  //  //out.rows[1].v = _mm_shuffle_ps(xy0xy1, xy2xy3, _MM_SHUFFLE(3, 1, 3, 1));
  //  //out.rows[2].v = _mm_shuffle_ps(zw0zw1, zw2zw3, _MM_SHUFFLE(2, 0, 2, 0));
  //  //out.rows[3].v = _mm_shuffle_ps(zw0zw1, zw2zw3, _MM_SHUFFLE(3, 1, 3, 1));

  //  return out;
  //}
}