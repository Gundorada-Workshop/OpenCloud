// SPDX-License-Identifier: MIT

#pragma once
#include <array>
#include <cstdint>
#include <cstddef>

// unsigned integer
using u8     = std::uint8_t;
using u16    = std::uint16_t;
using u32    = std::uint32_t;
using u64    = std::uint64_t;
using uchar  = unsigned char;
using ushort = unsigned short;
using uint   = unsigned int;
using ulong  = unsigned long;
using ullong = unsigned long long;
using usize  = std::size_t;
using uptr   = std::uintptr_t;

// signed integer
using s8     = std::int8_t;
using s16    = std::int16_t;
using s32    = std::int32_t;
using s64    = std::int64_t;
using schar  = signed char;
using sint   = signed int;
using ssize  = std::intmax_t;

// wrapper for bools of a defined size
template<typename underlying_type>
requires std::is_unsigned_v<underlying_type>
struct portable_bool
{
  using type = underlying_type;

  constexpr portable_bool() = default;

  constexpr portable_bool(bool init)
  {
    set(init);
  }

  constexpr bool set(const bool val)
  {
    value_ = static_cast<type>(val);

    return value_;
  }

  constexpr explicit operator bool() const
  {
    return static_cast<bool>(value_);
  }

  constexpr bool operator =(bool val)
  {
    return set(val);
  }

  template<typename other>
  static constexpr portable_bool<type> from(other val)
  {
    return portable_bool<type>{static_cast<bool>(val)};
  }

  type value_{ 0 };
};

// boolean
using b8  = portable_bool<u8>;
using b16 = portable_bool<u16>;
using b32 = portable_bool<u32>;
using b64 = portable_bool<u64>;

// floating point
using f32 = float;
using f64 = double;

// unknown
using unk8  = u8;
using unk16 = u16;
using unk32 = u32;
using unk64 = u64;

using unk = sint;
using unkptr = void*; //note: ps2 ptr is 32 bit

template<usize size>
struct unkstr
{
  char data[size];
};

template<usize size>
struct unks
{
  std::array<u8, size> data;
};
