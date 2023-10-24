#pragma once
#include <array>

#include "common/debug.h"
#include "common/types.h"

// ~ 00188880 - 00190840

// TODO THIS FILE
class CSound {};
struct SND_LOOP_SE_SEQ {};
class sndCSeSeqData{};

struct sndTrack
{
  // 0018B4B0
  void Initialize();

  // 0
  s8 m_unk_field_0;
  // 1
  s8 m_unk_field_1;
  // 2
  s8 m_unk_field_2;
  // 3
  s8 m_unk_field_3;
  // 4
  s8 m_unk_field_4;
  // 5
  s8 m_unk_field_5;
  // 6
  s8 m_unk_field_6;
  // 8
  usize m_n_unk_field_C;
  // C
  std::array<s8, 1> m_unk_field_C;
};

class sndCSeSeq 
{
public:
  // 0018B880
  void Initialize();
  // 00190600
  sndCSeSeq();

  // 8
  unk m_unk_field_8;
  // C
  // FIXME: What the heck is this type? 00190620
  unk m_unk_field_C;
  // 10
  unk m_unk_field_10;
  // 14
  unk m_unk_field_14;
  // 18
  int m_unk_field_18;
  
  // ?
  
  // 28
  unk m_unk_field_28;
  // 2C
  usize m_n_unk_field_30;
  // 30
  std::array<sndTrack, 8> m_unk_field_30;
};

struct sndPortInfoUnk1
{
  // 0
  s16 m_unk_field_0;

  // Size 0x8
};

struct sndPortInfo
{
  // 00190680
  sndPortInfo();

  // 0
  s32 m_unk_field_0;
  // 4
  s32 m_unk_field_4;
  // 8
  unk m_unk_field_8;
  // C
  // (70 32-bit words ; size 0x1C0)
  std::array<unk, 70> m_unk_field_C;

  // ?

  // 20C
  s32 m_unk_field_20C;
  // 210
  unk m_unk_field_210;
  // 214
  unk m_unk_field_214;
  // 218
  s32 m_unk_field_218;
  // 21C
  std::array<sndPortInfoUnk1, 10> m_unk_field_21C;
};

class CLoopSeMngr
{
public:
  // 0018C550
  void Initialize();

  usize m_n_unk_field_4;
  unkptr m_unk_field_4;
};

// 0018D1E0
void sndSetMasterVol(float volume, int i);

// 0018D270
float sndGetMasterVol(int i);

// 0018D2B0
void sndMasterVolFadeInOut(int i1, int i2, float f1, float f2);

// 0018D650
void sndStep(float f);

// 0018E060
void sndSePlay(uint u1, int i1, int i2);

// 0018E0C0
void sndSePlayVPf(uint i0, sint i1, f32 f0, f32 f1, sint i2);

// 0018E410
void sndPortSqPause(int port_no);

// 0018E460
void sndPortSqReplay(int port_no);

// 0018EEF0
//void sndGetVolPan(f32* fp0, f32* fp1, vec3* emitter_position, f32 f0, f32 f1);

// 00190530
void sndStreamPause();

// 00190560
void sndStreamRePlay();

// 00190590
int sndStreamGetState();