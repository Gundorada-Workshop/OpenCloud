// SPDX-License-Identifier: MIT

#pragma once
#include <string_view>
#include <thread>

#include "common/types.h"

namespace common::synchro
{
  // get the id of the current thread
  // P: The return type might need to be OS-dependent
  sint current_thread_id();

  // set the name of the current thread
  void set_current_thread_name(std::string_view name);

  // sleep the thread
  void sleep_current_thread(uint ms);
}