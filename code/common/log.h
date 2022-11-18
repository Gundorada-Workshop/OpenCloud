#pragma once
#include <functional>
#include <optional>
#include <fmt/core.h>

#include "types.h"
#include "strings.h"
#include "debug.h"

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

  inline std::string level_string(level lvl)
  {
    switch (lvl)
    {
    case level::debug:
      return "DBG";
    case level::error:
      return "ERR";
    case level::warning:
      return "WRN";
    case level::info:
      return "INF";
    case level::performance:
      return "PRF";
    case level::trace:
      return "TRC";
    }

    return "[UNK]";
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
  namespace{ const char* log_channel = ch; }