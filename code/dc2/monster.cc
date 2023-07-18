#include "common/clock.h"
#include "common/constants.h"
#include "common/log.h"
#include "common/macros.h"

#include "dc2/dng_main.h"
#include "dc2/mainloop.h"
#include "dc2/monster.h"
#include "dc2/monster_func.h"
#include "dc2/run_script.h"
#include "dc2/scene.h"
#include "dc2/script_interpreter.h"
#include "dc2/snd_mngr.h"

set_log_channel("monster");

static bool _MONSTER_NAME(MAYBE_UNUSED SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  // "NAME"
  trace_script_call(stack, stack_count);

  todo;
  return false;
}

// 0034D2F0
static const std::array<SPI_TAG_PARAM, 2> mos_data_anlyze_tag =
{
  "NAME", _MONSTER_NAME,
  NULL, nullptr
};

// 001C9820
void CPiyori::Reset()
{
  log_trace("CPiyori::{}()", __func__);

  m_monster = nullptr;
  m_unk_field_1C = 0;
}

// 001C9830
void CPiyori::Set(CActiveMonster* monster, f32 f0, f32 f1, s16 i)
{
  log_trace("CPiyori::{}({}, {}, {}, {})", __func__, fmt::ptr(monster), f0, f1, i);

  if (monster == nullptr)
  {
    return;
  }

  m_monster = monster;
  m_unk_field_1C = i;

  m_unk_field_10 = 0.0f;
  m_unk_field_14 = f0;
  m_unk_field_18 = f1;

  for (usize j = 0; j < m_unk_field_4.size(); ++j)
  {
    m_unk_field_4[j] = fRand(common::math::pi2()) - common::math::pi();
  }

  m_unk_field_1E = 0;
}

// 001C98C0
void CPiyori::Set(CActiveMonster* monster, s16 i)
{
  log_trace("CPiyori::{}({}, {})", __func__, fmt::ptr(monster), i);

  if (monster == nullptr)
  {
    return;
  }

  Set(monster, monster->m_unk_field_110 * 2.0f, monster->m_unk_field_10C * 2.0f, i);
}

// 001C9900
void CPiyori::Draw()
{
  log_trace("CPiyori::{}()", __func__);

  todo;
}

// 001C9B40
void CPiyori::Step()
{
  log_trace("CPiyori::{}()", __func__);

  //if (m_monster == nullptr)
  //{
  //  return;
  //}

  //if (--m_unk_field_1C <= 0)
  //{
  //  m_monster = nullptr;
  //  return;
  //}

  //if (--m_unk_field_1E <= 0)
  //{
  //  // FIXME: MAGIC
  //  vec3 entry_pos = m_monster->GetEntryObjectPos(0);
  //  f32 fp0;
  //  f32 fp1;
  //  sndGetVolPan(&fp0, &fp1, &entry_pos, 160.0f, 1200.0f);
  //  sndSePlayVPf(GetMainScene()->m_unk_field_C4D0, 36, fp0, fp1, 0);
  //  m_unk_field_1E = 13;
  //}

  //m_unk_field_10 += common::math::pi() / GAME_FPS;
  //if (m_unk_field_10 > common::math::pi())
  //{
  //  m_unk_field_10 -= common::math::pi2();
  //}

  //for (usize i = 0; i < m_unk_field_4.size(); ++i)
  //{
  //  m_unk_field_4[i] += common::math::pi2() / GAME_FPS;

  //  if (m_unk_field_4[i] > common::math::pi())
  //  {
  //    m_unk_field_4[i] -= common::math::pi2();
  //  }
  //}
}
