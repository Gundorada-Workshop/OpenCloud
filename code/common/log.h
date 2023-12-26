#pragma once
#include <functional>
#include <optional>
#include <fmt/core.h>

#include "common/types.h"
#include "common/strings.h"
#include "common/debug.h"
#include "common/macros.h"
#include "common/dictionary.h"

namespace common::log
{
  enum class level
  {
    none,
    error,
    warning,
    performance,
    info,
    trace,
    debug
  };

  struct output_callback
  {
    using fncb = std::function<void(std::string_view, level, std::string_view, std::string_view, std::string_view)>;

    using cb_handle = usize;

    bool enable{ false };
    cb_handle handle{ 0 };
    fncb callback{ };
  };

  // register a new output callback with the logger
  std::optional<output_callback::cb_handle> register_output_callback(output_callback::fncb callback);

  // unregister a callback
  void unregister_output_callback(output_callback::cb_handle handle);

  // enable a callback
  void enable_output_callback(output_callback::cb_handle handle);

  // disable a callback
  void disable_output_callback(output_callback::cb_handle handle);

  // disable a channel
  void disable_channel(std::string_view channel);

  // enable a channel
  void enable_channel(std::string_view channel);

  // write to the callbacks
  void write(std::string_view channel, level lvl, std::string_view file, std::string_view func, std::string_view msg);

  // write with formatting
  template<typename ...Args>
  void write_format(std::string_view channel, level lvl, std::string_view file, std::string_view func_name, fmt::format_string<Args...> fmtstr, Args&&... args)
  {
    std::string msg = strings::format(fmtstr, std::forward<Args>(args)...);

    write(channel, lvl, file, func_name, msg);
  }

  inline std::string_view level_string(level lvl)
  {
    static constexpr common::dictionary<level, std::string_view, 6> s_map =
    {
      { level::debug,       "DBG" },
      { level::error,       "ERR" },
      { level::warning,     "WRN" },
      { level::info,        "INF" },
      { level::performance, "PRF" },
      { level::trace,       "TRC" }
    };

    return s_map.find_or(lvl, "NUL");
  }
}

// log error
#define log_error(...) \
  common::log::write_format(log_channel, common::log::level::error, __FILE__, __func__, __VA_ARGS__)

// log warning
#define log_warn(...) \
  common::log::write_format(log_channel, common::log::level::warning, __FILE__, __func__, __VA_ARGS__)

// log performance
#define log_perf(...) \
  common::log::write_format(log_channel, common::log::level::performance, __FILE__, __func__, __VA_ARGS__)

// log info
#define log_info(...) \
  common::log::write_format(log_channel, common::log::level::info, __FILE__, __func__, __VA_ARGS__)

// don't enable these on release
#if defined(_DEBUG)
// log trace
#define log_trace(...) \
  common::log::write_format(log_channel, common::log::level::trace, __FILE__, __func__, __VA_ARGS__)

// log debug
#define log_debug(...) \
  common::log::write_format(log_channel, common::log::level::debug, __FILE__, __func__, __VA_ARGS__)
#else
#define log_trace(...)              \
  do                                \
  {                                 \
  } while(0)

#define log_debug(...)              \
  do                                \
  {                                 \
  } while(0)
#endif

#define set_log_channel(ch) \
  namespace{ MAYBE_UNUSED const char* log_channel = ch; }
