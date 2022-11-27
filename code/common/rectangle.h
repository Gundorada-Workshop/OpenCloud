#pragma once
#include "common/types.h"

namespace common
{
  template<typename type>
  class rectangle
  {
  public:
    using storage_type = vec<type, 4>;
    using point_type = vec<type, 2>;

    rectangle(storage_type v)
      : m_data{ v }
    {
    }

    static constexpr rectangle<type> from_points(type x0, type y0, type x1, type y1)
    {
      return storage_type{ x0, y0, x1, y1 };
    }

    static constexpr rectangle<type> from_extent(type x, type y, type width, type height)
    {
      return storage_type{ x, y, x + width, y + height };
    }

    constexpr type width() const
    {
      return m_data.z - m_data.x;
    }

    constexpr type height() const
    {
      return m_data.w - m_data.y;
    }

    constexpr point_type extent()
    {
      return { width(), height() };
    }

    constexpr point_type origin()
    {
      return { m_data.x, m_data.y };
    }

  private:
    storage_type m_data{ 0, 0, 0, 0 };
  };
}

using irect = common::rectangle<sint>;
using urect = common::rectangle<uint>;
using rect  = common::rectangle<f32>;