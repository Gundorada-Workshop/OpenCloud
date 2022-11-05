#include <array>
#include <math.h>
#include "glm/glm.hpp"
#include "common/log.h"
#include "common/types.h"
#include "mg_lib.h"

set_log_channel("mg_lib");

// 00380EC0
mgRENDER_INFO mgRenderInfo;
// 00381EE0
static glm::vec4 mgBackColor;
// 00381EF0
mgCTextureManager mgTexManager;
// 003820E0
mgCDrawManager mgDrawManager;
// 003823D0
static std::array<mgCMemory, 2> packet_buf;
// 00382430
static std::array<mgCMemory, 2> data_buf;
// 00382490
static mgCTexture frame_tex;
// 00382510
static std::array<mgCTexture, 2> fixz_tex;

namespace mg_lib
{
  // 00373440
  void SInit()
  {
    log_trace("SInit()");

    for (auto& draw_env : mgRenderInfo.m_unk_field_F20)
    {
      draw_env = mgCDrawEnv();
    }

    mgTexManager = mgCTextureManager();
    mgDrawManager = mgCDrawManager();

    for (auto& memory : packet_buf)
    {
      memory = mgCMemory();
    }

    for (auto& memory : data_buf)
    {
      memory = mgCMemory();
    }

    frame_tex = mgCTexture();

    for (auto& texture : fixz_tex)
    {
      texture = mgCTexture();
    }
  }
}