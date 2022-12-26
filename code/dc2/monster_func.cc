#include "common/bits.h"
#include "common/constants.h"
#include "common/debug.h"
#include "common/log.h"
#include "common/macros.h"

#include "dc2/camera.h"
#include "dc2/monster.h"
#include "dc2/monster_func.h"
#include "dc2/run_script.h"
#include "dc2/scene.h"
#include "dc2/script_interpreter.h"

set_log_channel("monster_func");

#define VERIFY_STACK_COUNT(n) \
  if (stack_count != n) UNLIKELY \
  { \
    return false; \
  }

// 0037735C
CScene* nowScene{ nullptr };
// 00377360
CActiveMonster* nowMonster{ nullptr };

MAYBE_UNUSED static sint GetStackInt(RS_STACKDATA* stack)
{
  log_trace("{}()", __func__, fmt::ptr(stack));

  if (stack->m_data_type == EStackDataType::Float)
  {
    return static_cast<sint>(stack->m_data.f);
  }
  else
  {
    return stack->m_data.i;
  }
}

static f32 GetStackFloat(RS_STACKDATA* stack)
{
  log_trace("{}()", __func__, fmt::ptr(stack));

  if (stack->m_data_type == EStackDataType::Int)
  {
    return static_cast<f32>(stack->m_data.i);
  }
  else
  {
    return stack->m_data.f;
  }
}

MAYBE_UNUSED static vec3 GetStackVector(RS_STACKDATA* stack)
{
  log_trace("{}()", __func__, fmt::ptr(stack));

  return {
    GetStackFloat(&stack[0]),
    GetStackFloat(&stack[1]),
    GetStackFloat(&stack[2]),
  };
}

MAYBE_UNUSED static const char* GetStackString(RS_STACKDATA* stack)
{
  log_trace("{}()", __func__, fmt::ptr(stack));

  return stack->m_data.s;
}

MAYBE_UNUSED static void SetStack(RS_STACKDATA* stack, sint value)
{
  log_trace("{}()", __func__, fmt::ptr(stack));

  if (stack->m_data_type != EStackDataType::Pointer)
  {
    return;
  }

  stack->m_data.p->m_data.i = value;
}

MAYBE_UNUSED static void SetStack(RS_STACKDATA* stack, f32 value)
{
  log_trace("{}()", __func__, fmt::ptr(stack));

  if (stack->m_data_type != EStackDataType::Pointer)
  {
    return;
  }

  stack->m_data.p->m_data.f = value;
}

