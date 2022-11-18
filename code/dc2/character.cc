#include "common/log.h"

#include "dc2/character.h"
#include "dc2/mg_lib.h"
#include "dc2/script_interpreter.h"

set_log_channel("character")

// 00172DE0
void CCharacter2::SetPosition(glm::vec4& v)
{
  log_trace("CCharacter2::{}({})", __func__, fmt::ptr(&v));

  mgCObject::SetPosition(v);
}

// 00172DE0
void CCharacter2::SetPosition(float x, float y, float z)
{
  log_trace("CCharacter2::{}({}, {}, {})", __func__, x, y, z);

  mgCObject::SetPosition({ x, y, z, 1.0f });
}

// 00172F60
_UNKNOWNPOINTER CCharacter2::Draw()
{
  log_trace("CCharacter2::{}()", __func__);

  todo;
  return nullptr;
}

CCharacter2::CCharacter2()
{
  for (auto& v : m_unk_field_140)
  {
    v = glm::ivec4(0, 0, -1, 0);
  }
}

// 001731F0
_UNKNOWNPOINTER CCharacter2::DrawDirect()
{
  log_trace("CCharacter2::{}()", __func__);

  todo;
  return nullptr;
}

void CCharacter2::Initialize()
{
  log_trace("CCharacter2::Initialize()");
  log_warn("Initialize should not be called (unless the game actually uses this as a virtual method on unknown type)");
  new (this) CCharacter2();
}

// 00173170
float CCharacter2::GetCameraDist()
{
  log_trace("CCharacter2::{}()", __func__);

  todo;
  return 0.0f;
}

// 00173120
bool CCharacter2::DrawStep()
{
  log_trace("CCharacter2::{}()", __func__);

  todo;
  return false;
}

// 001751D0
void CCharacter2::LoadPack(void* file_buf, char* file_name, mgCMemory* mem1, mgCMemory* mem2, mgCMemory* mem3, _DWORD i, CCharacter2* character2)
{
  log_trace("CCharacter2::{}({}, {}, {}, {}, {}, {}, {})", __func__, fmt::ptr(file_buf), file_name, fmt::ptr(mem1), fmt::ptr(mem2), fmt::ptr(mem3), i, fmt::ptr(character2));

  LoadChrFile(file_buf, file_name, mem1, mem2, mem3, i, character2, true);
}
// 00175200
void CCharacter2::LoadPackNoLine(void* file_buf, char* file_name, mgCMemory* mem1, mgCMemory* mem2, mgCMemory* mem3, _DWORD i, CCharacter2* character2)
{
  log_trace("CCharacter2::{}({}, {}, {}, {}, {}, {}, {})", __func__, fmt::ptr(file_buf), file_name, fmt::ptr(mem1), fmt::ptr(mem2), fmt::ptr(mem3), i, fmt::ptr(character2));

  LoadChrFile(file_buf, file_name, mem1, mem2, mem3, i, character2, false);
}
// 00175230
void CCharacter2::LoadChrFile(void* file_buf, char* file_name, mgCMemory* mem1, mgCMemory* mem2, mgCMemory* mem3, _DWORD i, CCharacter2* character2, bool b)
{
  log_trace("CCharacter2::{}({}, {}, {}, {}, {}, {}, {}, {})", __func__, fmt::ptr(file_buf), file_name, fmt::ptr(mem1), fmt::ptr(mem2), fmt::ptr(mem3), i, fmt::ptr(character2), b);

  todo;
}

// 00168410
int CCharacter2::GetMotionStatus()
{
  log_trace("CCharacter2::{}()", __func__);

  return m_motion_status;
}
// 00168420
_UNKNOWNPOINTER CCharacter2::GetNowMotionName()
{
  log_trace("CCharacter2::{}()", __func__);

  return m_now_motion_name;
}

