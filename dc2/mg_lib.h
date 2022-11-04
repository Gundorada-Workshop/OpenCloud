#pragma once
#include "common/types.h"
#include "mg_camera.h"
#include "mg_frame.h"
#include "mg_math.h"
#include "mg_memory.h"
#include "mg_tanime.h"
#include "mg_texture.h"

// 00380EC0
extern mgRENDER_INFO mgRenderInfo;
// 00381EF0
extern mgCTextureManager mgTexManager;
// 003820E0
extern mgCDrawManager g_draw_mavnager;

namespace mg_lib
{
  // 00373440
  void SInit();
}