static bool _NORMAL_VECTOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _COPY_VECTOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ADD_VECTOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SUB_VECTOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SCALE_VECTOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DIV_VECTOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ANGLE_CMP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ANGLE_LIMIT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SQRT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ATAN2F(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ND_TEST(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_DIST_VECTOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_DIST_VECTOR2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CALC_IP_CIRCLE_LINE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_ANGLE_INNER(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _MY_SE_PLAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _MY_SE_STOP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _MONS_SE_PLAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _MONS_SE_STOP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _MONS_SE_LOOP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_CAMERA_NEXT_REF(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(3);

  auto camera = static_cast<CCameraControl*>(nowScene->GetCamera(nowScene->m_active_cmrid));
  if (camera == nullptr)
  {
    return false;
  }

  camera->FollowOff();
  camera->ControlOff();
  camera->SetNextRef(GetStackFloat(&stack[0]), GetStackFloat(&stack[1]), GetStackFloat(&stack[2]));

  return true;
}

static bool _SET_CAMERA_FOLLOW(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(1);

  auto camera = static_cast<CCameraControl*>(nowScene->GetCamera(nowScene->m_active_cmrid));
  if (camera == nullptr)
  {
    return false;
  }

  bool follow_on = common::bits::to_bool(GetStackInt(stack++));
  if (follow_on)
  {
    camera->FollowOn();
    camera->ControlOn();
  }
  else
  {
    camera->FollowOff();
    camera->ControlOff();
  }

  return true;
}

static bool _SET_CAMERA_NEXT_POS(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(3);

  auto camera = static_cast<CCameraControl*>(nowScene->GetCamera(nowScene->m_active_cmrid));
  if (camera == nullptr)
  {
    return false;
  }

  camera->FollowOff();
  camera->ControlOff();
  camera->SetNextPos(GetStackFloat(&stack[0]), GetStackFloat(&stack[1]), GetStackFloat(&stack[2]));

  return true;
}

static bool _SET_CAMERA_MODE(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(1);

  nowScene->m_battle_area_scene.m_camera_mode = GetStackInt(stack++);
  return true;
}

static bool _SET_CAMERA_SPEED(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto camera = static_cast<CCameraControl*>(nowScene->GetCamera(nowScene->m_active_cmrid));
  if (camera == nullptr)
  {
    return false;
  }

  camera->SetSpeed(GetStackFloat(stack++));
  return true;
}

static bool _CAMERA_QUAKE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(2);

  f32 f = GetStackFloat(stack++);
  nowScene->m_battle_area_scene.m_unk_field_70 = f;
  sint i = GetStackInt(stack++);
  nowScene->m_battle_area_scene.m_unk_field_74 = f / static_cast<f32>(i);
  nowScene->m_battle_area_scene.m_unk_field_78 = i;
  return true;
}

static bool _SET_CAMERA_CTRL_PARAM1(RS_STACKDATA* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);
  if (stack_count < 0 || stack_count > 4)
  {
    return false;
  }

  auto camera = static_cast<CCameraControl*>(nowScene->GetCamera(nowScene->m_active_cmrid));
  auto& param = camera->GetActiveParam();

  std::optional<f32> arg0{};
  std::optional<f32> arg1{};
  std::optional<f32> arg2{};
  std::optional<f32> arg3{};

  if (stack_count >= 1)
  {
    arg0 = GetStackFloat(stack++);
  }

  if (arg0.has_value() && arg0.value() != -99999.9f)
  {
    param.m_unk_field_0 = arg0.value();
  }

  if (stack_count >= 2)
  {
    arg1 = GetStackFloat(stack++);
  }

  if (arg1.has_value() && arg1.value() != -99999.9f)
  {
    param.m_unk_field_4 = arg1.value();
  }

  if (stack_count >= 3)
  {
    arg2 = GetStackFloat(stack++);
  }

  if (arg2.has_value() && arg2.value() != -99999.9f)
  {
    param.m_unk_field_8 = arg2.value();
  }

  if (stack_count >= 4)
  {
    arg3 = GetStackFloat(stack++);
  }

  if (arg3.has_value() && arg3.value() != -99999.9f)
  {
    param.m_unk_field_C = arg3.value();
  }

  return true;
}

static bool _SET_CAMERA_CTRL_PARAM2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  if (stack_count < 0 || stack_count > 6)
  {
    return false;
  }

  auto camera = static_cast<CCameraControl*>(nowScene->GetCamera(nowScene->m_active_cmrid));
  auto& param = camera->GetActiveParam();

  std::optional<f32> arg0{};
  std::optional<f32> arg1{};
  std::optional<f32> arg2{};
  std::optional<f32> arg3{};
  std::optional<f32> arg4{};
  std::optional<f32> arg5{};

  if (stack_count >= 1)
  {
    arg0 = GetStackFloat(stack++);
  }

  if (arg0.has_value() && arg0.value() != -99999.9f)
  {
    param.m_unk_field_10 = arg0.value();
  }

  if (stack_count >= 2)
  {
    arg1 = GetStackFloat(stack++);
  }

  if (arg1.has_value() && arg1.value() != -99999.9f)
  {
    param.m_unk_field_14 = arg1.value();
  }

  if (stack_count >= 3)
  {
    arg2 = GetStackFloat(stack++);
  }

  if (arg2.has_value() && arg2.value() != -99999.9f)
  {
    param.m_unk_field_18 = arg2.value();
  }

  if (stack_count >= 4)
  {
    arg3 = GetStackFloat(stack++);
  }

  if (arg3.has_value() && arg3.value() != -99999.9f)
  {
    param.m_unk_field_1C = arg3.value();
  }

  if (stack_count >= 5)
  {
    arg4 = GetStackFloat(stack++);
  }

  if (arg4.has_value() && arg4.value() != -99999.9f)
  {
    param.m_unk_field_20 = arg4.value();
  }

  if (stack_count >= 6)
  {
    arg5 = GetStackFloat(stack++);
  }

  if (arg5.has_value() && arg5.value() != -99999.9f)
  {
    param.m_unk_field_24 = arg5.value();
  }

  return true;
}

static bool _RESET_CAMERA_CTRL_PARAM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto camera = static_cast<CCameraControl*>(nowScene->GetCamera(nowScene->m_active_cmrid));
  auto& param = camera->GetActiveParam();
  param.m_unk_field_0 = 100.0f;
  param.m_unk_field_4 = 160.0f;
  param.m_unk_field_8 = 18.0f;
  param.m_unk_field_C = 10.0f;
  param.m_unk_field_14 = 40.0f;
  param.m_unk_field_18 = -15.0f;
  param.m_unk_field_1C = 20.0f;
  param.m_unk_field_20 = -15.0f;
  param.m_unk_field_10 = -15.0f;
  param.m_unk_field_24 = 25.0f;

  return true;
}

