#pragma once

#include "common/helpers.h"

#define WARNING_ID_CONDITIONAL_EXPRESSION_IS_CONSTANT 4127
#define WARNING_ID_ASSIGNMENT_WITHIN_CONDITIONAL_STATEMENT 4706
#define WARNING_ID_NAMELESS_STRUCT_UNION 4201

// FILE_DISABLE_WARNING
#if defined(_MSC_VER)
  #define MSVC_WARNING_PUSH \
    __pragma(warning(push))

  #define MSVC_WARNING_POP \
    __pragma(warning(pop))

  #define MSVC_WARNING_SILENCE(id) \
    __pragma(warning(disable:id))
#endif

#if defined(_MSC_VER)
  #define FILE_WARNING_PUSH MSVC_WARNING_PUSH
  #define FILE_WARNING_POP MSVC_WARNING_POP
  #define FILE_WARNING_DISABLE(id) MSVC_WARNING_SILENCE(id)
#elif defined(__GNUG__) || defined(__clang__)
  // TODO
  #define FILE_WARNING_PUSH
  #define FILE_WARNING_POP
  #define FILE_WARNING_DISABLE(id)
#endif

// ALWAYS_INLINE
#if defined(_MSC_VER)
  #define ALWAYS_INLINE __forceinline
#elif defined(__GNUG__) || defined(__clang__)
  #define ALWAYS_INLINE inline __attribute__((__always_inline__))
#endif

// INLINE
#define INLINE inline

#define MAYBE_UNUSED [[maybe_unused]]
#define NO_DISCARD [[nodiscard]]
#define NO_RETURN [[noreturn]]
#define FALLTHROUGH [[fallthrough]]
#define LIKELY [[likely]]
#define UNLIKELY [[unlikely]]

// ALIGN
#if defined(_MSC_VER)
  #define ALIGN(width) __declspec(align(width))
#elif defined(__GNUG__) || defined(__clang__)
  #define ALIGN(width) __attribute__((aligned(width)))
#endif

#define assert_type_size_static(type, expected_size) static_assert(sizeof(type) == expected_size) 

// Enum class bitwise operators
#define IMPLEMENT_ENUM_CLASS_BITWISE_OPERATORS(type_)               \
  ALWAYS_INLINE constexpr type_ operator &(type_ lhs, type_ rhs)    \
  {                                                                 \
    return static_cast<type_>(common::to_underlying(lhs) &          \
                              common::to_underlying(rhs));          \
  }                                                                 \
  ALWAYS_INLINE constexpr type_ operator |(type_ lhs, type_ rhs)    \
  {                                                                 \
    return static_cast<type_>(common::to_underlying(lhs) |          \
                              common::to_underlying(rhs));          \
  }                                                                 \
  ALWAYS_INLINE constexpr type_ operator ^(type_ lhs, type_ rhs)    \
  {                                                                 \
    return static_cast<type_>(common::to_underlying(lhs) ^          \
                              common::to_underlying(rhs));          \
  }                                                                 \
  ALWAYS_INLINE constexpr type_ operator ~(type_ val)               \
  {                                                                 \
    return static_cast<type_>(~common::to_underlying(val));         \
  }                                                                 \
  ALWAYS_INLINE constexpr type_& operator &=(type_& lhs, type_ rhs) \
  {                                                                 \
    lhs = static_cast<type_>(common::to_underlying(lhs) &           \
                             common::to_underlying(rhs));           \
    return lhs;                                                     \
  }                                                                 \
  ALWAYS_INLINE constexpr type_& operator |=(type_& lhs, type_ rhs) \
  {                                                                 \
    lhs = static_cast<type_>(common::to_underlying(lhs) |           \
                             common::to_underlying(rhs));           \
    return lhs;                                                     \
  }                                                                 \
  ALWAYS_INLINE constexpr type_& operator ^=(type_& lhs, type_ rhs) \
  {                                                                 \
    lhs = static_cast<type_>(common::to_underlying(lhs) ^           \
                             common::to_underlying(rhs));           \
    return lhs;                                                     \
  }
