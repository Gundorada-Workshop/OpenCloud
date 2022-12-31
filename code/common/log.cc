#pragma once
#include <limits>

#include "common/log.h"

namespace common::log
{
  // list of all the registered callbacks
  static std::vector<output_callback> s_callbacks{ };
  // list of disabled channels
  static std::vector<std::string> s_disabled_channels{ };

  // find a log callback by it's handle
  static std::vector<output_callback>::iterator find_by_handle(output_callback::cb_handle handle)
  {
    return std::find_if(s_callbacks.begin(), s_callbacks.end(), [&](const output_callback& cb) {
      return cb.handle == handle;
    });
  }

  // find a channel
  static std::vector<std::string>::iterator find_channel(std::string_view name)
  {
    return std::find(s_disabled_channels.begin(), s_disabled_channels.end(), name);
  }

  // check if a handle exits already
  static bool handle_exits(output_callback::cb_handle handle)
  {
    const auto itr = find_by_handle(handle);

    return itr != s_callbacks.end();
  }

  static bool channel_disabled(std::string_view channel)
  {
    const auto search = find_channel(channel);

    return search != s_disabled_channels.end();
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

  void disable_channel(std::string_view name)
  {
    // channel is already disabled
    // lets not pollute the list
    if (channel_disabled(name))
      return;

    s_disabled_channels.emplace_back(name);
  }

  void enable_channel(std::string_view channel)
  {
    auto itr = find_channel(channel);

    if (itr == s_disabled_channels.end())
      return;

    s_disabled_channels.erase(itr);
  }

  void write(std::string_view channel , level lvl, std::string_view file, std::string_view func, std::string_view msg)
  {
    for (const auto& cb : s_callbacks)
    {
      if (cb.enable && !channel_disabled(channel))
        cb.callback(channel, lvl, file, func, msg);
    }
  }
}
