#include "glm/glm.hpp"
#include "common/log.h"
#include "common/types.h"
#include "dngmenu.h"
#include "effect.h"
#include "event_func.h"
#include "mg_lib.h"

set_log_channel("event_func");

// 00377CD4
static CMarker EventMarker{};
// 01ECE880
static CEohMother EventObjHandleMother{};
// 01ECEA80
static CEventSpriteMother esMother{};
// 01ECEEC0
static std::array<u32, 0x40> EventLocalFlag{};
// 01ECEFC0
static std::array<u32, 0x40> EventLocalCnt{};
// 01ECF0C0
static CRain EventRain{};
// 01EE00B0
static std::array<CHitEffectImage, 5> HitEffect{};
// 01EE0290
static std::array<char, 0x40> PakuAnimName{};
// 01EE02D0
static std::array<char, 0x40> PakuAnimName2{};
// 01EE0310
static std::array<char, 0x40> PakuMotionName{};
// 01EE0350
static std::array<char, 0x40> PakuMotionName2{};
// 01EE0390
static std::array<char, 0x8010> alignas(16) event_snd_buff {};
// 01EE83A0
static mgCMemory BuffEventSnd{};
// 01EE83D0
static std::array<char, 0x1410> alignas(16) event_snd2_buff {};
// 01EE97E0
static mgCMemory BuffEventSnd2{};
// 01EE9810
static CDngFreeMap EventDngMap{};
// 01EE9920
static std::array<_SEN_CMR_SEQ, 0x100> cmr_seq_tbl{};
// 01EEF920
static CSceneCmrSeq CameraSeq{};
// 01EF0430
static std::array<_SEN_OBJ_SEQ, 0x100> obj_seq_tbl{};
// 01EF5430
static std::array<CSceneObjSeq, 0x20> ObjectSeq{};
// 01F01230
static std::array<CEventSprite2, 0x30> EventSprite2{};
// 01F02A30
static CEventScriptArg EventScriptArg{};
// 01F02A40
static CScreenEffect EventScreenEffect{};

// 00255B80
void SPLINE_KEY::Initialize()
{
  log_trace("SPLINE_KEY::Initialize()");

  m_unk_field_0 = 0;
  m_unk_field_4 = 0;
  m_unk_field_8 = 0;
  m_unk_field_C = 0;
  m_unk_field_10 = 0;
  m_unk_field_14 = 0;
  m_unk_field_18 = 0;
  m_unk_field_1C = 0;
  m_unk_field_20 = 0;
  m_unk_field_24 = 0;
  m_unk_field_28 = 0;
  m_unk_field_2C = 0;
  m_unk_field_30 = 0;
  m_unk_field_34 = 0;
}

// 00255BC0
C3DSpline::C3DSpline()
{
  log_trace("C3DSpline::C3DSpline()");

  Initialize();
}

// 00255BF0
void C3DSpline::Initialize()
{
  log_trace("C3DSpline::Initialize()");

  for (auto& spline_key : m_spline_keys)
  {
    spline_key.Initialize();
  }

  m_unk_field_380 = 0;
  m_unk_field_384 = 0;
  m_unk_field_388 = 0;
  m_unk_field_398 = 0;
}

// 00256380
CCameraPas::CCameraPas()
{
  log_trace("CCameraPas::CCameraPas()");

  new (&m_unk_field_208) C3DSpline();
  new (&m_unk_field_5A4) C3DSpline();
  Initialize();
}
// 00256710
void CCameraPas::Initialize()
{
  log_trace("CCameraPas::Initialize()");

  for (auto& v : m_unk_field_0)
  {
    v = glm::vec4(0.0f);
  }

  for (auto& v : m_unk_field_100)
  {
    v = glm::vec4(0.0f);
  }

  m_unk_field_200 = 0;
  m_unk_field_940 = 0;
  m_unk_field_204 = 0;

  m_unk_field_208.Initialize();
  m_unk_field_5A4.Initialize();
}

