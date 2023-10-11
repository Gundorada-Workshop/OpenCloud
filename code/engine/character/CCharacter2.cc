#include "common/log.h"
#include "common/debug.h"
#include "common/macros.h"

#include "engine/character/CCharacter2.h"

set_log_channel("character");

// 00172DE0
//void CCharacter2::SetPosition(const vec3& v)
//{
//  log_trace("CCharacter2::{}({})", __func__, fmt::ptr(&v));
//
//  mgCObject::SetPosition(v);
//}

// 00172DE0
void CCharacter2::SetPosition(MAYBE_UNUSED f32 x, MAYBE_UNUSED f32 y, MAYBE_UNUSED f32 z)
{
  log_trace("CCharacter2::{}({}, {}, {})", __func__, x, y, z);

  //mgCObject::SetPosition({ x, y, z });
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
void CCharacter2::DrawStep()
{
  log_trace("CCharacter2::{}()", __func__);

  todo;
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
bool CCharacter2::CheckMotionEnd() const
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
f32 CCharacter2::GetNowFrameWait() const
{
  log_trace("CCharacter2::{}()", __func__);

  return m_now_frame_wait;
}

// 00173890
f32 CCharacter2::GetChgStepWait() const
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
  //m_unk_field_2C0->SetPosition(m_position);
  //m_unk_field_2C0->SetRotation(m_rotation);
  //m_unk_field_2C0->SetScale(m_scale);

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
//void CCharacter2::SetWind(f32 velocity, vec4& direction)
//{
//  log_trace("CCharacter2::{}({}, {})", __func__, velocity, fmt::ptr(&direction));
//
//  for (sint i = 0; i < m_n_unk_field_130; ++i)
//  {
//    m_unk_field_130[i].SetWind(velocity, direction);
//  }
//}

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
void CCharacter2::AddOutLine(MAYBE_UNUSED const char* frame_name, MAYBE_UNUSED COutLineDraw* outline)
{
  log_trace("CCharacter2::{}({}, {})", __func__, frame_name, fmt::ptr(outline));

  todo;
}

// 00172F00
void CCharacter2::CopyOutLine(MAYBE_UNUSED CCharacter2* other)
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
void CCharacter2::SetDAnimeEnable(MAYBE_UNUSED bool flag)
{
  log_trace("CCharacter2::{}({})", __func__, flag);

  todo;
}

// 00173B30
void CCharacter2::GetSoundInfoCopy(MAYBE_UNUSED mgCMemory* memory)
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
void CCharacter2::StepDA(MAYBE_UNUSED s32 steps)
{
  log_trace("CCharacter2::{}({})", __func__, steps);

  todo;
}

// 001743C0
//void CCharacter2::SetWind(f32 velocity, const vec3& direction)
//{
//  log_trace("CCharacter2::{}({}, {})", __func__, velocity, direction);
//
//  todo;
//}

// 00174AD0
CHRINFO_KEY_SET* CCharacter2::GetKeyListPtr(MAYBE_UNUSED std::string key_name, MAYBE_UNUSED s32* index_dest)
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
//vec3 CCharacter2::GetEntryObjectPos(usize object_index)
//{
//  log_trace("CCharacter2::{}({})", __func__, object_index);
//
//  todo;
//  return vec3{ 0.0f };
//}

// 00174FE0
//matrix4 CCharacter2::GetEntryObjectPosMatrix(usize object_index)
//{
//  log_trace("CCharacter2::{}({})", __func__, object_index);
//
//  todo;
//  return matrix4{ 1.0f };
//}

// 00175080
//vec3 CCharacter2::GetEntryObjectPos(usize i1, usize i2)
//{
//  log_trace("CCharacter2::{}({}, {})", __func__, i1, i2);
//
//  todo;
//  return vec3{ 0.0f };
//}

// 00175160
f32 CCharacter2::GetWaitToFrame(MAYBE_UNUSED std::string key_name, MAYBE_UNUSED f32 rate)
{
  log_trace("CCharacter2::{}({}, {})", __func__, key_name, rate);

  todo;
  return 0.0f;
}

// 001751C0
void CCharacter2::LoadSkin(MAYBE_UNUSED uint* i1, MAYBE_UNUSED char* c1, MAYBE_UNUSED char* c2, MAYBE_UNUSED mgCMemory* memory, MAYBE_UNUSED sint i2)
{
  log_trace("CCharacter2::{}({}, {}, {}, {}, {})", __func__, fmt::ptr(i1), c1, c2, fmt::ptr(memory), i2);

  todo;
}

// 00177A30
void CCharacter2::ExecEntryEffect(MAYBE_UNUSED CHRINFO_KEY_SET* keys)
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
void CCharacter2::ChangeLOD(MAYBE_UNUSED usize lod)
{
  log_trace("CCharacter2::{}({})", __func__, lod);

  todo;
}