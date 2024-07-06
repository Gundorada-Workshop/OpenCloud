#include <thread>

#include "common/console.h"
#include "common/console_logger.h"
#include "common/file_helpers.h"
#include "common/log.h"
#include "common/synchro.h"
#include "common/scoped_function.h"

#include "host/host_interface_x11.h"
#undef None

#include "engine/mainloop.h"

set_log_channel("main");

using namespace common;

static std::jthread s_game_thread;

int main(int argc, char** argv)
{
  log_trace("LinuxMain()");

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
  std::array<char, PATH_MAX> result;
  ssize_t count = readlink("/proc/self/exe", result.data(), PATH_MAX);
  std::string path;
  if (count != -1)
      path = result.data();
  file_helpers::set_application_directory(file_helpers::parent_directory(path));

  if (!host::x11_interface::create(file_helpers::basename(path)))
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
