#pragma once
#include <array>
#include <cstdint>
#include <cstddef>

#include <glm/glm.hpp>

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
using unk32  = u32;
using unk64  = u64;
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

// vectors
using vec2 = glm::vec2;
using vec3 = glm::vec3;
using vec4 = glm::vec4;

using ivec2 = glm::ivec2;
using ivec3 = glm::ivec3;
using ivec4 = glm::ivec4;

using uvec2 = glm::uvec2;
using uvec3 = glm::uvec3;
using uvec4 = glm::uvec4;

// matrices
using matrix2 = glm::mat2;
using matrix3 = glm::mat3;
using matrix4 = glm::mat4;
