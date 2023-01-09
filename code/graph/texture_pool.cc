#include <algorithm>

#include "common/debug.h"

#include "graph/texture_pool.h"
#include "graph/renderer.h"

namespace graph
{
  texture_pool::texture_pool() = default;
  texture_pool::~texture_pool() = default;

  auto texture_pool::find_first_available_by_config(const create_info& config) -> std::optional<entry>
  {
    auto range = m_pool.equal_range(config);

    for(auto itr = range.first; range.first != range.second; ++itr)
    {
      auto& pool_entry = itr->second;

      if (pool_entry.marked_for_reuse)
        return pool_entry;
    }

    return std::nullopt;
  }

  std::shared_ptr<texture> texture_pool::allocate(const create_info& config)
  {
    auto texture_pool_entry = find_first_available_by_config(config);

    // pool miss
    if (!texture_pool_entry)
    {
      auto tex = g_renderer->create_texture_from_config(config);

      assert_panic(tex);

      auto itr = m_pool.emplace(config, entry{ });

      texture_pool_entry = itr->second;
      texture_pool_entry->tex = std::move(tex);
    }

    texture_pool_entry->last_used = common::time::current_cycle_count();
    texture_pool_entry->marked_for_reuse = false;

    return texture_pool_entry->tex;
  }

  void texture_pool::free(std::shared_ptr<texture> tex)
  {
    auto range = m_pool.equal_range(tex->config());

    for (auto itr = range.first; range.first != range.second; ++itr)
    {
      if (itr->second.tex == tex)
        itr->second.marked_for_reuse = true;
    }
  }
}

std::unique_ptr<graph::texture_pool> g_texture_pool{ nullptr };
