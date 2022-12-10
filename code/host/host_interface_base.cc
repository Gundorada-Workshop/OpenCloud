#include "common/log.h"
#include "common/clock.h"

#include "host/host_interface_base.h"

set_log_channel("host");

using namespace common;

std::unique_ptr<host::host_interface_base> g_host_interface{ nullptr };

namespace host
{
  host_interface_base::host_interface_base() = default;
  host_interface_base::~host_interface_base() = default;

  host_interface_base::cached_file host_interface_base::open_game_file_cached(std::string_view data_relative_file)
  {
    log_info("Opening game file: {}", data_relative_file);

    const auto key = std::string{ data_relative_file };

    const auto itr = m_file_cache.find(key);

    if (itr != m_file_cache.end())
    {
      log_debug("File cache hit: {}", data_relative_file);

      return itr->second;
    }

    log_debug("File cache miss: {}", data_relative_file);

    // cache miss
    const auto path = file_helpers::append(file_helpers::get_data_directory(), data_relative_file);

    auto file_stream = file_stream::open(path, "rb");
    if (!file_stream)
      return { };

    const auto file_size = file_stream->size();

    auto buff = std::make_shared<u8[]>(file_size);

    if (!buff || !file_size)
      return { };

    if (!file_stream->read_buffer_checked(buff.get(), file_size))
      return { };

    // this shouldn't matter since the cache hit check prevents a duplicate insert
    // but just in case someone changes that condition, make sure we return the item in the map
    // and not the one that was potentially blocked from insertion
    auto [insert_itr, inserted] = m_file_cache.insert({key, std::make_pair(buff, file_size)});

    return insert_itr->second;
  }

  vec2 host_interface_base::sample_pad_left_stick_xy()
  {
    std::lock_guard<std::mutex> lk(m_pad_handler_mutex);

    const auto axis = m_pad_handler->right_stick_axis();

    return { axis.x, axis.y };
  }

  vec2 host_interface_base::sample_pad_right_stick_xy()
  {
    std::lock_guard<std::mutex> lk(m_pad_handler_mutex);

    const auto axis = m_pad_handler->left_stick_axis();

    return { axis.x, axis.y };
  }

  void host_interface_base::start_game_frame()
  {
    log_trace("Starting in-game frame");

    m_frame_start_time = common::time::current_cycle_count();

    // critical section
    {
      std::lock_guard<std::mutex> lk(m_pad_handler_mutex);

      m_game_button_buffer[m_game_button_buffer_index ^= 1] = m_pad_handler->current_buttons();
    }
  }

  void host_interface_base::end_game_frame()
  {
    log_trace("Ending in-game frame");

    static constexpr f64 max_frame_seconds = 1.0 / 60.0;

    const u64 limit = common::time::seconds_to_cycles(max_frame_seconds * m_frame_divider);

    u64 dt = common::time::current_cycle_count() - m_frame_start_time;

    log_trace("Delta time {}:{}", limit, dt);

    while (dt < limit)
    {
      dt = common::time::current_cycle_count() - m_frame_start_time;
    }
  }
}
