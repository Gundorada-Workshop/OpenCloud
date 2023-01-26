#pragma once
#include "common/types.h"

#include "graph/_vector/_vector_common.h"

namespace graph::detail
{
  template<typename type>
  struct vector_traits_cxp;

  template<>
  struct vector_traits_cxp<f32>
  {
    using type = std::array<f32, 4>;
  };

  template<>
  struct vector_traits_cxp<f64>
  {
    using type = std::array<f64, 2>;
  };

  template<>
  struct vector_traits_cxp<u32>
  {
    using type = std::array<u32, 4>;
  };

  template<>
  struct vector_traits_cxp<u64>
  {
    using type = std::array<u64, 2>;
  };

  template<>
  struct vector_traits_cxp<s32>
  {
    using type = std::array<s32, 4>;
  };

  template<>
  struct vector_traits_cxp<s64>
  {
    using type = std::array<s64, 2>;
  };

  template<typename type>
  struct vector_impl_cxp
  {
    using traits = vector_traits_cxp<type>;

    template<typename u = type, typename v = typename traits::type>
    static inline constexpr v set(const u& a)
    {
      v out{ };

      for (usize i = 0; i < out.size(); i++)
        out[i] = a;

      return out;
    }

    template<typename u = type, typename v = typename traits::type>
    static inline constexpr v set(const u& a, const u& b)
    {
      v out{ };

      for (usize i = 0; i < out.size(); i += 2)
      {
        out[i + 0] = a;
        out[i + 1] = b;
      }

      return out;
    }

    template<typename u = type, typename v = typename traits::type>
    static inline constexpr v set(const u& a, const u& b, const u& c, const u& d)
    {
      v out{ };

      for (usize i = 0; i < out.size(); i += 4)
      {
        out[i + 0] = a;
        out[i + 1] = b;
        out[i + 2] = c;
        out[i + 3] = d;
      }

      return out;
    }

    template<element el, typename u = type, typename v = typename traits::type>
    static inline constexpr u extract(const v& a)
    {
      return a[common::to_underlying(el)];
    }

    template<element e0, element e1, element e2, element e3, typename u = type, typename v = typename traits::type>
    static inline v swizzle(const v& a)
    {
      v out{ };

      // TODO
      out[0] = a[common::to_underlying(e0)];
      out[1] = a[common::to_underlying(e1)];
      out[2] = a[common::to_underlying(e2)];
      out[3] = a[common::to_underlying(e3)];

      return out;
    }

    template<element e0, element e1, element e2, element e3, typename u = type, typename v = typename traits::type>
    static inline v shuffle(const v& a, const v& b)
    {
      v out{ };

      // TODO
      out[0] = a[common::to_underlying(e0)];
      out[1] = a[common::to_underlying(e1)];
      out[2] = b[common::to_underlying(e2)];
      out[3] = b[common::to_underlying(e3)];

      return out;
    }

    template<typename u = type, typename v = typename traits::type>
    static inline constexpr v add(const v& lhs, const v& rhs)
    {
      v out{ };

      for (usize i = 0; i < out.size(); i++)
        out[i] = lhs[i] + rhs[i];

      return out;
    }

    template<typename u = type, typename v = typename traits::type>
    static inline constexpr v sub(const v& lhs, const v& rhs)
    {
      v out{ };

      for (usize i = 0; i < out.size(); i++)
        out[i] = lhs[i] - rhs[i];

      return out;
    }

    template<typename u = type, typename v = typename traits::type>
    static inline constexpr v div(const v& lhs, const v& rhs)
    {
      v out{ };

      for (usize i = 0; i < out.size(); i++)
        out[i] = lhs[i] / rhs[i];

      return out;
    }

    template<typename u = type, typename v = typename traits::type>
    static inline constexpr v mul(const v& lhs, const v& rhs)
    {
      v out{ };

      for (usize i = 0; i < out.size(); i++)
        out[i] = lhs[i] * rhs[i];

      return out;
    }

    template<typename u = type, typename v = typename traits::type>
    static inline v equal(const v& lhs, const v& rhs)
    {
      v out{ };

      for (usize i = 0; i < out.size(); i++)
      {
        if (lhs[i] == rhs[i])
          out[i] = std::bit_cast<u>(0xFFFFFFFF);
        else
          out[i] = 0;
      }

      return out;
    }

    template<typename u = type, typename v = typename traits::type>
    static inline v less_than(const v& lhs, const v& rhs)
    {
      v out{ };

      for (usize i = 0; i < out.size(); i++)
      {
        if (lhs[i] < rhs[i])
          out[i] = std::bit_cast<u>(0xFFFFFFFF);
        else
          out[i] = 0;
      }

      return out;
    }

    template<typename u = type, typename v = typename traits::type>
    static inline v less_than_equal(const v& lhs, const v& rhs)
    {
      v out{ };

      for (usize i = 0; i < out.size(); i++)
      {
        if (lhs[i] <= rhs[i])
          out[i] = std::bit_cast<u>(0xFFFFFFFF);
        else
          out[i] = 0;
      }

      return out;
    }

    template<typename u = type, typename v = typename traits::type>
    static inline v greater_than(const v& lhs, const v& rhs)
    {
      v out{ };

      for (usize i = 0; i < out.size(); i++)
      {
        if (lhs[i] > rhs[i])
          out[i] = std::bit_cast<u>(0xFFFFFFFF);
        else
          out[i] = 0;
      }

      return out;
    }

    template<typename u = type, typename v = typename traits::type>
    static inline v greater_than_equal(const v& lhs, const v& rhs)
    {
      v out{ };

      for (usize i = 0; i < out.size(); i++)
      {
        if (lhs[i] >= rhs[i])
          out[i] = std::bit_cast<u>(0xFFFFFFFF);
        else
          out[i] = 0;
      }

      return out;
    }
  };
}