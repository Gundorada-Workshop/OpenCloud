#include "common/log.h"
#include "common/debug.h"

#include "dc2/character.h"
#include "dc2/mg/mg_lib.h"
#include "dc2/script_interpreter.h"

set_log_channel("character")

// 00172DE0
void CCharacter2::SetPosition(vec3& v)
{
  log_trace("CCharacter2::{}({})", __func__, fmt::ptr(&v));

  mgCObject::SetPosition(v);
}

// 00172DE0
void CCharacter2::SetPosition(f32 x, f32 y, f32 z)
{
  log_trace("CCharacter2::{}({}, {}, {})", __func__, x, y, z);

  mgCObject::SetPosition({ x, y, z });
}

// 00172F60
unkptr CCharacter2::Draw()
{
  log_trace("CCharacter2::{}()", __func__);

  todo;

  return nullptr;
}

CCharacter2::CCharacter2()
{
  /*
  for (auto& v : m_unk_field_140)
  {
    v = ivec4(0, 0, -1, 0);
  }
  */
}

// 001731F0
unkptr CCharacter2::DrawDirect()
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
f32 CCharacter2::GetCameraDist()
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
void CCharacter2::LoadPack(void* file_buf, char* file_name, mgCMemory* mem1, mgCMemory* mem2, mgCMemory* mem3, unk32 i, CCharacter2* character2)
{
  log_trace("CCharacter2::{}({}, {}, {}, {}, {}, {}, {})", __func__, fmt::ptr(file_buf), file_name, fmt::ptr(mem1), fmt::ptr(mem2), fmt::ptr(mem3), i, fmt::ptr(character2));

  LoadChrFile(file_buf, file_name, mem1, mem2, mem3, i, character2, true);
}

// 00175200
void CCharacter2::LoadPackNoLine(void* file_buf, char* file_name, mgCMemory* mem1, mgCMemory* mem2, mgCMemory* mem3, unk32 i, CCharacter2* character2)
{
  log_trace("CCharacter2::{}({}, {}, {}, {}, {}, {}, {})", __func__, fmt::ptr(file_buf), file_name, fmt::ptr(mem1), fmt::ptr(mem2), fmt::ptr(mem3), i, fmt::ptr(character2));

  LoadChrFile(file_buf, file_name, mem1, mem2, mem3, i, character2, false);
}
// 00175230
void CCharacter2::LoadChrFile(MAYBE_UNUSED void* file_buf, MAYBE_UNUSED char* file_name,
  MAYBE_UNUSED mgCMemory* mem1, MAYBE_UNUSED mgCMemory* mem2,
  MAYBE_UNUSED mgCMemory* mem3, MAYBE_UNUSED unk32 i,
  MAYBE_UNUSED CCharacter2* character2, MAYBE_UNUSED bool b)
{
  log_trace("CCharacter2::{}({}, {}, {}, {}, {}, {}, {}, {})", __func__, fmt::ptr(file_buf), file_name, fmt::ptr(mem1), fmt::ptr(mem2), fmt::ptr(mem3), i, fmt::ptr(character2), b);

  todo;
}

// 00168410
ECharacterMotionStatus CCharacter2::GetMotionStatus()
{
  log_trace("CCharacter2::{}()", __func__);

  return m_motion_status;
}
// 00168420
std::string CCharacter2::GetNowMotionName()
{
  log_trace("CCharacter2::{}()", __func__);

  return m_now_motion->m_name;
}

// 001738C0
bool CCharacter2::CheckMotionEnd()
{
  log_trace("CCharacter2::{}()", __func__);

  if (m_now_motion == nullptr)
  {
    return true;
  }

  // 001738D4
  todo;
  return false;
}

// 00168440
f32 CCharacter2::GetNowFrameWait()
{
  log_trace("CCharacter2::{}()", __func__);

  return m_now_frame_wait;
}

// 00173890
f32 CCharacter2::GetChgStepWait()
{
  log_trace("CCharacter2::{}()", __func__);

  if (m_motion_status != ECharacterMotionStatus::_3)
  {
    return -1.0f;
  }

  return m_chg_step_wait;
}


// 00168450
void CCharacter2::SetNowFrame(f32 now_frame)
{
  log_trace("CCharacter2::{}({})", __func__, now_frame);

  m_now_frame = now_frame;
}

