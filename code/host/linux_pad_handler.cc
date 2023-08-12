#include <mutex>

#include <dirent.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/ioctl.h>

#include "common/log.h"
#include "common/bits.h"
#include "common/dynamic_library.h"

#include "host/linux_pad_handler.h"
#include <iostream>
set_log_channel("linux pad");

namespace host
{
  static std::unordered_map<u32, pad_handler::buttons> s_default_international_mapping =
  {
    { BTN_DPAD_UP,    pad_handler::buttons::dpad_up },
    { BTN_DPAD_DOWN,  pad_handler::buttons::dpad_down },
    { BTN_DPAD_LEFT,  pad_handler::buttons::dpad_left },
    { BTN_DPAD_RIGHT, pad_handler::buttons::dpad_right },
    { BTN_START,      pad_handler::buttons::start },
    { BTN_SELECT,     pad_handler::buttons::select },
    { BTN_THUMBL,     pad_handler::buttons::l3 },
    { BTN_THUMBR,     pad_handler::buttons::r3 },
    { BTN_TL,         pad_handler::buttons::l1 },
    { BTN_TR,         pad_handler::buttons::r1 },
    { BTN_SOUTH,      pad_handler::buttons::cross },
    { BTN_EAST,       pad_handler::buttons::circle },
    { BTN_WEST,       pad_handler::buttons::square },
    { BTN_NORTH,      pad_handler::buttons::triangle },
    { BTN_TL2,        pad_handler::buttons::l2 },
    { BTN_TR2,        pad_handler::buttons::r2 }
  };

  static std::unordered_map<u32, pad_handler::buttons> s_default_japanese_mapping =
  {
    { BTN_DPAD_UP,    pad_handler::buttons::dpad_up },
    { BTN_DPAD_DOWN,  pad_handler::buttons::dpad_down },
    { BTN_DPAD_LEFT,  pad_handler::buttons::dpad_left },
    { BTN_DPAD_RIGHT, pad_handler::buttons::dpad_right },
    { BTN_START,      pad_handler::buttons::start },
    { BTN_SELECT,     pad_handler::buttons::select },
    { BTN_THUMBL,     pad_handler::buttons::l3 },
    { BTN_THUMBR,     pad_handler::buttons::r3 },
    { BTN_TL,         pad_handler::buttons::l1 },
    { BTN_TR,         pad_handler::buttons::r1 },
    { BTN_SOUTH,      pad_handler::buttons::circle },
    { BTN_EAST,       pad_handler::buttons::cross },
    { BTN_WEST,       pad_handler::buttons::square },
    { BTN_NORTH,      pad_handler::buttons::triangle },
    { BTN_TL2,        pad_handler::buttons::l2 },
    { BTN_TR2,        pad_handler::buttons::r2 }
  };

  linux_pad_handler::linux_pad_handler()
    : m_mapping{ s_default_international_mapping }
  {
  };

  linux_pad_handler::~linux_pad_handler()
  {
    if (m_joystick_handle > -1)
      close(m_joystick_handle);
  };

  static bool find_joysticks(std::vector<std::string>& joystick_names)
  {
    // Get all joysticks that exist under evdev
    static const std::string EVDEV_DIR = "/dev/input/by-id/";
    DIR* dirp = opendir(EVDEV_DIR.c_str());
    struct dirent* dp;
    if(dirp == NULL)
          return false;
  
    // Loop over dir entries using readdir
    size_t len = strlen("event-joystick");
    while((dp = readdir(dirp)) != NULL)
    {
      // Only select names that end in 'event-joystick'
      size_t devlen = strlen(dp->d_name);
      if(devlen >= len)
      {
        const char* const start = dp->d_name + devlen - len;
        if(strncmp(start, "event-joystick", len) == 0)
        {
          std::string js_name = EVDEV_DIR + dp->d_name;
          joystick_names.push_back(js_name);
          log_info("Located gamepad: {}", js_name);
        }
      }
    }
    return true;
  }

  std::unique_ptr<pad_handler> linux_pad_handler::create()
  {
    std::vector<std::string> joystick_names;
    if (!find_joysticks(joystick_names))
     return nullptr;

    // Find first joystick - make settable...
    auto pad_handler_obj = std::make_unique<linux_pad_handler>();
    if (joystick_names.size() > 0)
      pad_handler_obj->m_joystick_handle = open((joystick_names[0]).c_str(), O_RDONLY | O_NONBLOCK);
    else
      return nullptr;
    if (pad_handler_obj->m_joystick_handle == -1)
      return nullptr;
      
    // Allow user to select a pad later?

    return pad_handler_obj;
  }

  static bool get_bit(char* buf, int idx)
  {
    // Many processors do / and % in the same op: should be quick
    // Could also make these indices static from a list of indices
    // known at compile-time.
    int char_idx    = idx / 8;
    int char_offset = idx % 8;
    return (buf[char_idx] >> char_offset) & 1;
  }

  bool linux_pad_handler::poll()
  {
    // Rumble is FF_RUMBLE

    buttons current_buttons{ };
    std::vector<char> key_map(KEY_MAX/8 + 1, 0);
    ioctl(m_joystick_handle, EVIOCGKEY(sizeof(key_map)), key_map.data()); // Read keyboard state into keymap[]
    for (int k = 0; k < KEY_MAX/8 + 1; ++k)
    {
      while (key_map[k])
      {
        auto lsb = common::bits::lsb(key_map[k]);
        auto it = m_mapping.find(k*8 + lsb);
        if (it != m_mapping.end())
        {
          log_info("Detected button press: {}", it->first);
          current_buttons |= it->second;
        }
        key_map[k] &= ~(lsb);
      } 
    }
    
    // // Alternatively: just look for the inputs you want
    // for (const auto& [first, second] : m_mapping)
    // {
    //   if (get_bit(key_map.data(), first))
    //     current_buttons |= second;
    // }

    m_buttons = current_buttons;

    return true;
  }
}
