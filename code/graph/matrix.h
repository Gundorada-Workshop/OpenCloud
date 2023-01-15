#pragma once
#include <array>

#include "common/types.h"
#include "common/macros.h"

#include "graph/vector.h"

namespace graph
{
  template<typename type, usize row_count, usize column_count>
  struct matrix
  {
    using vector_type = vector<type, column_count>;

    ALWAYS_INLINE static consteval usize rows()
    {
      return row_count;
    }

    ALWAYS_INLINE static consteval usize columns()
    {
      return column_count;
    }

    std::array<vector_type, row_count> rows_;
  };

  template<typename type, usize rows, usize columns, typename matrix_type = matrix<type, rows, columns>>
  ALWAYS_INLINE constexpr auto operator+(const matrix_type& lhs, const type rhs) -> matrix_type
  {
    matrix_type out;
    for (usize i = 0; i < matrix_type::rows(); ++i)
      out.rows_[i] = lhs.rows_[i] + rhs;

    return out;
  }

  template<typename type, usize rows, usize columns, typename matrix_type = matrix<type, rows, columns>>
  ALWAYS_INLINE constexpr auto operator-(const matrix_type& lhs, const type rhs) -> matrix_type
  {
    matrix_type out;
    for (usize i = 0; i < matrix_type::rows(); ++i)
      out.rows_[i] = lhs.rows_[i] - rhs;

    return out;
  }

  template<typename type, usize rows, usize columns, typename matrix_type = matrix<type, rows, columns>>
  ALWAYS_INLINE constexpr auto operator*(const matrix_type& lhs, const type rhs) -> matrix_type
  {
    matrix_type out;
    for (usize i = 0; i < matrix_type::rows(); ++i)
      out.rows_[i] = lhs.rows_[i] * rhs;

    return out;
  }

  template<typename type, usize rows, usize columns, typename matrix_type = matrix<type, rows, columns>>
  ALWAYS_INLINE constexpr auto operator/(const matrix_type& lhs, const type rhs) -> matrix_type
  {
    matrix_type out;
    for (usize i = 0; i < matrix_type::rows(); ++i)
      out.rows_[i] = lhs.rows_[i] / rhs;

    return out;
  }

  template<typename type, usize rows, usize columns, typename matrix_type = matrix<type, rows, columns>>
  ALWAYS_INLINE constexpr auto operator+(const matrix_type& lhs, const matrix_type& rhs) -> matrix_type
  {
    matrix_type out;
    for (usize i = 0; i < matrix_type::rows(); ++i)
      out.rows_[i] = lhs.rows_[i] + rhs.rows_[i];

    return out;
  }

  template<typename type, usize rows, usize columns, typename matrix_type = matrix<type, rows, columns>>
  ALWAYS_INLINE constexpr auto operator-(const matrix_type& lhs, const matrix_type& rhs) -> matrix_type
  {
    matrix_type out;
    for (usize i = 0; i < matrix_type::rows(); ++i)
      out.rows_[i] = lhs.rows_[i] - rhs.rows_[i];

    return out;
  }

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

template<usize rows, usize columns>
using mat = graph::matrix<f32, rows, columns>;

using mat4 = mat<4, 4>;
using mat3 = mat<3, 3>;
using mat2 = mat<2, 2>;