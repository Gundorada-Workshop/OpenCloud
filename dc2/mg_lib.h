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

// TEMP
using sceGsTex0 = mgCTexture;

// 001421E0
void mgBeginFrame(mgCDrawManager* draw_man);
// 00142F90
_UNKNOWNPOINTER mgDraw(mgCFrame* frame);
// 00142FD0
_UNKNOWNPOINTER mgDrawDirect(mgCFrame* frame);
// 001425B0
void mgEndFrame(mgCDrawManager* draw_man);
// 00144400
void mgGetFrameBackBuffer(mgCTexture* texture);
// 001445A0
void mgSetPkMoveImage(sceGsTex0* tex1, mgRect<int>* rect, sceGsTex0* tex2, int i1, int i2, int i3);
// 00145B20
float mgGetDistFromCamera(glm::vec4& point);