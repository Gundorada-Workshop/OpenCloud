#pragma once
#include <memory>
#include "host/pad_handler.h"

namespace host
{
  class linux_pad_handler final : public pad_handler
  {
  public:
    linux_pad_handler();
    ~linux_pad_handler();

    static std::unique_ptr<pad_handler> create();

  public:
    bool poll() override;

  private:
    std::unordered_map<u32, pad_handler::buttons> m_mapping{ };
    sint m_joystick_handle;
  };
}
