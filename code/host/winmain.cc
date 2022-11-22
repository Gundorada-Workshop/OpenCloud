#include <Windows.h>
#include <cstdlib>

#include "common/console.h"
#include "common/console_logger.h"
#include "common/file_helpers.h"
#include "common/log.h"
#include "common/strings.h"

#include "dc2/mainloop.h"

set_log_channel("WINMAIN");

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

  log_info("Starting");

  // set the application directory
  WCHAR w_path[MAX_PATH];
  GetModuleFileNameW(NULL, w_path, MAX_PATH);
  auto path = strings::to_utf8(w_path);
  if (!path.has_value())
  {
    panicf("Can't locate module file name!!");
  }
   
  file_helpers::set_application_directory(file_helpers::parent_directory(path.value()));

  // the main loop
  MainLoop();

  // free the console
  common::log::console_logger::shutdown();
  common::console::shutdown();

  return EXIT_SUCCESS;
}