// 001738C0
bool CCharacter2::CheckMotionEnd()
{
  log_trace("CCharacter2::{}()", __func__);

  if (m_now_motion_name == nullptr)
  {
    return true;
  }

  // 001738D4
  todo;
  return false;
}

// 00168440
float CCharacter2::GetNowFrameWait()
{
  log_trace("CCharacter2::{}()", __func__);

  return m_now_frame_wait;
}

// 00173890
float CCharacter2::GetChgStepWait()
{
  log_trace("CCharacter2::{}()", __func__);

  if (m_motion_status != 3)
  {
    return -1.0f;
  }

  return m_chg_step_wait;
}


// 00168450
void CCharacter2::SetNowFrame(float now_frame)
{
  log_trace("CCharacter2::{}({})", __func__, now_frame);

  m_now_frame = now_frame;
}

// 001739B0
void CCharacter2::SetNowFrameWeight(float weight)
{
  log_trace("CCharacter2::{}({})", __func__, weight);

  if (m_now_motion_name == nullptr)
  {
    return;
  }

  weight = std::clamp(weight, 0.0f, 1.0f);

  // 001739FC
  todo;
  // virtual call (t9) = SetNowFrame(...)
}

// 00168460
float CCharacter2::GetNowFrame()
{
  log_trace("CCharacter2::{}()", __func__);

  return m_now_frame;
}

// 00175160
float CCharacter2::GetWaitToFrame(const char* c, float f)
{
  log_trace("CCharacter2::{}({}, {})", __func__, c, f);

  todo;
  return 0.0f;
}

// 00173930
void CCharacter2::SetMotion(_DWORD i1, _DWORD i2)
{
  log_trace("CCharacter2::{}({}, {})", __func__, i1, i2);

  todo;
}

// 001739A0
void CCharacter2::SetMotion(char* c, int i)
{
  log_trace("CCharacter2::{}({}, {})", __func__, c, i);

  SetMotionPara(c, i, -1);
}

// 00173870
void CCharacter2::ResetMotion()
{
  log_trace("CCharacter2::{}()", __func__);

  m_now_motion_name = nullptr;
  m_unk_field_368 = 0;
  m_unk_field_3A8 = 0;
  m_unk_field_3A4 = 0;
}

// 00173860
void CCharacter2::SetStep(float frame_step)
{
  log_trace("CCharacter2::{}()", __func__);

  m_frame_step = frame_step;
}

// 00168470
float CCharacter2::GetStep()
{
  log_trace("CCharacter2::{}()", __func__);

  return m_now_frame;
}

// 00173840
float CCharacter2::GetDefaultStep()
{
  log_trace("CCharacter2::{}()", __func__);

  if (m_now_motion_name == nullptr)
  {
    return 0.0f;
  }

  // 0017384C
  todo;
  return 0.0f;
}

// 00168480
void CCharacter2::SetFadeFlag(bool flag)
{
  log_trace("CCharacter2::{}({})", __func__, flag);

  m_fade_flag = flag;
}

// 00168490
bool CCharacter2::GetFadeFlag()
{
  log_trace("CCharacter2::{}()", __func__);

  return m_fade_flag;
}

// 00173610
_UNKNOWNPOINTER CCharacter2::DrawShadowDirect()
{
  log_trace("CCharacter2::{}()", __func__);

  if (!m_visible || !CheckDraw() || m_unk_field_2C0 == nullptr)
  {
    return nullptr;
  }

  ShadowStep();
  m_unk_field_2C0->SetPosition(m_position);
  m_unk_field_2C0->SetRotation(m_rotation);
  m_unk_field_2C0->SetScale(m_scale);

  // 001736A8
  todo;
  return nullptr;
}

// 00174580
void CCharacter2::NormalDrive()
{
  log_trace("CCharacter2::{}()", __func__);

  todo;
}

// 00173ED0
void CCharacter2::Step()
{
  log_trace("CCharacter2::{}()", __func__);

  todo;
}

