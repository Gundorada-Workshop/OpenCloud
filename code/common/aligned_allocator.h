// SPDX-License-Identifier: MIT

#pragma once
#include "common/types.h"
#include "common/macros.h"

namespace common
{
  template<typename type, uint alignment>
  struct aligned_allocator
  {
    using value_type = type;

    using reference  = type&;
    using pointer    = type*;

    using const_reference = const type&;
    using const_pointer   = const type*;
    
    using size_type       = usize;
    using difference_type = ptrdiff_t;

    template<typename u>
    struct rebind
    {
      using other = aligned_allocator<u, alignment>;
    };

    ALWAYS_INLINE aligned_allocator() noexcept = default;
    ALWAYS_INLINE ~aligned_allocator() noexcept = default;

    ALWAYS_INLINE aligned_allocator(const aligned_allocator&) noexcept
    {
    };

    template<typename u>
    ALWAYS_INLINE aligned_allocator(const aligned_allocator<u, alignment>&) noexcept
    {
    };

    ALWAYS_INLINE pointer address(reference r) noexcept
    {
      return &r;
    }

    ALWAYS_INLINE const_pointer address(const_reference& r) noexcept
    {
      return &r;
    }

    ALWAYS_INLINE NO_DISCARD pointer allocate(size_type n) noexcept
    {
      return reinterpret_cast<pointer>(_aligned_malloc(sizeof(value_type) * n, alignment));
    }

    ALWAYS_INLINE void deallocate(pointer p, size_type) noexcept
    {
      _aligned_free(p);
    }
  };

  template<typename type, typename other, usize alignement>
  bool operator==(const aligned_allocator<type, alignement>, const aligned_allocator<other, alignement>&)
  {
    return true;
  }

  template<typename type, typename other, usize alignement>
  bool operator!=(const aligned_allocator<type, alignement>, const aligned_allocator<other, alignement>&)
  {
    return false;
  }

  template<typename type>
  using simd_allocator = aligned_allocator<type, 16>;
}