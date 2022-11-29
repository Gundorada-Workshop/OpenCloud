#pragma once
#include <glm/glm.hpp>
#include <fmt/core.h>
#include <fmt/ranges.h>

#include <array>
#include <cstdint>
#include <cstddef>

// Enum class bitwise operators
#define IMPLEMENT_ENUM_CLASS_BITWISE_OPERATORS(type_)                                                                  \
  inline constexpr type_ operator&(type_ lhs, type_ rhs)                                                        \
  {                                                                                                                    \
    return static_cast<type_>(static_cast<std::underlying_type<type_>::type>(lhs) &                                    \
                              static_cast<std::underlying_type<type_>::type>(rhs));                                    \
  }                                                                                                                    \
  inline constexpr type_ operator|(type_ lhs, type_ rhs)                                                        \
  {                                                                                                                    \
    return static_cast<type_>(static_cast<std::underlying_type<type_>::type>(lhs) |                                    \
                              static_cast<std::underlying_type<type_>::type>(rhs));                                    \
  }                                                                                                                    \
  inline constexpr type_ operator^(type_ lhs, type_ rhs)                                                        \
  {                                                                                                                    \
    return static_cast<type_>(static_cast<std::underlying_type<type_>::type>(lhs) ^                                    \
                              static_cast<std::underlying_type<type_>::type>(rhs));                                    \
  }                                                                                                                    \
  inline constexpr type_ operator~(type_ val)                                                                   \
  {                                                                                                                    \
    return static_cast<type_>(~static_cast<std::underlying_type<type_>::type>(val));                                   \
  }                                                                                                                    \
  inline constexpr type_& operator&=(type_& lhs, type_ rhs)                                                     \
  {                                                                                                                    \
    lhs = static_cast<type_>(static_cast<std::underlying_type<type_>::type>(lhs) &                                     \
                             static_cast<std::underlying_type<type_>::type>(rhs));                                     \
    return lhs;                                                                                                        \
  }                                                                                                                    \
  inline constexpr type_& operator|=(type_& lhs, type_ rhs)                                                     \
  {                                                                                                                    \
    lhs = static_cast<type_>(static_cast<std::underlying_type<type_>::type>(lhs) |                                     \
                             static_cast<std::underlying_type<type_>::type>(rhs));                                     \
    return lhs;                                                                                                        \
  }                                                                                                                    \
  inline constexpr type_& operator^=(type_& lhs, type_ rhs)                                                     \
  {                                                                                                                    \
    lhs = static_cast<type_>(static_cast<std::underlying_type<type_>::type>(lhs) ^                                     \
                             static_cast<std::underlying_type<type_>::type>(rhs));                                     \
    return lhs;                                                                                                        \
  }

// unsigned
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

// signed
using s8     = std::int8_t;
using s16    = std::int16_t;
using s32    = std::int32_t;
using s64    = std::int64_t;
using schar  = signed char;
using sint   = signed int;
using ssize  = std::intmax_t;

// bool
using b8 = u8;
using b16 = u16;
using b32 = u32;
using b64 = u64;

// floating point
using f32 = float;
using f64 = double;

// unknown
using unk8   = u8;
using unk16  = u16;
using unk32  = u32;
using unk64  = u64;

using unk = uint;
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

// wrapper for glm vectors
template<typename type, usize size>
using vec = glm::vec<size, type>;

// vectors
using vec2 = vec<f32, 2>;
using vec3 = vec<f32, 3>;
using vec4 = vec<f32, 4>;

using ivec2 = vec<sint, 2>;
using ivec3 = vec<sint, 3>;
using ivec4 = vec<sint, 4>;

using uvec2 = vec<uint, 2>;
using uvec3 = vec<uint, 3>;
using uvec4 = vec<uint, 4>;

// matrices
using matrix2 = glm::mat2;
using matrix3 = glm::mat3;
using matrix4 = glm::mat4;

template<typename type, usize size>
struct fmt::formatter<vec<type, size>> : formatter<std::string_view>
{
  const auto format(const vec<type, size>& v, format_context& ctx)
  {
    // TODO: find a less ass way to do this
    std::array<type, size> data{ };

    for (usize i = 0; i < size; ++i)
      data[i] = v[i];

    return fmt::format_to(ctx.out(), "vec{}({})", size, fmt::join(data, ","));
  }
};