#pragma once

#include "common/platform.h"

// Don't include those nasty headers
#if PLATFORM_OS_LINUX
typedef ulong Window;
typedef struct _XDisplay Display;
#endif

#if PLATFORM_OS_WINDOWS
typedef struct HWND__* HWND;
#endif

namespace common
{
  enum class window_system
  {
    headless,
    dwm,
    x11,
    wayland,
    cocoa
  };

  template<window_system type>
  struct window_handle_t;

  template<>
  struct window_handle_t<window_system::headless>
  {
  };

  #if PLATFORM_OS_WINDOWS
  template<>
  struct window_handle_t<window_system::dwm>
  {
    HWND window{ nullptr };
  };

  using native_window_handle_type = window_handle_t<window_system::dwm>;
  #endif

  #if PLATFORM_OS_LINUX
  template<>
  struct window_handle_t<window_system::x11>
  {
    Display* display{ nullptr };
    Window   window{ 0 };
  };

  using native_window_handle_type = window_handle_t<window_system::x11>;
  #endif

  // TODO
  #if PLATFORM_OS_LINUX && PLATFORM_USE_WAYLAND
  //#include <wayland-client-protocol.h>

  //template<>
  //struct window_handle_t<window_system::wayland>
  //{
  //  wl_display* display{ nullptr };
  //  wl_surface* surface{ nullptr };
  //};
  #endif

  // TODO
  // this will probably need more work than just NSView* because objc nonsense
  #if PLATFORM_OS_MACOS
  //template<>
  //struct window_handle_t<window_system::cocoa>
  //{
  //  NSView* view{ nullptr };
  //};
  #endif
}
