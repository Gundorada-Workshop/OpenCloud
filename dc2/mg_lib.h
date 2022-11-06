#pragma once
#include "glm/glm.hpp"
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
extern mgCDrawManager mgDrawManager;

namespace mg_lib
{
  // 00373440
  void SInit();
}

// 00142F90
_UNKNOWNPOINTER mgDraw(mgCFrame* frame);
// 00142FD0
_UNKNOWNPOINTER mgDrawDirect(mgCFrame* frame);
// 00145B20
float mgGetDistFromCamera(glm::vec4& point);