#pragma once
#include <bit>
#include <array>

namespace data
{
  // some stuff is le followed by be (dual endian)
  // small helper for dealing with that
  template<typename T>
  struct iso_dual_endian
  {
    std::array<T, 2> data{ };
  };

  template<typename T>
  static inline T iso_get_native_endian(const iso_dual_endian<T>& de)
  {
    if constexpr (std::endian::native == std::endian::little)
      return de.data[0];
    else
      return de.data[1];
  }
}