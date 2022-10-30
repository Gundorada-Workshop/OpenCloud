#pragma once
#include "log.h"
#include <limits>

namespace common::log
{
  // list of all the registered callbacks
  static std::vector<output_callback> s_callbacks;

  // find a log callback by it's handle
  static std::vector<output_callback>::iterator find_by_handle(output_callback::cb_handle handle)
  {
    return std::find_if(s_callbacks.begin(), s_callbacks.end(), [&](const output_callback& cb) {
      return cb.handle == handle;
    });
  }

  // check if a handle exits already
  static bool handle_exits(output_callback::cb_handle handle)
  {
    const auto itr = find_by_handle(handle);

    return itr != s_callbacks.end();
  }

  // create a new handle
  static std::optional<output_callback::cb_handle> create_handle()
  {
    for (usize i = 0; i < std::numeric_limits<u8>::max(); ++i)
    {
      if (!handle_exits(i))
        return i;
    }

    return std::nullopt;
  }

  // remove a callback by it's handle
  static bool remove_by_handle(output_callback::cb_handle handle)
  {
    auto itr = find_by_handle(handle);
    if (itr == s_callbacks.end())
      return false;

    s_callbacks.erase(itr);

    return true;
  }

  // enable or disable a callback by it's handle
  static bool enable_by_handle(output_callback::cb_handle handle, bool enable)
  {
    auto itr = find_by_handle(handle);

    if (itr == s_callbacks.end())
      return false;

    itr->enable = enable;

    return true;
  }

  // insert a new callback
  // creates a new handle
  static std::optional<output_callback::cb_handle> insert_callback(output_callback::fncb fn)
  {
    auto handle = create_handle();

    if (!handle)
      return std::nullopt;

    output_callback cb =
    {
      .enable = true,
      .handle = *handle,
      .callback = fn
    };

    s_callbacks.push_back(std::move(cb));

    return handle;
  }

  std::optional<output_callback::cb_handle> register_output_callback(output_callback::fncb callback)
  {
    return insert_callback(callback);
  }

  void unregister_output_callback(output_callback::cb_handle handle)
  {
    remove_by_handle(handle);
  }

  void enable_output_callback(output_callback::cb_handle handle)
  {
    enable_by_handle(handle, true);
  }

  void disable_output_callback(output_callback::cb_handle handle)
  {
    enable_by_handle(handle, false);
  }

  void write(std::string_view channel , level lvl, std::string_view file, std::string_view func, std::string_view msg)
  {
    for (const auto& cb : s_callbacks)
    {
      if (cb.enable)
        cb.callback(channel, lvl, file, func, msg);
    }
  }
}