// 00259100
void _SEN_CMR_SEQ::Initialize()
{
  log_trace("_SEN_CMR_SEQ::Initialize()");

  m_unk_field_0 = 0;
  m_unk_field_10 = glm::vec4(0.0f);
  m_unk_field_20 = glm::vec4(0.0f);
  m_unk_field_30 = 0;
  m_unk_field_34 = 0;
  m_unk_field_38 = 0;
  m_unk_field_3C[0] = '\0';
  m_unk_field_5C = 0;
}

// 00259160
CSceneCmrSeq::CSceneCmrSeq()
{
  log_trace("CSceneCmrSeq::{}()", __func__);

  new (&m_unk_field_1C0) CCameraPas();
  ZeroInitialize();
}

// 002591A0
void CSceneCmrSeq::ZeroInitialize()
{
  log_trace("CSceneCmrSeq::{}()", __func__);

  m_sequences = nullptr;
  m_n_sequences = 0;
  m_unk_field_50 = glm::vec4(0.0f);
  m_unk_field_60 = glm::vec4(0.0f);
  Clear();
}

// 002591E0
void CSceneCmrSeq::Initialize(_SEN_CMR_SEQ* seq, usize length)
{
  log_trace("CSceneCmrSeq::{}({}, {})", __func__, fmt::ptr(seq), length);

  ZeroInitialize();
  m_sequences = seq;
  m_n_sequences = length;
  Clear();
}

// 00259230
void CSceneCmrSeq::Clear()
{
  log_trace("CSceneCmrSeq::{}()", __func__);

  m_unk_field_30 = 0;
  m_unk_field_34 = 0;
  m_unk_field_38 = 0;
  m_unk_field_3C = 0;
  m_unk_field_40 = 0;
  m_unk_field_44 = 0;
  m_unk_field_48 = 0;
  m_unk_field_50 = glm::vec4(0.0f);
  m_unk_field_60 = glm::vec4(0.0f);
  m_unk_field_78 = 0;
  m_unk_field_7C = 0;
  m_unk_field_80 = -1;
  m_unk_field_84 = 0;
  m_unk_field_90 = glm::vec4(0.0f);
  m_unk_field_AC[0] = '\0';
  m_unk_field_A8 = 0;
  m_unk_field_A4 = 0;
  m_unk_field_A0 = 0;
  m_unk_field_D0 = glm::vec4(0.0f);
  m_unk_field_E0 = glm::vec4(0.0f);
  m_unk_field_FC = 0;
  m_unk_field_F8 = 0;
  m_unk_field_F0 = 0;
  m_unk_field_100 = glm::vec4(0.0f);
  m_unk_field_110 = glm::vec4(0.0f);
  m_unk_field_120 = glm::vec4(0.0f);
  m_unk_field_130 = glm::vec4(0.0f);
  m_unk_field_140 = 0;
  m_unk_field_150 = glm::vec4(0.0f);
  m_unk_field_160 = glm::vec4(0.0f);
  m_unk_field_170 = glm::vec4(0.0f);
  m_unk_field_180 = 0;
  m_unk_field_1C0.Initialize();
  m_unk_field_190 = glm::vec4(0.0f);
  m_unk_field_1A0 = glm::vec4(0.0f);
  m_unk_field_1B0 = glm::vec4(0.0f);
  m_unk_field_8 = 0;
  m_unk_field_C = 0;
  m_unk_field_10 = 0;
  m_unk_field_14 = 0;
  m_unk_field_18 = 0;
  m_unk_field_1C = 0;
  m_unk_field_20 = 0;
  m_unk_field_24 = 0;
  m_unk_field_28 = 0;
  m_unk_field_2C = 0;

  if (m_sequences != nullptr)
  {
    for (int i = 0; i < m_n_sequences; ++i)
    {
      m_sequences[i].Initialize();
    }
  }
}

// 00256B20
CCharaPas::CCharaPas()
{
  log_trace("CCharaPas::{}()", __func__);

  new (&m_unk_field_108) C3DSpline();
  Initialize();
}