// 00174910
void CCharacter2::ShadowStep()
{
  log_trace("CCharacter2::{}()", __func__);

  todo;
}

// 001743C0
void CCharacter2::SetWind(float velocity, glm::vec4& direction)
{
  log_trace("CCharacter2::{}({}, {})", __func__, velocity, fmt::ptr(&direction));

  for (int i = 0; i < m_n_unk_field_130; ++i)
  {
    m_unk_field_130[i].SetWind(velocity, direction);
  }
}

// 00174440
void CCharacter2::ResetWind()
{
  log_trace("CCharacter2::{}()", __func__);

  for (int i = 0; i < m_n_unk_field_130; ++i)
  {
    m_unk_field_130[i].ResetWind();
  }
}

// 001744A0
void CCharacter2::SetFloor(float floor)
{
  log_trace("CCharacter2::{}({})", __func__, floor);

  todo;
}

// 00174520
void CCharacter2::ResetFloor()
{
  log_trace("CCharacter2::{}()", __func__);

  todo;
}

// 00178C70
void CCharacter2::Copy(CCharacter2& other, mgCMemory* memory)
{
  log_trace("CCharacter2::{}({}, {})", __func__, fmt::ptr(&other), fmt::ptr(memory));

  todo;
}

// 001684A0
s32 CCharacter2::GetCopySize()
{
  log_trace("CCharacter2::{}()", __func__);

  return m_unk_field_11C > 0 ? m_unk_field_11C : m_unk_field_118;
}

// 00177CB0
void CCharacter2::DrawEffect()
{
  log_trace("CCharacter2::{}()", __func__);

  todo;
}

// 00173A40
void CCharacter2::SetMotionPara(char* c, int i1, s32 i2)
{
  log_trace("CCharacter2::{}({}, {}, {})", __func__, c, i1, i2);

  todo;
}

