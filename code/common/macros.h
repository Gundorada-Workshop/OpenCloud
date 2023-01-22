#pragma once

#define WARNING_ID_CONDITIONAL_EXPRESSION_IS_CONSTANT 4127
#define WARNING_ID_ASSIGNMENT_WITHIN_CONDITIONAL_STATEMENT 4706

// FILE_DISABLE_WARNING
#if defined(_MSC_VER)
  #define MSVC_SILENCE_WARNING(id) \
    __pragma(warning(disable:id))
  #define FILE_DISABLE_WARNING(id) MSVC_SILENCE_WARNING(id)
#elif defined(__GNUG__) || defined(__clang__)
  #define MSVC_SILENCE_WARNING(id)
  #define FILE_DISABLE_WARNING(id)
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

// Enum class bitwise operators
#define IMPLEMENT_ENUM_CLASS_BITWISE_OPERATORS(type_)                                                                  \
  ALWAYS_INLINE constexpr type_ operator&(type_ lhs, type_ rhs)                                                        \
  {                                                                                                                    \
    return static_cast<type_>(static_cast<std::underlying_type<type_>::type>(lhs) &                                    \
                              static_cast<std::underlying_type<type_>::type>(rhs));                                    \
  }                                                                                                                    \
  ALWAYS_INLINE constexpr type_ operator|(type_ lhs, type_ rhs)                                                        \
  {                                                                                                                    \
    return static_cast<type_>(static_cast<std::underlying_type<type_>::type>(lhs) |                                    \
                              static_cast<std::underlying_type<type_>::type>(rhs));                                    \
  }                                                                                                                    \
  ALWAYS_INLINE constexpr type_ operator^(type_ lhs, type_ rhs)                                                        \
  {                                                                                                                    \
    return static_cast<type_>(static_cast<std::underlying_type<type_>::type>(lhs) ^                                    \
                              static_cast<std::underlying_type<type_>::type>(rhs));                                    \
  }                                                                                                                    \
  ALWAYS_INLINE constexpr type_ operator~(type_ val)                                                                   \
  {                                                                                                                    \
    return static_cast<type_>(~static_cast<std::underlying_type<type_>::type>(val));                                   \
  }                                                                                                                    \
  ALWAYS_INLINE constexpr type_& operator&=(type_& lhs, type_ rhs)                                                     \
  {                                                                                                                    \
    lhs = static_cast<type_>(static_cast<std::underlying_type<type_>::type>(lhs) &                                     \
                             static_cast<std::underlying_type<type_>::type>(rhs));                                     \
    return lhs;                                                                                                        \
  }                                                                                                                    \
  ALWAYS_INLINE constexpr type_& operator|=(type_& lhs, type_ rhs)                                                     \
  {                                                                                                                    \
    lhs = static_cast<type_>(static_cast<std::underlying_type<type_>::type>(lhs) |                                     \
                             static_cast<std::underlying_type<type_>::type>(rhs));                                     \
    return lhs;                                                                                                        \
  }                                                                                                                    \
  ALWAYS_INLINE constexpr type_& operator^=(type_& lhs, type_ rhs)                                                     \
  {                                                                                                                    \
    lhs = static_cast<type_>(static_cast<std::underlying_type<type_>::type>(lhs) ^                                     \
                             static_cast<std::underlying_type<type_>::type>(rhs));                                     \
    return lhs;                                                                                                        \
  }
