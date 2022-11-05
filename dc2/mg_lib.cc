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
      new (&draw_env) mgCDrawEnv;
    }

    new (&mgTexManager) mgCTextureManager;
    new (&mgDrawManager) mgCDrawManager;

    for (auto& memory : packet_buf)
    {
      new (&memory) mgCMemory;
    }

    for (auto& memory : data_buf)
    {
      new (&memory) mgCMemory;
    }

    new (&frame_tex) mgCTexture;

    for (auto& texture : fixz_tex)
    {
      new (&texture) mgCTexture;
    }
  }
}

// 00142F90
_UNKNOWNPOINTER mgDraw(mgCFrame* frame)
{
  log_trace("mgDraw({})", fmt::ptr(frame));

  if (frame == nullptr)
  {
    return nullptr;
  }

  return frame->Draw();
}

// 00142FD0
_UNKNOWNPOINTER mgDrawDirect(mgCFrame* frame)
{
  log_trace("mgDraw({})", fmt::ptr(frame));

  if (frame == nullptr)
  {
    return nullptr;
  }

  // Likely not applicable to Windows anyways
  todo;
}

// 00145B20
float mgGetDistFromCamera(glm::vec4& point)
{
  log_trace("mgGetDistFromCamera({})", fmt::ptr(&point));

  return glm::distance(point, mgRenderInfo.camera_pos);
}