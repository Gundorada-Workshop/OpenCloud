#include <chrono>
#include "debug.h"
#include "console.h"
#include "console_logger.h"

namespace common::log::console_logger
{
  static std::optional<output_callback::cb_handle> s_callback_handle{ }
;
  static void console_log_callback(std::string_view chan, level level, std::string_view file, std::string_view fn, std::string_view msg)
  {
    const auto now = std::chrono::system_clock::now();

    std::string out = strings::format("{} [{}] {}\n", now, chan, msg);

    console::write(out);
  }

  bool initialize()
  {
    assert_msg(!s_callback_handle.has_value(), "Console logger already initialized");

    s_callback_handle = register_output_callback(console_log_callback);

    if (s_callback_handle)
      enable_output_callback(*s_callback_handle);

    return s_callback_handle.has_value();
  }

  void shutdown()
  {
    if (s_callback_handle)
      unregister_output_callback(*s_callback_handle);
  }
}
