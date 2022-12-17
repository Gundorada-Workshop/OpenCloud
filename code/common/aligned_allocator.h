#pragma once
#include <vector>

#include "common/types.h"

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

    [[nodiscard]] pointer allocate(size_type n)
    {
      auto ptr = _aligned_malloc(sizeof(value_type) * n, alignment);
      return reinterpret_cast<pointer>(ptr);
    }

    void deallocate(pointer p, size_type)
    {
      _aligned_free(p);
    }
  };

  template<typename type, usize alignment>
  using aligned_vector = std::vector<type, aligned_allocator<type, alignment>>;
}