static bool _GET_RND(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(2);

  // NOTE: Metrowerks does multiplication, then division, which likely results in a less precise result.
  // MSVC will likely reverse the operation for precision, but this likely won't cause any issues.
  f32 max = GetStackInt(stack++);
  SetStack(stack++, static_cast<s32>(static_cast<f32>(rand()) * max / static_cast<f32>(common::constants::s32_max)));
  return true;
}

static bool _GET_RNDF(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(2);

  // NOTE: Metrowerks does multiplication, then division, which likely results in a less precise result.
  // MSVC will likely reverse the operation for precision, but this likely won't cause any issues.
  f32 max = GetStackFloat(stack++);
  SetStack(stack++, static_cast<f32>(rand()) * max / static_cast<f32>(common::constants::s32_max));
  return true;
}

static bool _V_PUSH(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _V_POP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_MONSTER_NUM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_MONSTER_INDEX(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_MONSTER_ID(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_USERID(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_USER_MONS_ID(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _RESET_TIMER(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_TIMER(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CREATE_MONSTER(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _RUN_EVENT_SCRIPT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_FRAME_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_OBJ_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_MAPOBJ_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_PAUSE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHECK_PAUSE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_BIT_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_BIT_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_ATT_TYPE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_USER_ATTR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _TRANS_RESERV_IMG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_STS_ATTR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _V_PUSH2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _V_POP2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_LOCKON_MODE(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(1);

  nowScene->m_battle_area_scene.m_lockon_mode = GetStackInt(stack++);
  return true;
}

static bool _SET_MOTION_BLUR(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(1);

  nowScene->m_fade_in_out.m_motion_blur = common::bits::to_bool(GetStackInt(stack++));
  return true;
}

static bool _GET_EVENT_INFO(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _MONS_VOL_CTRL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_DIST(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SEARCH_AREA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SEARCH_AREA2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_PLACE_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_PLACE_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_INDEX_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_NEXT_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_NEXT_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHK_MOVE_END(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _RESET_MOVE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_TARGET_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_TARGET_DIST(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_TARGET_ANGLE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_TARGET_REF_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_REF_DIR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_REFANGLE_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_TARGET_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_REF_ANGLE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_HIGH(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_NEAR_MONS_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_TARGET_OLD_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_TARGET_SPEED(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CALC_MOVE_NEXT_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_POSREF_ANGLE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_ACTIVE_MONS_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_ACTIVE_MONS_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_ACTIVE_MONS_DIST(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_ACTIVE_MONS_ANGLE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_REF_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_REF_ROT2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _FLYING_SEARCH_AREA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_HIGH2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_RANGE_MONS_ID(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_ENTRY_OBJ_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_OBJ(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_BODY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_DMG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_DMG2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LINK_MAP_TO_OBJECT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LINK_OBJECT_TO_PIECE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LOAD_EFFECT_SCRIPT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_SCOOP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LOAD_RESERV_IMG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_PRIORITY_LIMMIT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MODEL_LIGHT_SWITCH(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MODEL_LIGHT_COLOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_ALPHA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_SCALE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_INDEX_ALPHA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_PALLET_ANIM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _RESET_PALLET_ANIM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_ATTRIB(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_STATUS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_INT_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_ACT_STATUS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MUTEKI(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_GRAVITY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return false;
}

static bool _SET_COLLISION(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return false;
}

static bool _GET_GEKIRIN(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_PRIORITY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_CLIP_DIST(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_PIYORI_MARK(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHECK_PIYORI(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_SCALE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_MONS_WIDTH(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _BLOW_START(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_DEAD_START(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_DEAD_OFF(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_SHROW_END(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_BASE_ATTACK(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);
  VERIFY_STACK_COUNT(1);
  
  SetStack(stack++, nowMonster->m_base_attack);
  return true;
}

static bool _SET_DEF_RATE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MONSTER_LIFE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_MONSTER_LIFE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_NO_DAMAGE_CNT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_ACTIVE_MONS_LIFEI(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_ACTIVE_MONS_LIFEF(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_ACTIVE_MONS_LIFEI(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_ACTIVE_MONS_LIFEF(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_ACTIVE_MONS_MAX_LIFE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_DAMAGE_SCORE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_MONS_GRADE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_ESCAPE_RATE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_GUARD_RATE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_EXT_PARAM_RATE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_BOSS_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_INDEXOBJ_SIZE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_INDEXOBJ_SIZE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _RESET_MOTION(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  nowMonster->ResetMotion();
  return true;
}

static bool _SET_MOS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHECK_MOS_END(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _NOW_MOS_WAIT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_MOS_STATUS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_CREATE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_FINISH(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_DELETE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_SET_VECT1(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_GET_VECT1(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_SET_VECT2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_GET_VECT2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_SET_TARGET_ID(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_GET_TARGET_ID(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_SET_USER_ID(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_GET_USER_ID(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_SET_VALUE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SW_EFFECT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_GET_NOTUESD_TEXB(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_ADD_TEXB(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SHOT_ROCKET_LAUNCHER(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_ALL_CLEAR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MAPOBJ_SHOW(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static const RS_TAG_PARAM ext_func_info[]
{
  _NORMAL_VECTOR,             0,
  _COPY_VECTOR,               1,
  _ADD_VECTOR,                2,
  _SUB_VECTOR,                3,
  _SCALE_VECTOR,              4,
  _DIV_VECTOR,                5,
  _ANGLE_CMP,                 6,
  _ANGLE_LIMIT,               7,
  _SQRT,                      8,
  _ATAN2F,                    9,
  _ND_TEST,                   10,
  _GET_DIST_VECTOR,           11,
  _GET_DIST_VECTOR2,          12,
  _CALC_IP_CIRCLE_LINE,       13,
  _GET_ANGLE_INNER,           14,
  _MY_SE_PLAY,                21,
  _MY_SE_STOP,                22,
  _MONS_SE_PLAY,              23,
  _MONS_SE_STOP,              24,
  _MONS_SE_LOOP,              65,
  _SET_CAMERA_NEXT_REF,       25,
  _SET_CAMERA_FOLLOW,         26,
  _SET_CAMERA_NEXT_POS,       27,
  _SET_CAMERA_MODE,           28,
  _SET_CAMERA_SPEED,          29,
  _CAMERA_QUAKE,              30,
  _SET_CAMERA_CTRL_PARAM1,    31,
  _SET_CAMERA_CTRL_PARAM2,    32,
  _RESET_CAMERA_CTRL_PARAM,   33,
  _GET_RND,                   35,
  _GET_RNDF,                  36,
  _V_PUSH,                    37,
  _V_POP,                     38,
  _GET_MONSTER_NUM,           39,
  _GET_MONSTER_INDEX,         40,
  _GET_MONSTER_ID,            41,
  _GET_USERID,                42,
  _GET_USER_MONS_ID,          43,
  _RESET_TIMER,               44,
  _GET_TIMER,                 45,
  _CREATE_MONSTER,            46,
  _RUN_EVENT_SCRIPT,          47,
  _GET_FRAME_POS,             48,
  _GET_OBJ_POS,               49,
  _GET_MAPOBJ_POS,            50,
  _SET_PAUSE,                 51,
  _CHECK_PAUSE,               52,
  _GET_BIT_FLAG,              53,
  _SET_BIT_FLAG,              54,
  _GET_ATT_TYPE,              55,
  _GET_USER_ATTR,             56,
  _TRANS_RESERV_IMG,          57,
  _GET_STS_ATTR,              58,
  _V_PUSH2,                   59,
  _V_POP2,                    60,
  _SET_LOCKON_MODE,           61,
  _SET_MOTION_BLUR,           62,
  _GET_EVENT_INFO,            64,
  _MONS_VOL_CTRL,             66,
  _GET_DIST,                  70,
  _SEARCH_AREA,               71,
  _SEARCH_AREA2,              108,
  _GET_PLACE_POS,             72,
  _SET_PLACE_POS,             73,
  _GET_INDEX_POS,             74,
  _GET_POS,                   75,
  _SET_POS,                   76,
  _GET_ROT,                   77,
  _SET_ROT,                   78,
  _SET_NEXT_ROT,              79,
  _SET_NEXT_POS,              80,
  _CHK_MOVE_END,              81,
  _RESET_MOVE,                82,
  _GET_TARGET_POS,            83,
  _GET_TARGET_DIST,           84,
  _GET_TARGET_ANGLE,          85,
  _GET_TARGET_REF_POS,        86,
  _GET_REF_DIR,               87,
  _GET_REFANGLE_POS,          88,
  _GET_TARGET_ROT,            89,
  _GET_REF_ANGLE,             90,
  _GET_HIGH,                  91,
  _GET_NEAR_MONS_POS,         92,
  _GET_TARGET_OLD_POS,        93,
  _GET_TARGET_SPEED,          94,
  _CALC_MOVE_NEXT_POS,        95,
  _GET_POSREF_ANGLE,          96,
  _GET_ACTIVE_MONS_POS,       97,
  _GET_ACTIVE_MONS_ROT,       98,
  _GET_ACTIVE_MONS_DIST,      99,
  _GET_ACTIVE_MONS_ANGLE,     100,
  _GET_REF_ROT,               101,
  _GET_REF_ROT2,              102,
  _FLYING_SEARCH_AREA,        103,
  _GET_HIGH2,                 104,
  _GET_RANGE_MONS_ID,         105,
  _GET_ENTRY_OBJ_POS,         106,
  _SET_OBJ,                   110,
  _SET_BODY,                  111,
  _SET_DMG,                   112,
  _SET_DMG2,                  113,
  _LINK_MAP_TO_OBJECT,        114,
  _LINK_OBJECT_TO_PIECE,      115,
  _LOAD_EFFECT_SCRIPT,        116,
  _SET_SCOOP,                 117,
  _LOAD_RESERV_IMG,           118,
  _SET_PRIORITY_LIMMIT,       119,
  _SET_MODEL_LIGHT_SWITCH,    120,
  _SET_MODEL_LIGHT_COLOR,     121,
  _SET_ALPHA,                 122,
  _SET_SCALE,                 123,
  _SET_INDEX_ALPHA,           124,
  _SET_PALLET_ANIM,           125,
  _RESET_PALLET_ANIM,         126,
  _SET_ATTRIB,                127,
  _SET_STATUS,                128,
  _SET_INT_FLAG,              129,
  _SET_ACT_STATUS,            130,
  _SET_MUTEKI,                131,
  _SET_GRAVITY,               132,
  _SET_COLLISION,             133,
  _GET_GEKIRIN,               134,
  _GET_PRIORITY,              135,
  _SET_CLIP_DIST,             136,
  _SET_PIYORI_MARK,           137,
  _CHECK_PIYORI,              138,
  _GET_SCALE,                 139,
  _GET_MONS_WIDTH,            140,
  _BLOW_START,                150,
  _SET_DEAD_START,            151,
  _SET_DEAD_OFF,              152,
  _SET_SHROW_END,             153,
  _GET_BASE_ATTACK,           160,
  _SET_DEF_RATE,              161,
  _SET_MONSTER_LIFE,          162,
  _GET_MONSTER_LIFE,          163,
  _GET_NO_DAMAGE_CNT,         164,
  _GET_ACTIVE_MONS_LIFEI,     165,
  _GET_ACTIVE_MONS_LIFEF,     166,
  _SET_ACTIVE_MONS_LIFEI,     167,
  _SET_ACTIVE_MONS_LIFEF,     168,
  _GET_ACTIVE_MONS_MAX_LIFE,  169,
  _SET_DAMAGE_SCORE,          170,
  _GET_MONS_GRADE,            171,
  _SET_ESCAPE_RATE,           173,
  _SET_GUARD_RATE,            172,
  _SET_EXT_PARAM_RATE,        174,
  _GET_BOSS_FLAG,             175,
  _SET_INDEXOBJ_SIZE,         176,
  _GET_INDEXOBJ_SIZE,         177,
  _RESET_MOTION,              180,
  _SET_MOS,                   182,
  _CHECK_MOS_END,             183,
  _NOW_MOS_WAIT,              184,
  _GET_MOS_STATUS,            185,
  _ESM_CREATE,                191,
  _ESM_FINISH,                192,
  _ESM_DELETE,                193,
  _ESM_SET_VECT1,             194,
  _ESM_GET_VECT1,             195,
  _ESM_SET_VECT2,             196,
  _ESM_GET_VECT2,             197,
  _ESM_SET_TARGET_ID,         198,
  _ESM_GET_TARGET_ID,         199,
  _ESM_SET_USER_ID,           200,
  _ESM_GET_USER_ID,           201,
  _ESM_SET_VALUE,             202,
  _SW_EFFECT,                 203,
  _ESM_GET_NOTUESD_TEXB,      204,
  _ESM_ADD_TEXB,              205,
  _SHOT_ROCKET_LAUNCHER,      206,
  _ESM_ALL_CLEAR,             207,
  _SET_MAPOBJ_SHOW,           63,
  nullptr, -1
};

// 001E7BB0
bool SetMonsterScript(MAYBE_UNUSED CRunScript* run_script, MAYBE_UNUSED char* rs_program, MAYBE_UNUSED mgCMemory* stack)
{
  log_trace("{}({}, {}, {})", __func__, fmt::ptr(run_script), fmt::ptr(rs_program), fmt::ptr(stack));

  todo;
  return false;
}

// 001E7C40
void SetMonsterExtendTable()
{
  log_trace("{}()", __func__);

  todo;
}