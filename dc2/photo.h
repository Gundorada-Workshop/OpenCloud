#pragma once
#include <array>

#include "common/types.h"

#include "dc2/gamepad.h"
#include "dc2/inventmn.h"
#include "dc2/mg_memory.h"
#include "dc2/userdata.h"

// ~ 0030E4C0 - 0030F9B0

// 0030E4C0
const char* GetMesTxt(ssize index);

// 0030E520
float PhotoAddProjection(void);

// 0030E550
void InitPhotoTitle(void);

// 0030E560
void InitTakePhoto(void);

// 0030E5A0
void LoadTakePhoto(int, mgCMemory& unused);

// 0030E640
void StartTakePhoto(void);

// 0030E670
void EndTakePhoto(void);

// 0030E680
bool NowTakePhoto(void);

// 0030E690
bool IsEnablePhotoMenu(void);

// 0030E6A0
void HidePhoto(void);

// 0030E6B0
bool GhostPhotoTiming(void);

// 0030E6E0
void LoopTakePhoto(CPadControl& padControl, CInventUserData& invest_user_data);

// 0030E810
void DrawTakePhoto(USER_PICTURE_INFO& picture_info, float* fp);

// 0030F610
void SetTookPhotoData(USER_PICTURE_INFO& picture_info);

// 0030F6A0
void DrawTakePhotoSystem(s32 i1, CInventUserData& invent_user_data);