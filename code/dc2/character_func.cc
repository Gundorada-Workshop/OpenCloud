#include "common/bits.h"
#include "common/debug.h"
#include "common/log.h"
#include "common/macros.h"

#include "script/rs/stack.h"

#include "dc2/character.h"
#include "dc2/character_func.h"
#include "dc2/dng_main.h"
#include "dc2/monster_func.h"
#include "dc2/run_script.h"
#include "dc2/script_interpreter.h"
#include "dc2/userdata.h"

using namespace script;

set_log_channel("character_func");

#define VERIFY_STACK_COUNT(n) \
  if (stack_count != n) UNLIKELY \
  { \
    return false; \
  }

// 01F0D430
extern ACTION_INFO action_info{};

static sint GetStackInt(rs::stack_data* stack)
{
  log_trace("{}()", __func__, fmt::ptr(stack));

  if (stack->type == rs::stack_data_type::_flt)
  {
    return static_cast<sint>(stack->_flt);
  }
  else
  {
    return stack->_int;
  }
}

static f32 GetStackFloat(rs::stack_data* stack)
{
  log_trace("{}()", __func__, fmt::ptr(stack));

  if (stack->type == rs::stack_data_type::_int)
  {
    return static_cast<f32>(stack->_int);
  }
  else
  {
    return stack->_flt;
  }
}

//MAYBE_UNUSED static vec3 GetStackVector(rs::stack_data* stack)
//{
//  log_trace("{}()", __func__, fmt::ptr(stack));
//
//  return {
//    GetStackFloat(&stack[0]),
//    GetStackFloat(&stack[1]),
//    GetStackFloat(&stack[2]),
//  };
//}

MAYBE_UNUSED static const char* GetStackString(rs::stack_data* stack)
{
  log_trace("{}()", __func__, fmt::ptr(stack));

  return stack->_str;
}

static void SetStack(rs::stack_data* stack, sint value)
{
  log_trace("{}()", __func__, fmt::ptr(stack));

  if (stack->type != rs::stack_data_type::_ptr)
  {
    return;
  }

  stack->_ptr->_int = value;
}

MAYBE_UNUSED static void SetStack(rs::stack_data* stack, f32 value)
{
  log_trace("{}()", __func__, fmt::ptr(stack));

  if (stack->type != rs::stack_data_type::_ptr)
  {
    return;
  }

  stack->_ptr->_flt = value;
}

static bool _INIT_SCRIPT(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  action_info.m_chara->ResetScript();
  return true;
}

static bool _PROG_SET(rs::stack_data* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  if (stack_count != 1)
  {
    return false;
  }

  action_info.m_chara->m_prog = static_cast<s16>(GetStackInt(stack++));
  return true;
}

static bool _PROG_GET(rs::stack_data* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  if (stack_count != 1)
  {
    return false;
  }

  SetStack(stack++, action_info.m_chara->m_prog);
  return true;
}

static bool _GET_ATTK_TYPE(rs::stack_data* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  if (stack_count != 1)
  {
    return false;
  }

  SetStack(stack++, static_cast<s32>(action_info.m_chara->m_attack_type));
  return true;
}

static bool _GET_MOVE_TYPE(rs::stack_data* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  if (stack_count != 1)
  {
    return false;
  }

  SetStack(stack++, static_cast<s32>(action_info.m_chara->m_move_type));
  return true;
}

static bool _SET_MOVE_SPEED(rs::stack_data* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  if (stack_count != 1)
  {
    return false;
  }

  f32 speed = GetStackFloat(stack++);

  if (speed < 0.0f)
  {
    speed = DEFAULT_CHARACTER_MOVE_SPEED;
  }

  action_info.m_chara->m_move_speed = speed;
  return true;
}

