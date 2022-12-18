#include <array>

#include "common/log.h"
#include "common/macros.h"

#include "dc2/snd_mngr.h"

set_log_channel("snd_mngr")

// 003D3680
static std::array<sndPortInfo, 0x10> PortInfo{};
// 003D6040
static std::array<sndCSeSeq, 0x20> SeSequencer{};

// 0018B4B0
void sndTrack::Initialize()
{
  log_trace("sndTrack::Initialize()");

  m_unk_field_0 = 0x7F;
  m_unk_field_1 = 0x7F;
  m_unk_field_2 = 0;
  m_unk_field_3 = 0x40;
  m_unk_field_4 = 0;
  m_unk_field_5 = 0x40;
  m_unk_field_6 = 0;

  m_n_unk_field_C = m_unk_field_C.size();
  for (auto& unk_var : m_unk_field_C)
  {
    unk_var = 0;
  }
}

// 0018C550
void CLoopSeMngr::Initialize()
{
  log_trace("CLoopSeMngr::Initialize()");

  m_n_unk_field_4 = 0;
  m_unk_field_4 = nullptr;
}

// 0018B880
void sndCSeSeq::Initialize()
{
  log_trace("sndCSeSeq::Initialize()");

  m_unk_field_10 = 0;
  m_unk_field_14 = 0;
  m_unk_field_8 = 0;
  m_unk_field_C = 0;
  m_unk_field_18 = 0x7F;
  m_unk_field_28 = 0;
  m_n_unk_field_30 = m_unk_field_30.size();

  for (int i = 0; i < m_n_unk_field_30; ++i)
  {
    m_unk_field_30[i].Initialize();
    m_unk_field_30[i].m_unk_field_6 = static_cast<s8>(i) + 0x40;
  }
}

// 00190600
sndCSeSeq::sndCSeSeq()
{
  log_trace("sndCSeSeq::sndCSeSeq()");

  for (int i = 0; i < m_unk_field_30.size(); ++i)
  {
    // FIXME: not sure how this is implemented, 00190620
    for (int j = 0; j < m_unk_field_30[j].m_unk_field_C.size(); j += 4)
    {
      m_unk_field_30[j].m_unk_field_C[j] = 0;
    }

    m_unk_field_30[i].Initialize();
  }

  Initialize();
};

// 00190680
sndPortInfo::sndPortInfo()
{
  log_trace("sndPortInfo::sndPortInfo()");

  // BUG: ? Unintentional?
  // 190680
  for (auto& unk_var : m_unk_field_C)
  {
    unk_var = 0;
  }
  for (auto& unk_var : m_unk_field_21C)
  {
    unk_var.m_unk_field_0 = -1;
  }

  // 001906DC
  m_unk_field_0 = -1;
  m_unk_field_4 = -1;
  m_unk_field_8 = 0;
  m_unk_field_20C = -1;
  m_unk_field_210 = 0;
  m_unk_field_214 = 0;
  m_unk_field_218 = -1;

  for (auto& unk_var : m_unk_field_21C)
  {
    unk_var.m_unk_field_0 = -1;
  }
  for (auto& unk_var : m_unk_field_C)
  {
    unk_var = 0;
  }
}

// 0018D1E0
void sndSetMasterVol(MAYBE_UNUSED f32 volume, MAYBE_UNUSED sint i)
{
  log_trace("{}({}, {})", __func__, volume, i);

  todo;
}

// 0018D270
f32 sndGetMasterVol(MAYBE_UNUSED sint i)
{
  log_trace("{}({})", __func__, i);

  todo;
  return 0.0f;
}

// 0018D2B0
void sndMasterVolFadeInOut(MAYBE_UNUSED sint i1, MAYBE_UNUSED sint i2, MAYBE_UNUSED f32 f1, MAYBE_UNUSED f32 f2)
{
  log_trace("{}({}, {}, {}, {})", __func__, i1, i2, f1, f2);

  todo;
}

// 0018D650
void sndStep(MAYBE_UNUSED f32 f)
{
  log_trace("{}({})", __func__, f);

  todo;
}

// 0018E060
void sndSePlay(MAYBE_UNUSED uint u1, MAYBE_UNUSED sint i1, MAYBE_UNUSED sint i2)
{
  log_trace("{}({}, {}, {})", __func__, u1, i1, i2);

  todo;
}

// 0018E410
void sndPortSqPause(MAYBE_UNUSED sint port_no)
{
  log_trace("{}({})", __func__, port_no);

  todo;
}

// 0018E460
void sndPortSqReplay(MAYBE_UNUSED sint port_no)
{
  log_trace("{}({})", __func__, port_no);

  todo;
}

// 00190530
void sndStreamPause()
{
  log_trace("{}()", __func__);

  todo;
}

// 00190560
void sndStreamRePlay()
{
  log_trace("{}()", __func__);

  todo;
}

// 00190590
int sndStreamGetState()
{
  log_trace("{}()", __func__);

  todo;
  return 0;
}