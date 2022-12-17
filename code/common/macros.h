#pragma once

#if defined(_MSC_VER)
#define WARNING_ID_CONDITIONAL_EXPRESSION_IS_CONSTANT 4127
#define WARNING_ID_ASSIGNMENT_WITHIN_CONDITIONAL_STATEMENT 4706

#define MSVC_SILENCE_WARNING(id) \
  __pragma(warning(disable:id))

#define FILE_DISABLE_WARNING(id) MSVC_SILENCE_WARNING(id)

#define ALWAYS_INLINE __forceinline
#define INLINE inline
#endif

#define MAYBE_UNUSED [[maybe_unused]]
#define NO_DISCARD [[nodiscard]]
#define NO_RETURN [[noreturn]]
#define FALLTHROUGH [[fallthrough]]
#define LIKELY [[likely]]
#define UNLIKELY [[unlikely]]