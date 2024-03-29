#pragma once
#include "common/types.h"

#include "engine/mg/mg_camera.h"
#include "engine/mg/mg_frame.h"
#include "engine/mg/mg_math.h"
#include "engine/mg/mg_memory.h"
#include "engine/mg/mg_tanime.h"
#include "engine/mg/mg_texture.h"

// 00380EC0
extern mgRENDER_INFO mgRenderInfo;

// 00381EF0
extern mgCTextureManager mgTexManager;

// 003820E0
extern mgCDrawManager mgDrawManager;

// TEMP
// using sceGsTex0 = mgCTexture;

// 001413E0
void mgInit();

// 001421E0
// This is not useful to us.
// Clear screen, set up vif stuff
//void mgBeginFrame(mgCDrawManager* draw_man);

// 00142F90
unkptr mgDraw(mgCFrame* frame);

// 00142FD0
unkptr mgDrawDirect(mgCFrame* frame);

// 001425B0
// This is not useful to us.
// Buffer swap, vsync, perf mon, screen capture,
//void mgEndFrame(mgCDrawManager* draw_man);

// 00144400
// This is not useful to us.
// Gets the backbuffer
//void mgGetFrameBackBuffer(mgCTexture* texture);

// 001445A0
// This is not useful to us.
// Does what it says on the tin
//void mgSetPkMoveImage(sceGsTex0* tex1, irect* rect, sceGsTex0* tex2, sint i1, sint i2, sint i3);

// 00145B20
//f32 mgGetDistFromCamera(vec3& point);