// 001739B0
void CCharacter2::SetNowFrameWeight(f32 weight)
{
  log_trace("CCharacter2::{}({})", __func__, weight);

  if (m_now_motion == nullptr)
  {
    return;
  }

  weight = std::clamp(weight, 0.0f, 1.0f);

  // 001739FC
  todo;
  // virtual call (t9) = SetNowFrame(...)
}

// 00168460
f32 CCharacter2::GetNowFrame()
{
  log_trace("CCharacter2::{}()", __func__);

  return m_now_frame;
}

// 00175160
f32 CCharacter2::GetWaitToFrame(MAYBE_UNUSED const char* c, MAYBE_UNUSED f32 f)
{
  log_trace("CCharacter2::{}({}, {})", __func__, c, f);

  todo;
  return 0.0f;
}

// 00173930
void CCharacter2::SetMotion(MAYBE_UNUSED unk32 i1, MAYBE_UNUSED unk32 i2)
{
  log_trace("CCharacter2::{}({}, {})", __func__, i1, i2);

  todo;
}

// 001739A0
void CCharacter2::SetMotion(std::string key_name, sint i)
{
  log_trace("CCharacter2::{}({}, {})", __func__, key_name, i);

  SetMotionPara(key_name, i, -1);
}

// 00173870
void CCharacter2::ResetMotion()
{
  log_trace("CCharacter2::{}()", __func__);

  m_now_motion = nullptr;
  m_unk_field_368 = 0;
  m_unk_field_3A8 = 0;
  m_unk_field_3A4 = 0;
}

// 00173860
void CCharacter2::SetStep(f32 frame_step)
{
  log_trace("CCharacter2::{}()", __func__);

  m_frame_step = frame_step;
}

// 00168470
f32 CCharacter2::GetStep()
{
  log_trace("CCharacter2::{}()", __func__);

  return m_now_frame;
}

