#pragma once
#include <functional>
#include <optional>
#include <fmt/core.h>

#include "types.h"
#include "strings.h"

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
    using fncb = std::function<void(level, std::string_view, std::string_view, std::string_view)>;

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

  // write to the callbacks
  void write(level lvl, std::string_view file, std::string_view func, std::string_view msg);

  // write with formatting
  template<typename ...Args>
  void write_format(level lvl, std::string_view file, std::string_view func_name, fmt::format_string<Args...> fmtstr, Args&&... args)
  {
    std::string msg = strings::format(fmtstr, std::forward<Args>(args)...);

    write(lvl, file, func_name, msg);
  }
}

// log error
#define LERR(...) \
  common::log::write_format(common::log::level::error, __FILE__, __func__, __VA_ARGS__);

// log warning
#define LWARN(...) \
  common::log::write_format(common::log::level::warning, __FILE__, __func__, __VA_ARGS__);

// log performance
#define LPERF(...) \
  common::log::write_format(common::log::level::performance, __FILE__, __func__, __VA_ARGS__);

// log info
#define LINFO(...) \
  common::log::write_format(common::log::level::info, __FILE__, __func__, __VA_ARGS__);


// don't enable these on release
#if defined(_DEBUG)
// log trace
#define LTRACE(...) \
  common::log::write_format(common::log::level::trace, __FILE__, __func__, __VA_ARGS__);

// log debug
#define LDEBUG(...) \
  common::log::write_format(common::log::level::debug, __FILE__, __func__, __VA_ARGS__);
#else
#define LTRACE                      \
  do                                \
  {                                 \
  } while(0)

#define LDEBUG                      \
  do                                \
  {                                 \
  } while(0)
#endif