// 00256B50
void CCharaPas::Initialize()
{
  log_trace("CCharaPas::{}()", __func__);

  for (auto& v : m_unk_field_0)
  {
    v = glm::vec4(0.0f);
  }
  m_unk_field_100 = 0;
  m_unk_field_104 = 0;
  m_unk_field_108.Initialize();
  m_unk_field_4A4 = 0;
  m_unk_field_4A8 = 0;
}

// 0025C170
void _SEN_OBJ_SEQ::Initialize()
{
  log_trace("_SEN_OBJ_SEQ::{}()", __func__);

  m_unk_field_0 = 0;
  m_unk_field_10 = glm::vec4(0.0f);
  m_unk_field_20 = 0;
  m_unk_field_24 = 0;
  m_unk_field_28 = 0;
  m_unk_field_2C[0] = '\0';
  m_unk_field_4C = 0;
}

// 0025C1C0
CSceneObjSeq::CSceneObjSeq()
{
  log_trace("CSceneObjSeq::{}()", __func__);

  new (&m_unk_field_140) CCharaPas();
  ZeroInitialize();
}

// 0025C220
void CSceneObjSeq::Initialize(_SEN_OBJ_SEQ* seq, usize length)
{
  log_trace("CSceneObjSeq::{}({}, {})", __func__, fmt::ptr(seq), length);

  m_sequences = seq;
  m_n_sequences = length;
  Clear();

  if (m_sequences != nullptr)
  {
    for (int i = 0; i < m_n_sequences; ++i)
    {
      m_sequences[i].Initialize();
    }
  }
}

// 0025C200
void CSceneObjSeq::ZeroInitialize()
{
  log_trace("CSceneObjSeq::{}()", __func__);
  
  m_sequences = nullptr;
  m_n_sequences = 0;
  Initialize(nullptr, 0);
}

// 0025C2A0
void CSceneObjSeq::Clear()
{
  log_trace("CSceneObjSeq::{}()", __func__);

  m_unk_field_64 = -1;
  m_unk_field_70 = glm::vec4(0.0f);
  m_unk_field_80 = glm::vec4(0.0f);
  m_unk_field_120 = glm::vec4(0.0f);
  m_unk_field_B0 = glm::vec4(0.0f);
  m_unk_field_D0 = glm::vec4(0.0f);
  m_unk_field_F0 = 0;
  m_unk_field_C0 = glm::vec4(0.0f);
  m_unk_field_E0 = glm::vec4(0.0f);
  m_unk_field_8 = 0;
  m_unk_field_C = 0;
  m_unk_field_10 = 0;
  m_unk_field_14 = 0;
  m_unk_field_18 = 0;
  m_unk_field_1C = 0;
  m_unk_field_20 = 0;
  m_unk_field_24 = -1;
  m_unk_field_28 = 0;
  m_unk_field_2C = 0;
  m_unk_field_30 = 0;
  m_unk_field_34 = 0;
  m_unk_field_38 = 0;
  m_unk_field_3C = 0;
  m_unk_field_40 = 0;
  m_unk_field_44 = 0;
  m_unk_field_48 = 0;
  m_unk_field_4C = 0;
  m_unk_field_50 = 0;
  m_unk_field_54 = 0;
  m_unk_field_58 = 0;
}

// 00282100
CRainDrop::CRainDrop()
{
  log_trace("CRainDrop::CRainDrop()");

  m_unk_field_0 = 0;
  m_unk_field_4 = 0;

  for (auto& v : m_unk_field_10)
  {
    v = glm::vec4(0, 0, 0, 1);
  }

  m_unk_field_90 = glm::vec4(0, 0, 0, 1);
  m_color = glm::u8vec4(128, 128, 128, 128);
}

// 002901F0
void CMarker::Draw()
{
  log_trace("CMarker::{}()", __func__);

  m_cnt = std::max(m_cnt - 1, 0);
}

// 00290210
void CMarker::Set(int i)
{
  log_trace("CMarker::{}({})", __func__, i);

  m_cnt = i;
}