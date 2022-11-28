#include <Windows.h>
#include <cstdlib>
#include <thread>

#include "common/console.h"
#include "common/console_logger.h"
#include "common/file_helpers.h"
#include "common/log.h"
#include "common/strings.h"
#include "common/synchro.h"
#include "common/scoped_function.h"

#include "host/host_interface_dwm.h"

#include "dc2/mainloop.h"

set_log_channel("main");

using namespace common;

static std::jthread s_game_thread;

INT WINAPI WinMain(_In_ HINSTANCE /*hInstance*/, _In_opt_ HINSTANCE /*hPrevInstance*/,
  _In_ LPSTR /*lpCmdLine*/, _In_ INT /*nCmdShow*/)

{
  log_trace("WinMain()");

  synchro::set_current_thread_name("gui-thread");

  // start the console
  // todo: report message box to user
  if (!console::initialize())
    return EXIT_FAILURE;

  log::console_logger::initialize();

  scoped_function cleanup([&]() {
    // free the console
    log::console_logger::shutdown();
    console::shutdown();
  });

  log_info("Starting");

  // set the application directory
  WCHAR w_path[MAX_PATH];
  GetModuleFileNameW(NULL, w_path, MAX_PATH);

  auto path = strings::wstring_to_utf8(w_path);
  if (!path)
    panicf("Can't convert application directory to utf8");

  file_helpers::set_application_directory(file_helpers::parent_directory(*path));

  if (!host::dwm_interface::create(file_helpers::basename(*path)))
    return EXIT_FAILURE;

  // create the render window
  if (!g_host_interface->create_render_window())
  {
    g_host_interface->present_user_error_dialog("Failed to create render window");

    return EXIT_FAILURE;
  }

  s_game_thread = std::jthread([]() {
    log_info("Starting game thread");

    synchro::set_current_thread_name("game-thread");

    MainLoop();
  });

  return g_host_interface->run_message_pump();
}
