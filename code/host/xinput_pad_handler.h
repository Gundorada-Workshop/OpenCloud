#pragma once
#include <memory>
#include "host/pad_handler.h"

namespace host
{
  class xinput_pad_handler final : public pad_handler
  {
  public:
    xinput_pad_handler();
    ~xinput_pad_handler();

    static std::unique_ptr<pad_handler> create();

  public:
    bool poll() override;

  private:
    std::unordered_map<u32, pad_handler::buttons> m_mapping{ };
  };
}