// 00177f20
static bool _SKIN_IMG(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00177f80
static bool _SKIN_IMG_END(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00177f90
static bool _SKIN_MODEL(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00178170
static bool _SKIN_MOTION(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00334db0
static const std::array<SPI_TAG_PARAM, 5> skin_tag =
{
  "IMG",     _SKIN_IMG,
  "IMG_END", _SKIN_IMG_END,
  "MODEL",   _SKIN_MODEL,
  "MOTION",  _SKIN_MOTION,
  NULL, nullptr
};

CDynamicAnime* dynNowDA{ nullptr };
mgCMemory* dynStack{ nullptr };

// 0017b160
static bool dynFRAME_START(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b190
static bool dynFRAME(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b210
static bool dynFRAME_END(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  // this function actually just returns true
  return true;
}

// 0017b220
static bool dynVERTEX_START(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  const int var = spiGetStackInt(stack);
  dynNowDA->NewVertexTable(var, dynStack);

  return true;
}

// 0017b300
static bool dynVERTEX_L(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  const int frame_id = spiGetStackInt(stack);

  vec3 vec{ };
  spiGetStackVector(vec, ++stack);

  todo;

  return true;
}

// 0017b390
static bool dynVERTEX_END(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b410
static bool dynFIX_VERTEX_START(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b530
static bool dynFIX_VERTEX(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b5c0
static bool dynFIX_VERTEX_C(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b650
static bool dynFIX_VERTEX_S(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b6e0
static bool dynFIX_VERTEX_END(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b8b0
static bool dynFRAME_POSE(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b8b0
static bool dynFRAME_POSE_L(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b970
static bool dynDRAW_FRAME(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b9f0
static bool dynBIND_VERTEX_START(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017ba20
static bool dynBIND_VERTEX(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017bb80
static bool dynBIND_VERTEX_END(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  // this function actually just returns true
  return true;
}

// 0017bb90
static bool dynBOUNDING_BOX_START(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  const int var = spiGetStackInt(stack);
  dynNowDA->NewBoundingBoxTable(var, dynStack);

  return true;
}

// 0017bbc0
static bool dynBOUNDING_BOX(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017bc70
static bool dynBOUNDING_BOX_END(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  // this function actually just returns true
  return true;
}

// 0017bc80
static bool dynCOLLISION_START(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  const int var = spiGetStackInt(stack);
  dynNowDA->NewCollisionTable(var, dynStack);

  return true;
}

// 0017bcb0
static bool dynCOLLISION(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017be60
static bool dynCOLLISION_END(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  // this function actuall just returns true
  return true;
}

// 0017be70
static bool dynGRAVITY(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017bed0
static bool dynWIND(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

const std::array<SPI_TAG_PARAM, 27> dynmc_tag =
{
  "FRAME_START",        dynFRAME_START,
  "FRAME",              dynFRAME,
  "FRAME_END",          dynFRAME_END,
  "VERTEX_START",       dynVERTEX_START,
  "VERTEX_END",         dynVERTEX_END,
  "FIX_VERTEX_START",   dynFIX_VERTEX_START,
  "FIX_VERTEX",         dynFIX_VERTEX,
  "FIX_VERTEX_C",       dynFIX_VERTEX_C,
  "FIX_VERTEX_S",       dynFIX_VERTEX_S,
  "FIX_VERTEX_END",     dynFIX_VERTEX_END,
  "FRAME_POSE",         dynFRAME_POSE,
  "FRAME_POST_L",       dynFRAME_POSE_L,
  "DRAW_FRAME",         dynDRAW_FRAME,
  "BIND_VERTEX_START",  dynBIND_VERTEX_START,
  "BIND_VERTEX",        dynBIND_VERTEX,
  "BIND_VERTEX_END",    dynBIND_VERTEX_END,
  "BOUNDING_BOX_START", dynBOUNDING_BOX_START,
  "BOUNDING_BOX",       dynBOUNDING_BOX,
  "BOUNDING_BOX_END",   dynBOUNDING_BOX_END,
  "COLLISION_START",    dynCOLLISION_START,
  "COLISSION",          dynCOLLISION,
  "GRAVITY",            dynGRAVITY,
  "WIND",               dynWIND,
  NULL, nullptr
};

void CDynamicAnime::Load(const char* script, int script_size, mgCFrame* frame, mgCMemory* stack)
{
  log_trace("CDynamicAnime::Load({}, {}, {}, {})", fmt::ptr(script), script_size, fmt::ptr(frame), fmt::ptr(stack));

  todo;
}

void CDynamicAnime::NewVertexTable(int unk, mgCMemory* stack)
{
  log_trace("CDynamicAnime::NewVertexTable({}, {})", unk, fmt::ptr(stack));

  todo;
}

void CDynamicAnime::NewBoundingBoxTable(int unk, mgCMemory* stack)
{
  log_trace("CDynamicAnime::NewBoundingBoxTable({}, {})", unk, fmt::ptr(stack));

  todo;
}

void CDynamicAnime::NewCollisionTable(int unk, mgCMemory* stack)
{
  log_trace("CDynamicAnime::NewCollisionTable({}, {})", unk, fmt::ptr(stack));

  todo;
}

// 00179E70
void CDynamicAnime::SetWind(float velocity, glm::vec4& direction)
{
  log_trace("CDynamicAnime::SetWind({}, {})", velocity, fmt::ptr(&direction));

  m_wind_velocity = velocity;
  m_wind_direction = glm::normalize(direction);
}

// 00179E80
void CDynamicAnime::ResetWind()
{
  log_trace("CDynamicAnime::ResetWind()");

  m_wind_velocity = 0.0f;
}

// 00179E90
void CDynamicAnime::SetFloor(float floor)
{
  log_trace("CDynamicAnime::SetFloor({})", floor);

  m_unk_field_88 = true;
  m_floor = floor;
}

// 00179EA0
void CDynamicAnime::ResetFloor()
{
  log_trace("CDynamicAnime::ResetFloor()");

  m_unk_field_88 = false;
}