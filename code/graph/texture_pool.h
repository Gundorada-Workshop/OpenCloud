#pragma once
#include <memory>
#include <unordered_map>

#include "common/types.h"
#include "common/clock.h"

#include "graph/vector.h"
#include "graph/rectangle.h"
#include "graph/texture.h"

namespace graph
{
  class texture_pool
  {
  public:
    struct entry
    {
      // texture
      std::shared_ptr<texture> tex{ };

      // high res time stamp
      common::time::cycles_type last_used{ };

      // currently in use?
      bool marked_for_reuse{ false };
    };

    using create_info = texture::create_info;
    using texture_list = std::unordered_multimap<create_info, entry>;

  public:
    texture_pool();
    ~texture_pool();

  public:
    // allocate an entry
    // may use an already existing entry that has been freed
    std::shared_ptr<texture> allocate(const create_info& config);

    // free a texture
    // may be reused or deleted
    void free(std::shared_ptr<texture> tex);

  private:
    std::optional<entry> find_first_available_by_config(const create_info& config);

  private:
    texture_list m_pool{ };
  };
}

extern std::unique_ptr<graph::texture_pool> g_texture_pool;