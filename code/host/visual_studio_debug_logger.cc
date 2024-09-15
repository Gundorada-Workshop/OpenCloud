#include <Windows.h>
#include <chrono>

#include "common/log.h"
#include "common/debug.h"
#include "common/macros.h"

#include "host/visual_studio_debug_logger.h"

namespace host::visual_studio_debug_logger
{
  static std::optional<common::log::output_callback::cb_handle> s_callback_handle{ };

  static void console_log_callback(std::string_view channel,
                                   common::log::level lvl,
                                   MAYBE_UNUSED std::string_view file,
                                   MAYBE_UNUSED std::string_view fn,
                                   std::string_view msg)
  {
    const auto now = std::chrono::system_clock::now();

    std::string fmt = common::format(
      "{} [{}] {:<15} {}\n", now, level_string(lvl), channel, msg
    );

    std::wstring out = common::strings::utf8_to_wstring_or_panic(fmt);

    OutputDebugStringW(out.c_str());
  }

  bool initialize()
  {
    assert_msg(!s_callback_handle.has_value(), "VS debug logger already initialized");

    s_callback_handle = common::log::register_output_callback(console_log_callback);

    if (s_callback_handle)
    {
      common::log::enable_output_callback(*s_callback_handle);
    }

    return s_callback_handle.has_value();
  }

  void shutdown()
  {
    if (s_callback_handle)
    {
      common::log::unregister_output_callback(*s_callback_handle);
    }
  }
}
