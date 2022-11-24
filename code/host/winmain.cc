#include <Windows.h>
#include <cstdlib>

#include "common/console.h"
#include "common/console_logger.h"
#include "common/file_helpers.h"
#include <thread>

#include "common/log.h"
#include "common/strings.h"
#include "common/scoped_function.h"

#include "host/host_interface_dwm.h"

#include "dc2/mainloop.h"

set_log_channel("WINMAIN");

static std::jthread s_game_thread;

INT WINAPI WinMain(_In_ HINSTANCE /*hInstance*/, _In_opt_ HINSTANCE /*hPrevInstance*/,
  _In_ LPSTR /*lpCmdLine*/, _In_ INT /*nCmdShow*/)

{
  log_trace("WinMain()");

  using namespace common;

  // start the console
  // todo: report message box to user
  if (!common::console::initialize())
    return EXIT_FAILURE;

  common::log::console_logger::initialize();

  scoped_function cleanup([&]() {
    // free the console
    common::log::console_logger::shutdown();
    common::console::shutdown();
  });

  log_info("Starting");

  // set the application directory
  WCHAR w_path[MAX_PATH];
  GetModuleFileNameW(NULL, w_path, MAX_PATH);

  auto path = strings::to_utf8(w_path);
  if (!path)
    panicf("Can't locate module file name!!");

  if (!host::dwm_interface::create(file_helpers::basename(*path)))
    return EXIT_FAILURE;

  if (!g_host_interface->create_render_window())
    return EXIT_FAILURE;
   
  file_helpers::set_application_directory(file_helpers::parent_directory(*path));

  s_game_thread = std::jthread([]() {
    log_info("Starting game thread");

    MainLoop();
  });

  return g_host_interface->run_message_pump();
}
