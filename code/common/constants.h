#pragma once

#include <limits>

#include "common/types.h"

namespace common::constants
{
  template<typename type>
  using limits = std::numeric_limits<type>;

  // unsigned max
  constexpr usize u8_max  = limits<u8>::max();
  constexpr usize u16_max = limits<u16>::max();
  constexpr usize u32_max = limits<u32>::max();
  constexpr usize u64_max = limits<u64>::max();

  // unsigned min
  constexpr usize u8_min  = limits<u8>::min();
  constexpr usize u16_min = limits<u16>::min();
  constexpr usize u32_min = limits<u32>::min();
  constexpr usize u64_min = limits<u64>::min();

  // signed max
  constexpr usize s8_max  = limits<s8>::max();
  constexpr usize s16_max = limits<s16>::max();
  constexpr usize s32_max = limits<s32>::max();
  constexpr usize s64_max = limits<s64>::max();

  // signed min
  constexpr usize s8_min  = limits<s8>::min();
  constexpr usize s16_min = limits<s16>::min();
  constexpr usize s32_min = limits<s32>::min();
  constexpr usize s64_min = limits<s64>::min();

  // float max
  constexpr f32 f32_max = limits<f32>::max();
  constexpr f64 f64_max = limits<f64>::max();

  // float min
  constexpr f32 f32_min = limits<f32>::min();
  constexpr f64 f64_min = limits<f64>::min();
}