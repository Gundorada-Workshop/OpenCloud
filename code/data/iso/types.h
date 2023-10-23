#pragma once
#include <fmt/format.h>

#include "common/types.h"

#include "data/iso/dual_endian.h"

namespace data
{
  // 8-bit unsigned numerical values
  using iso711_t = u8;

  // 8-bit signed numerical values
  using iso712_t = s8;

  // 16-bit numerical values le
  using iso721_t = u16;

  // 16-bit numerical values be
  using iso722_t = u16;

  // 16-bit numerical values de
  using iso723_t = iso_dual_endian<u16>;

  // 32-bit numerical values le
  using iso731_t = u32;

  // 32-bit numerical values be
  using iso732_t = u32;

  // 32-but numerical values de
  using iso733_t = iso_dual_endian<u32>;

  using achar = char;
  using dchar = char;
}

// dual endian u16 entry
template<>
struct fmt::formatter<data::iso723_t> : formatter<std::string_view>
{
  auto format(data::iso723_t de, format_context& ctx)
  {
    return fmt::format_to(ctx.out(), "{}", data::iso_get_native_endian(de));
  }
};

// dual endian u32 entry
template<>
struct fmt::formatter<data::iso733_t> : formatter<std::string_view>
{
  auto format(data::iso733_t de, format_context& ctx)
  {
    return fmt::format_to(ctx.out(), "{}", data::iso_get_native_endian(de));
  }
};
