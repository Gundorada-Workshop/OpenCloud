#pragma once
#include "types.h"

namespace common
{
  // returns true if value is aligned to align_to
  template<typename T>
  constexpr bool aligned(T value, uint align_to)
  {
    const T align = static_cast<T>(align_to);

    return (value % align) == 0;
  }

  // aligns the value up to align_to
  template<typename T>
  constexpr T align_up(T value, uint align_to)
  {
    const T align = static_cast<T>(align_to);

    return (value + align - 1) / align * align;
  }

  // aligns the value down to align_to
  template<typename T>
  constexpr T align_down(T value, uint align_to)
  {
    const T align = static_cast<T>(align_to);

    return value / align * align;
  }
}
