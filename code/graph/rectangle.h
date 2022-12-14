#pragma once
#include "common/types.h"
#include "common/strings.h"

#include "graph/vector.h"

namespace graph
{
  template<typename type>
  class rectangle
  {
  public:
    using storage_type = vector4<type>;
    using point_type = vector2<type>;

    friend struct fmt::formatter<rectangle<type>>;

    constexpr rectangle() = default;

    // construct from a vector type
    explicit constexpr rectangle(storage_type v)
      : m_data{ v }
    {
    }

    // consturct by values
    explicit constexpr rectangle(type x0, type y0, type x1, type y1)
      : m_data{ x0, y0, x1, y1 }
    {
    }

    // construct a rectangle from two points xy0 and xy1
    // assumes top left origin (meaning x0 < x1 and y0 < y1)
    static constexpr rectangle<type> from_points(type x0, type y0, type x1, type y1)
    {
      return rectangle<type>{ x0, y0, x1, y1 };
    }

    // construct from a single point and an extent
    static constexpr rectangle<type> from_extent(type x, type y, type width, type height)
    {
      const point_type p0{ x, y };
      const point_type extent{ width, height };

      const point_type p1 = p0 + extent;

      return rectangle<type>{ p0.x(), p0.y(), p1.x(), p1.y() };
    }

    // construct from an extent assuming top left is 0,0
    static constexpr rectangle<type> from_extent(type width, type height)
    {
      return rectangle<type>{ 0, 0, width, height };
    }

    // get the width of the rectangle
    constexpr type width() const
    {
      return m_data.z() - m_data.x();
    }

    // get the height of the rectangle
    constexpr type height() const
    {
      return m_data.w() - m_data.y();
    }

    // get the extent (width, height)
    constexpr point_type extent()
    {
      return m_data.zw() - m_data.xy();
    }

    // get the top left origin point (x, y)
    constexpr point_type origin()
    {
      return m_data.xy();
    }

  private:
    // vector storage
    storage_type m_data{ };
  };

  using irect = rectangle<sint>;
  using urect = rectangle<uint>;
  using rect  = rectangle<f32>;
}

template<typename rect_type>
struct fmt::formatter<graph::rectangle<rect_type>> : formatter<std::string_view>
{
  auto format(const graph::rectangle<rect_type>& rect, format_context& ctx)
  {
    return fmt::format_to(ctx.out(), "rect<{}>({}, {}, {}, {})",
      typeid(rect_type).name(), rect.m_data.x(), rect.m_data.y(), rect.m_data.z(), rect.m_data.w());
  }
};