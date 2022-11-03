#pragma once
#include "common/debug.h"
#include "common/types.h"

// ~ 00188880 - 00190840

// TODO THIS FILE
class CSound {};
struct sndTrack {};
class sndCSeSeq {};
struct SND_LOOP_SE_SEQ {};
class sndCSeSeqData{};

class CLoopSeMngr
{
public:
  // 0018C550
  void Initialize();

  usize m_n_unk_field_4;
  _UNKNOWNPOINTER m_unk_field_4;
};