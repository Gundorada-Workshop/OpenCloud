#pragma once
#include <array>
#include "glm/glm.hpp"
#include "common/debug.h"
#include "common/types.h"

// ~ 00188880 - 00190840

namespace snd_mngr
{
  // 00373520
  void SInit();
}

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
  _UNKNOWN m_unk_field_8;
  // C
  // FIXME: What the heck is this type? 00190620
  _UNKNOWN m_unk_field_C;
  // 10
  _UNKNOWN m_unk_field_10;
  // 14
  _UNKNOWN m_unk_field_14;
  // 18
  int m_unk_field_18;
  
  // ?
  
  // 28
  _UNKNOWN m_unk_field_28;
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
  _UNKNOWN m_unk_field_8;
  // C
  // (70 32-bit words ; size 0x1C0)
  std::array<_UNKNOWN, 70> m_unk_field_C;

  // ?

  // 20C
  s32 m_unk_field_20C;
  // 210
  _UNKNOWN m_unk_field_210;
  // 214
  _UNKNOWN m_unk_field_214;
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
  _UNKNOWNPOINTER m_unk_field_4;
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

// 0018E410
void sndPortSqPause(int port_no);

// 0018E460
void sndPortSqReplay(int port_no);

// 00190530
void sndStreamPause();

// 00190560
void sndStreamRePlay();

// 00190590
int sndStreamGetState();