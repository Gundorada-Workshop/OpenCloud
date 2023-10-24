#pragma once
#include <array>
#include <ctime>

#include "common/debug.h"
#include "common/types.h"

#include "engine/menusave.h"
#include "engine/mg/mg_memory.h"
#include "engine/scene.h"

// ~ 0029F050 - 002A4D90

struct INIT_LOOP_ARG;

struct SHDDINFO
{
  // 0
  bool m_unk_field_0;
  // 4
  bool m_unk_field_4;
  // 8
  bool m_unk_field_8;
  // C
  unk32 m_unk_field_C;
  // 10
  unk32 m_unk_field_10;
  // 14
  unk32 m_unk_field_14;
  // 18
  unk32 m_unk_field_18;
  // 1C
  unk32 m_unk_field_1C;
  // 20
  unk32 m_unk_field_20;
  // 24
  unk32 m_unk_field_24;
  // 28
  unk32 m_unk_field_28;
  // 2C
  unk32 m_unk_field_2C;
};

struct TITLE_INFO
{
  // 0
  s32 m_unk_field_0{};
  // 4
  s32 m_unk_field_4{};
  // 8
  s16 m_unk_field_8{};
  // A
  s16 m_unk_field_A{};
  // C
  s16 m_unk_field_C{};
  // E
  s16 m_unk_field_E{};
  // 10
  s16 m_unk_field_10{};
  // 14
  f32 m_unk_field_14{};
  // 18
  s32 m_unk_field_18{};
  // 1C
  f32 m_unk_field_1C{};
  // 20
  f32 m_unk_field_20{};
  // 24
  f32 m_unk_field_24{};
  // 28
  f32 m_unk_field_28{};
  // 2C
  s32 m_unk_field_2C{};
  // 30
  f32 m_unk_field_30{};
  // 34
  f32 m_unk_field_34{};
  // 38
  s32 m_unk_field_38{};
  // 48
  SV_CONFIG_OPTION m_save_config_option{};
  // 88
  CScene::BGM_STATUS m_bgm_status{};
};

// 0029F050
inline void title_init_rand()
{
  srand(static_cast<uint>(time(0)));
}

// 0029F080
void SetSoundMode();

// 0029F080
inline void InitTitleOmakeFlag()
{
  OmakeFlag = false;
}

// 0029F0F0
inline void TitleOmakeOn()
{
  OmakeFlag = true;
}

// 0029F100
inline bool CheckOmakeFlag()
{
  return OmakeFlag;
}

// 0029F110
void InitOmakeEnv(int, INIT_LOOP_ARG*, int*);

// 0029F1F0
void TitleInit(INIT_LOOP_ARG loop_arg);

// 0029FF30
void TitleExit();

// 0029FFA0
void TitleLoop();

// 002A0AB0
void TitleDraw();

// 002A0B70
void InitRushMovie();

// 002A0C90
s32 RushMovieKey();

// 002A0EB0
void RushMovieDraw();

// 002A1020
void TitleModeInit();

// 002A1220
s32 TitleModeKey();

// 002A1B60
void TitleModeDraw();

// 002A1B60
void TitleMapDraw();

// 002A2950
void CalcPushAlpha(sint, float*);

// 002A29F0
void TitleMCCheckInit(sint);

// 002A2AD0
sint TitleMCCheckKey();

// 002A2FD0
void TitleMCCheckDraw();
