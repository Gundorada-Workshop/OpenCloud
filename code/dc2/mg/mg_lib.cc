#include <array>
#include <math.h>

#include <glm/glm.hpp>

#include "common/log.h"
#include "common/types.h"

#include "dc2/mg/mg_lib.h"
#include "dc2/mg/mg_math.h"

set_log_channel("mg_lib");

// 00380EC0
mgRENDER_INFO mgRenderInfo{ };

// 00381EE0
static vec4 mgBackColor{ 0 };

// 00381EF0
mgCTextureManager mgTexManager{ };

// 003820E0
mgCDrawManager mgDrawManager{ };

// 003823D0
static std::array<mgCMemory, 2> packet_buf{ };

// 00382430
static std::array<mgCMemory, 2> data_buf{ };

// 00382490
static mgCTexture frame_tex{ };

// 00382510
static std::array<mgCTexture, 2> fixz_tex{ };

// 001413E0
void mgInit()
{
  log_trace("{}()", __func__);

  todo;

  // 001419B0
  mgCreateSinTable();

  todo;
}

// 001421E0
void mgBeginFrame(mgCDrawManager* draw_man)
{
  log_trace("{}({})", __func__, fmt::ptr(draw_man));

  todo;
}

// 00142F90
unkptr mgDraw(mgCFrame* frame)
{
  log_trace("mgDraw({})", fmt::ptr(frame));

  if (frame == nullptr)
  {
    return nullptr;
  }

  return frame->Draw();
}

// 00142FD0
unkptr mgDrawDirect(mgCFrame* frame)
{
  log_trace("mgDrawDirect({})", fmt::ptr(frame));

  if (frame == nullptr)
  {
    return nullptr;
  }

  // Likely not applicable to Windows anyways
  todo;
  return nullptr;
}

// 001425B0
void mgEndFrame(mgCDrawManager* draw_man)
{
  log_trace("{}({})", __func__, fmt::ptr(draw_man));

  todo;
}

// 00144400
void mgGetFrameBackBuffer(mgCTexture* texture)
{
  log_trace("mgGetFrameBackBuffer({})", fmt::ptr(texture));

  todo;
}

// 001445A0
void mgSetPkMoveImage(sceGsTex0* tex1, irect* rect, sceGsTex0* tex2, sint i1, sint i2, sint i3)
{
  log_trace("mgSetPkMoveImage({})", fmt::ptr(tex1), fmt::ptr(rect), fmt::ptr(tex2), i1, i2, i3);

  todo;
}

// 00145B20
f32 mgGetDistFromCamera(vec4& point)
{
  log_trace("mgGetDistFromCamera({})", fmt::ptr(&point));

  return glm::distance(point, mgRenderInfo.camera_pos);
}