static bool _SET_PALLET(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHECK_EQUIP(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CAMERA_QUAKE(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHECK_PAUSE(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_STATUS_ATTR(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SE_PLAY(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SE_LOOP_PLAY(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_SHOT_TYPE(rs::stack_data* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  if (stack_count != 1)
  {
    return false;
  }

  auto chara_info = GetBattleCharaInfo();
  SetStack(stack++, static_cast<s32>(chara_info->m_equip_table.as.human->ranged.GetAttackType()));

  return true;
}

static bool _GET_MONS_ID(rs::stack_data* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  if (stack_count != 1)
  {
    return false;
  }

  s32 mons_id = -1;
  if (DngUserData->m_active_chara_no == ECharacterID::Monster)
  {
    mons_id = static_cast<s32>(GetBattleCharaInfo()->GetMonsterID());
  }

  SetStack(stack++, mons_id);
  return true;
}

static bool _GET_FRONT_VEC(rs::stack_data* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  //if (stack_count != 3)
  //{
  //  return false;
  //}

  //vec3 front_vec = action_info.m_chara->m_front_vec;

  //SetStack(stack++, front_vec.x);
  //SetStack(stack++, front_vec.y);
  //SetStack(stack++, front_vec.z);
  return true;
}

static bool _GET_PADON(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_PADDOWN(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_PADUP(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_BTN(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_PAD_HISTORY(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _RESET_PAD_HISTORY(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_ACUMU_PAD(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _RESET_ACUMU_PAD(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _RUN_MAIN_MOVE(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  switch (action_info.m_chara->m_move_type)
  {
    case EMoveType::Human:
      action_info.m_chara->HumanMoveIF();
      break;
    case EMoveType::Monster:
      action_info.m_chara->MonsterMoveIF();
      break;
    default:
      break;
  }

  return true;
}

static bool _RUN_SHROW_MOVE(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  action_info.m_chara->HumanThrowMoveIF();
  return true;
}

static bool _RUN_TAME_MOVE(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  action_info.m_chara->HumanChargeUpMoveIF();
  return true;
}

static bool _RUN_HOLD_MOVE(rs::stack_data* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  if (stack_count != 2)
  {
    return false;
  }

  action_info.m_chara->HumanGunMoveIF(GetStackString(&stack[0]), GetStackString(&stack[1]));
  return true;
}

static bool _SET_MENU_FLAG(rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(1);

  action_info.m_chara->m_menu_flag = static_cast<bool>(GetStackInt(stack++));
  return true;
}

static bool _GET_POS(rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(3);

  //vec3 pos = action_info.m_chara->GetPosition();
  //SetStack(stack++, pos.x);
  //SetStack(stack++, pos.y);
  //SetStack(stack++, pos.z);

  return true;
}

static bool _GET_ROT(rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(3);

  //vec3 rot = action_info.m_chara->GetRotation();
  //SetStack(stack++, rot.x);
  //SetStack(stack++, rot.y);
  //SetStack(stack++, rot.z);

  return true;
}

static bool _CHECK_FRONT_KEY(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHECK_BACK_KEY(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_BLOW_ANGLE(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_BLOW_MOVE(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _BLOW_START(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(3);

  action_info.m_chara->m_unk_field_F54 = GetStackFloat(stack++) * action_info.m_chara->m_unk_field_F50;
  action_info.m_chara->m_unk_field_F58 = GetStackFloat(stack++);
  action_info.m_chara->m_unk_field_F5C = GetStackInt(stack++);
  return true;
}

static bool _RUN_ROBO_MOVE(rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  sint i = GetStackInt(stack++);

  using enum EMoveType;

  switch (action_info.m_chara->m_move_type)
  {
    case RoboWalk1:
    case RoboWalk4:
      action_info.m_chara->RoboWalkMoveIF(i);
      break;
    case RoboTank2:
    case RoboTank5:
      action_info.m_chara->RoboTankMoveIF(i);
      break;
    case RoboBike:
      action_info.m_chara->RoboBikeMoveIF(i);
      break;
    case RoboAir6:
    case RoboAir7:
      action_info.m_chara->RoboAirMoveIF(1, i);
      break;
  }

  return true;
}

static bool _SET_DMG2(rs::stack_data* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);
  if (stack_count < 8 || stack_count > 9)
  {
    return false;
  }

  std::string s1 = GetStackString(stack++);
  std::string s2 = GetStackString(stack++);
  std::string s3 = GetStackString(stack++);
  f32 f0 = GetStackFloat(stack++) * 2.0f;
  f32 damage = GetStackFloat(stack++);
  std::string s4 = GetStackString(stack++);
  f32 f1 = GetStackFloat(stack++);
  f32 f2 = GetStackFloat(stack++);
  std::string s5 = "";

  if (stack_count == 9)
  {
    s5 = GetStackString(stack++);
  }

  auto result = action_info.m_chara->EntryDamage2(s1, s2, s3, f0, s4, f1, f2, s5);

  if (result == nullptr)
  {
    log_warn("CACT:DMG_ENTRY_ERR {}", s3);
    return false;
  }

  result->m_unk_field_14 = damage;
  return true;
}

static bool _SET_OBJ(rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(2);

  sint i = GetStackInt(stack++);
  std::string frame_name = GetStackString(stack++);

  if (!action_info.m_chara->EntryObject(frame_name, i))
  {
    log_warn("_SET_OBJ: Not found {}", frame_name);
    return false;
  }

  return true;
}

static bool _SET_BODY(rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(2);

  sint i = GetStackInt(stack++);
  f32 f = GetStackFloat(stack++) * 2.0f;
  return action_info.m_chara->EntryBodyCol(i, f) != nullptr;
}

static bool _SW_EFFECT(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_SND(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_ACCUME_FX(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_ACCUME_FLAG(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_MONSTER_NOWSTS(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MURDEROUS(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_TRG_DISTANCE(rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(1);

  SetStack(stack, action_info.m_chara->GetTargetDist(nowScene));
  return true;
}

static bool _SET_TRG_ANGLE(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_GUARD_FLAG(rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(1);

  action_info.m_chara->m_guard_flag = common::bits::to_bool(GetStackInt(stack++));
  return true;
}

static bool _SET_MUTEKI(rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(1);

  action_info.m_chara->m_invincible_flag = common::bits::to_bool(GetStackInt(stack++));
  return true;
}

static bool _CHECK_HAND_OBJ(rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(1);

  SetStack(stack++, action_info.m_chara->m_hand_obj);
  return true;
}

static bool _SET_ITEM_USED(rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack++, action_info.m_chara->UsedItemAction());
  return true;
}

static bool _THROW_HAND_OBJECT(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  action_info.m_chara->ThrowItemObject();
  return true;
}

static bool _CHECK_CATCH(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _RELEASE_OBJ(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_SHOT(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_SPECIAL_SHOT(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SHOT(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_OBJECT_POS(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_DIR_GUN(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_NOW_HP_RATE(rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(1);

  auto chara_info = GetBattleCharaInfo();
  // BUG: The original code does do integer division then cast to float, meaning this function would only return 0.0f or 1.0f.
  // I've changed it to float division, but that may result in different behavior than the original.
  // 002D1588
  SetStack(stack++, f32(chara_info->GetNowHp_i()) / f32(chara_info->GetMaxHp_i()));
  return true;
}

static bool _SET_BOMB(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  // Is this even used?
  // Oof, owie, my HP
  GetBattleCharaInfo()->SetHpRate(0.05f);
  return true;
}

static bool _GET_ACTION_CODE(rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(1);

  SetStack(stack++, GetBattleCharaInfo()->GetEquipTablePtr(0)->GetModelNo().value_or(-1));
  return true;
}

static bool _GET_ATTK_POINT(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(1);

  auto weapon_index = GetStackInt(stack++);
  SetStack(stack++, GetBattleCharaInfo()->m_param.m_weapons[weapon_index].m_attack);
  return true;
}

static bool _GET_RING_COLOR(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MOS(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHECK_MOS_END(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _NOW_MOS_WAIT(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_MOS_STATUS(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_XCHG_STEP(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MOS_STEP(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(1);

  action_info.m_chara->SetStep(GetStackFloat(stack++));
  return true;
}

static bool _TRG_ON_MOS(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _RESET_MOS(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  action_info.m_chara->ResetMotion();
  return true;
}

static bool _SET_DEFAULT_MOS(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_NEBA2(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _NOW_MOS_CHGWAIT(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_CREATE(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_SET_VECT1(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_SET_VECT2(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_FINISH(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_DELETE(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_SET_VALUE(MAYBE_UNUSED rs::stack_data* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static const RS_TAG_PARAM ext_func_info[]
{
  _INIT_SCRIPT,         0,
  _PROG_SET,            1,
  _PROG_GET,            2,
  _GET_ATTK_TYPE,       3,
  _GET_MOVE_TYPE,       4,
  _SET_MOVE_SPEED,      5,
  _SET_PALLET,          30,
  _CHECK_EQUIP,         31,
  _CAMERA_QUAKE,        32,
  _CHECK_PAUSE,         33,
  _GET_STATUS_ATTR,     34,
  _SE_PLAY,             35,
  _SE_LOOP_PLAY,        36,
  _GET_SHOT_TYPE,       37,
  _GET_MONS_ID,         38,
  _GET_FRONT_VEC,       39,
  _GET_PADON,           40,
  _GET_PADDOWN,         41,
  _GET_PADUP,           42,
  _GET_BTN,             43,
  _GET_PAD_HISTORY,     45,
  _RESET_PAD_HISTORY,   46,
  _GET_ACUMU_PAD,       47,
  _RESET_ACUMU_PAD,     48,
  _RUN_MAIN_MOVE,       49,
  _RUN_SHROW_MOVE,      50,
  _RUN_TAME_MOVE,       51,
  _RUN_HOLD_MOVE,       52,
  _SET_MENU_FLAG,       59,
  _GET_POS,             53,
  _GET_ROT,             61,
  _CHECK_FRONT_KEY,     54,
  _CHECK_BACK_KEY,      55,
  _SET_BLOW_ANGLE,      56,
  _SET_BLOW_MOVE,       57,
  _BLOW_START,          58,
  _RUN_ROBO_MOVE,       60,
  _SET_DMG2,            71,
  _SET_OBJ,             72,
  _SET_BODY,            73,
  _SW_EFFECT,           75,
  _SET_SND,             76,
  _SET_ACCUME_FX,       77,
  _SET_ACCUME_FLAG,     78,
  _GET_MONSTER_NOWSTS,  90,
  _SET_MURDEROUS,       91,
  _GET_TRG_DISTANCE,    92,
  _SET_TRG_ANGLE,       93,
  _SET_GUARD_FLAG,      94,
  _SET_MUTEKI,          95,
  _CHECK_HAND_OBJ,      96,
  _SET_ITEM_USED,       97,
  _THROW_HAND_OBJECT,   98,
  _CHECK_CATCH,         99,
  _RELEASE_OBJ,         100,
  _SET_SHOT,            101,
  _SET_SPECIAL_SHOT,    105,
  _SHOT,                102,
  _GET_OBJECT_POS,      103,
  _SET_DIR_GUN,         104,
  _GET_NOW_HP_RATE,     106,
  _SET_BOMB,            107,
  _GET_ACTION_CODE,     108,
  _GET_ATTK_POINT,      109,
  _GET_RING_COLOR,      110,
  _SET_MOS,             130,
  _CHECK_MOS_END,       131,
  _NOW_MOS_WAIT,        132,
  _GET_MOS_STATUS,      133,
  _SET_XCHG_STEP,       134,
  _SET_MOS_STEP,        135,
  _TRG_ON_MOS,          136,
  _RESET_MOS,           137,
  _SET_DEFAULT_MOS,     138,
  _SET_NEBA2,           140,
  _NOW_MOS_CHGWAIT,     139,
  _ESM_CREATE,          150,
  _ESM_SET_VECT1,       151,
  _ESM_SET_VECT2,       152,
  _ESM_FINISH,          153,
  _ESM_DELETE,          154,
  _ESM_SET_VALUE,       155,
  nullptr, -1
};

// 002D20D0
bool SetActionScript(CRunScript* run_script, char* rs_program, mgCMemory* stack)
{
  log_trace("{}({}, {}, {})", __func__, fmt::ptr(run_script), fmt::ptr(rs_program), fmt::ptr(stack));

  todo;
  return false;
}

// 002D2160
void SetActionExtendTable()
{
  log_trace("{}()", __func__);

  todo;
}