// 00173840
f32 CCharacter2::GetDefaultStep()
{
  log_trace("CCharacter2::{}()", __func__);

  if (m_now_motion == nullptr)
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
unkptr CCharacter2::DrawShadowDirect()
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
void CCharacter2::SetWind(f32 velocity, vec4& direction)
{
  log_trace("CCharacter2::{}({}, {})", __func__, velocity, fmt::ptr(&direction));

  for (sint i = 0; i < m_n_unk_field_130; ++i)
  {
    m_unk_field_130[i].SetWind(velocity, direction);
  }
}

// 00174440
void CCharacter2::ResetWind()
{
  log_trace("CCharacter2::{}()", __func__);

  for (sint i = 0; i < m_n_unk_field_130; ++i)
  {
    m_unk_field_130[i].ResetWind();
  }
}

// 001744A0
void CCharacter2::SetFloor(MAYBE_UNUSED f32 floor)
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
void CCharacter2::Copy(MAYBE_UNUSED CCharacter2& other, MAYBE_UNUSED mgCMemory* memory)
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

// 00172DF0
void CCharacter2::AddOutLine(const char* frame_name, COutLineDraw* outline)
{
  log_trace("CCharacter2::{}({}, {})", __func__, frame_name, fmt::ptr(outline));

  todo;
}

// 00172F00
void CCharacter2::CopyOutLine(CCharacter2* other)
{
  log_trace("CCharacter2::{}({})", __func__, fmt::ptr(other));

  todo;
}

// 00172F60
void CCharacter2::SetDeformMesh()
{
  log_trace("CCharacter2::{}()", __func__);

  todo;
}

// 00173700
void CCharacter2::UpdatePosition()
{
  log_trace("CCharacter2::{}()", __func__);

  todo;
}

// 001737B0
void CCharacter2::ResetDAPosition()
{
  log_trace("CCharacter2::{}()", __func__);

  todo;
}

// 00173A40
void CCharacter2::SetMotionPara(MAYBE_UNUSED std::string key_name, MAYBE_UNUSED sint i1, MAYBE_UNUSED s32 i2)
{
  log_trace("CCharacter2::{}({}, {}, {})", __func__, key_name, i1, i2);

  todo;
}

// 00173B00
void CCharacter2::SetDAnimeEnable(bool flag)
{
  log_trace("CCharacter2::{}({})", __func__, flag);

  todo;
}

// 00173B30
void CCharacter2::GetSoundInfoCopy(mgCMemory* memory)
{
  log_trace("CCharacter2::{}({})", __func__, fmt::ptr(memory));

  todo;
}

// 00173BC0
s32 CCharacter2::CheckFootEffect()
{
  log_trace("CCharacter2::{}()", __func__);

  todo;
  return -1;
}

// 00173BF0
void CCharacter2::SePlay()
{
  log_trace("CCharacter2::{}()", __func__);

  todo;
}

// 001742E0
void CCharacter2::StepDA(s32 steps)
{
  log_trace("CCharacter2::{}({})", __func__, steps);

  todo;
}

// 001743C0
void CCharacter2::SetWind(f32 velocity, const vec3& direction)
{
  log_trace("CCharacter2::{}({}, {})", __func__, velocity, direction);

  todo;
}

// 00174AD0
CHRINFO_KEY_SET* CCharacter2::GetKeyListPtr(std::string key_name, s32* index_dest)
{
  log_trace("CCharacter2::{}()", __func__);

  todo;
  return nullptr;
}

// 00174C70
void CCharacter2::DeleteExtMotion()
{
  log_trace("CCharacter2::{}()", __func__);

  todo;
}

// 00174E60
void CCharacter2::DeleteImage()
{
  log_trace("CCharacter2::{}()", __func__);

  todo;
}

// 00174F50
vec3 CCharacter2::GetEntryObjectPos(usize object_index)
{
  log_trace("CCharacter2::{}({})", __func__, object_index);

  todo;
  return vec3{ 0.0f };
}

// 00174FE0
matrix4 CCharacter2::GetEntryObjectPosMatrix(usize object_index)
{
  log_trace("CCharacter2::{}({})", __func__, object_index);

  todo;
  return matrix4{ 1.0f };
}

// 00175080
vec3 CCharacter2::GetEntryObjectPos(usize i1, usize i2)
{
  log_trace("CCharacter2::{}({}, {})", __func__, i1, i2);

  todo;
  return vec3{ 0.0f };
}

// 00175160
f32 CCharacter2::GetWaitToFrame(std::string key_name, f32 rate)
{
  log_trace("CCharacter2::{}({}, {})", __func__, key_name, rate);

  todo;
  return 0.0f;
}

// 001751C0
void CCharacter2::LoadSkin(uint* i1, char* c1, char* c2, mgCMemory* memory, sint i2)
{
  log_trace("CCharacter2::{}({}, {}, {}, {}, {})", __func__, fmt::ptr(i1), c1, c2, fmt::ptr(memory), i2);

  todo;
}

// 001751D0
void CCharacter2::LoadPack(uint* i1, char* c, mgCMemory* memory1, mgCMemory* memory2, mgCMemory* memory3, sint i2, CCharacter2* chara)
{
  log_trace("CCharacter2::{}({}, {}, {}, {}, {}, {}, {})", __func__, fmt::ptr(i1), c, fmt::ptr(memory1), fmt::ptr(memory2), fmt::ptr(memory3), i2, fmt::ptr(chara));

  todo;
}

// 00175200
void CCharacter2::LoadPackNoLine(uint* i1, char* c, mgCMemory* memory1, mgCMemory* memory2, mgCMemory* memory3, sint i2, CCharacter2* chara)
{
  log_trace("CCharacter2::{}({}, {}, {}, {}, {}, {}, {})", __func__, fmt::ptr(i1), c, fmt::ptr(memory1), fmt::ptr(memory2), fmt::ptr(memory3), i2, fmt::ptr(chara));

  todo;
}

// 00175230
void CCharacter2::LoadChrFile(uint* i1, char* c, mgCMemory* memory1, mgCMemory* memory2, mgCMemory* memory3, sint i2, CCharacter2* chara, sint i3)
{
  log_trace("CCharacter2::{}({}, {}, {}, {}, {}, {}, {}, {})", __func__, fmt::ptr(i1), c, fmt::ptr(memory1), fmt::ptr(memory2), fmt::ptr(memory3), i2, fmt::ptr(chara), i3);

  todo;
}

// 00177A30
void CCharacter2::ExecEntryEffect(CHRINFO_KEY_SET* keys)
{
  log_trace("CCharacter2::{}({})", __func__, fmt::ptr(keys));

  todo;
}

// 00177B30
void CCharacter2::CtrlEffect()
{
  log_trace("CCharacter2::{}()", __func__);

  todo;
}

// 00177C00
void CCharacter2::StepEffect()
{
  log_trace("CCharacter2::{}()", __func__);

  todo;
}

// 00178A60
void CCharacter2::ChangeLOD(usize lod)
{
  log_trace("CCharacter2::{}({})", __func__, lod);

  todo;
}

// 0016A220
void CActionChara::ResetScript()
{
  log_trace("CActionChara::{}()", __func__);

  todo;
}

// 00177f20
static bool _SKIN_IMG(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00177f80
static bool _SKIN_IMG_END(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00177f90
static bool _SKIN_MODEL(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 00178170
static bool _SKIN_MOTION(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
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
static bool dynFRAME_START(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b190
static bool dynFRAME(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b210
static bool dynFRAME_END(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  // this function actually just returns true
  return true;
}

// 0017b220
static bool dynVERTEX_START(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  const sint var = spiGetStackInt(stack);
  dynNowDA->NewVertexTable(var, dynStack);

  return true;
}

// 0017b300
static bool dynVERTEX_L(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  const sint frame_id = spiGetStackInt(stack);

  unused_v(frame_id);

  vec3 vec{ };
  spiGetStackVector(vec, ++stack);

  todo;

  return true;
}

// 0017b390
static bool dynVERTEX_END(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b410
static bool dynFIX_VERTEX_START(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b530
static bool dynFIX_VERTEX(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b5c0
static bool dynFIX_VERTEX_C(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b650
static bool dynFIX_VERTEX_S(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b6e0
static bool dynFIX_VERTEX_END(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b8b0
static bool dynFRAME_POSE(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b8b0
static bool dynFRAME_POSE_L(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b970
static bool dynDRAW_FRAME(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017b9f0
static bool dynBIND_VERTEX_START(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017ba20
static bool dynBIND_VERTEX(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017bb80
static bool dynBIND_VERTEX_END(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  // this function actually just returns true
  return true;
}

// 0017bb90
static bool dynBOUNDING_BOX_START(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  const sint var = spiGetStackInt(stack);
  dynNowDA->NewBoundingBoxTable(var, dynStack);

  return true;
}

// 0017bbc0
static bool dynBOUNDING_BOX(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017bc70
static bool dynBOUNDING_BOX_END(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  // this function actually just returns true
  return true;
}

// 0017bc80
static bool dynCOLLISION_START(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  const sint var = spiGetStackInt(stack);
  dynNowDA->NewCollisionTable(var, dynStack);

  return true;
}

// 0017bcb0
static bool dynCOLLISION(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017be60
static bool dynCOLLISION_END(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  // this function actuall just returns true
  return true;
}

// 0017be70
static bool dynGRAVITY(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0017bed0
static bool dynWIND(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
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

void CDynamicAnime::Load(MAYBE_UNUSED const char* script, MAYBE_UNUSED sint script_size, MAYBE_UNUSED mgCFrame* frame, MAYBE_UNUSED mgCMemory* stack)
{
  log_trace("CDynamicAnime::Load({}, {}, {}, {})", fmt::ptr(script), script_size, fmt::ptr(frame), fmt::ptr(stack));

  todo;
}

void CDynamicAnime::NewVertexTable(MAYBE_UNUSED sint unk, MAYBE_UNUSED mgCMemory* stack)
{
  log_trace("CDynamicAnime::NewVertexTable({}, {})", unk, fmt::ptr(stack));

  todo;
}

void CDynamicAnime::NewBoundingBoxTable(MAYBE_UNUSED sint unk, MAYBE_UNUSED mgCMemory* stack)
{
  log_trace("CDynamicAnime::NewBoundingBoxTable({}, {})", unk, fmt::ptr(stack));

  todo;
}

void CDynamicAnime::NewCollisionTable(MAYBE_UNUSED sint unk, MAYBE_UNUSED mgCMemory* stack)
{
  log_trace("CDynamicAnime::NewCollisionTable({}, {})", unk, fmt::ptr(stack));

  todo;
}

// 00179E70
void CDynamicAnime::SetWind(f32 velocity, vec4& direction)
{
  log_trace("CDynamicAnime::SetWind({}, {})", velocity, fmt::ptr(&direction));

  m_wind_velocity = velocity;
  m_wind_direction = normalize(direction);
}

// 00179E80
void CDynamicAnime::ResetWind()
{
  log_trace("CDynamicAnime::ResetWind()");

  m_wind_velocity = 0.0f;
}

// 00179E90
void CDynamicAnime::SetFloor(f32 floor)
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