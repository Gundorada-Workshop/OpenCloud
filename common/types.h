#pragma once
#include <array>
#include <cstdint>
#include <cstddef>

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

template<typename usize S>
using ivec = std::array<s32, S>;

using ivec4  = ivec<4>;
using ivec3  = ivec<3>;

// floating point
using f32 = float;
using f64 = double;

template<typename usize S>
using vec = std::array<f32, S>;

using vec4 = vec<4>;
using vec3 = vec<3>;

using matrix4 = std::array<vec4, 4>;
