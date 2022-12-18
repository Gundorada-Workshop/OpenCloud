#include "common/debug.h"
#include "common/log.h"
#include "common/macros.h"

#include "dc2/effect_script.h"
#include "dc2/monster_func.h"
#include "dc2/run_script.h"
#include "dc2/script_interpreter.h"

set_log_channel("effect_script");

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

static bool _ZERO_VECTOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
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

static bool _DIST_VECTOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DIST_VECTOR2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
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

static bool _GET_RAND(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
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

static bool _GET_DIR_VECTOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_ORIGIN(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_ORIGIN(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _AUTO_SET_OFFSET(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_WORK_VECT1(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_WORK_VECT2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_TARGET_ID(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_USER_ID(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_VALUE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_VALUE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_SET_SHOW(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_GET_SHOW(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_SET_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_GET_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_SET_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_GET_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_SET_SCALE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_GET_SCALE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_SET_MOTION(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_SET_MOT_STEP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_GET_DIR_VECTOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_GET_REF_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_ADD_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_ADD_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_ADD_SCALE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_COPY_CHARA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_SET_POS2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_SET_ROT2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_SET_SCALE2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_SET_MOTION2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_ADD_POS2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_ADD_ROT2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_ADD_SCALE2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_GET_MOT_WAIT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_SET_SHOW2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_GET_FRAME_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_SET_FRAME_SHOW(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_CHK_MOT_END(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHR_SET_LIGHT_COLOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_ASSIGN_SPRITE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_DELETE_SPRITE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_SET_TEXNAME(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_SET_ALPHAB(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_INIT_SPRITE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_SET_UV_SIZE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_SET_PUT_SIZE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_SET_DRAW_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_GET_DRAW_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_SET_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_GET_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_SET_ROTZ(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_GET_ROTZ(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_SET_SCALE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_GET_SCALE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_SET_COLOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_GET_COLOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_VAN_SET_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_VAN_SET_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_ADD_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_ADD_ROTZ(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_ADD_COLOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_WORLD_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_SET_LIFE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_SET_VELO_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_SET_ACC_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_SET_VELO_ROTZ(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_SET_ACC_ROTZ(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_SET_VELO_COL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_SET_ACC_COL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_SET_BLINKING(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_VAN_SET_COL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_SET_VELO_SCL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_SET_ACC_SCL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_VAN_SET_SCL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_SCALE_CONV(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPT_COLOR_CONV(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SCN_GET_CHR_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SCN_GET_CHR_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SCN_GET_CHR_FRM_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _INTERSECTION_POINT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _MON_SE_PLAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _MON_SE_STOP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _BTL_SE_PLAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _BTL_SE_STOP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _BSE_SE_PLAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _BSE_SE_STOP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _MON_SE_PLAY2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _MON_SE_STOP2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_LIGHT_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SCN_GET_CHR_ENTOBJ_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SCN_GET_CHR_FRM_DIR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SCN_GET_CHR_FRM_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SCN_GET_ENTRY_OBJ_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CREATE_DAMAGE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DELETE_DAMAGE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DMG_SET_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DMG_SET_FRONT_VECT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DMG_SET_DAMAGE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _COLPRIM_CREATE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _COLPRIM_SET_COORD(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _COLPRIM_DELETE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _COLPRIM_GET_HITCNT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _COLPRIM_SET_DAMAGE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _COLPRIM_GET_HIT_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _COLPRIM_GET_GIFT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _COLPRIM_GET_REVCNT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ES_CREATE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ES_SET_VECT1(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ES_SET_VECT2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ES_SET_TARGET_ID(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ES_SET_COLPRIM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ES_SET_VALUE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_EOH_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

// 0035C790
static const RS_TAG_PARAM ext_func_info[]
{
  _ZERO_VECTOR,             0,
  _NORMAL_VECTOR,           1,
  _COPY_VECTOR,             2,
  _ADD_VECTOR,              3,
  _SUB_VECTOR,              4,
  _SCALE_VECTOR,            5,
  _DIV_VECTOR,              6,
  _DIST_VECTOR,             7,
  _DIST_VECTOR2,            8,
  _SQRT,                    9,
  _ATAN2F,                  10,
  _ANGLE_CMP,               11,
  _ANGLE_LIMIT,             12,
  _GET_RAND,                13,
  _GET_REF_ROT,             14,
  _GET_DIR_VECTOR,          15,
  _SET_ORIGIN,              50,
  _GET_ORIGIN,              51,
  _AUTO_SET_OFFSET,         52,
  _GET_WORK_VECT1,          53,
  _GET_WORK_VECT2,          54,
  _GET_TARGET_ID,           55,
  _GET_USER_ID,             56,
  _GET_VALUE,               57,
  _SET_VALUE,               58,
  _CHR_SET_SHOW,            100,
  _CHR_GET_SHOW,            101,
  _CHR_SET_POS,             102,
  _CHR_GET_POS,             103,
  _CHR_SET_ROT,             104,
  _CHR_GET_ROT,             105,
  _CHR_SET_SCALE,           106,
  _CHR_GET_SCALE,           107,
  _CHR_SET_MOTION,          108,
  _CHR_SET_MOT_STEP,        109,
  _CHR_GET_DIR_VECTOR,      110,
  _CHR_GET_REF_ROT,         111,
  _CHR_ADD_POS,             112,
  _CHR_ADD_ROT,             113,
  _CHR_ADD_SCALE,           114,
  _CHR_COPY_CHARA,          125,
  _CHR_SET_POS2,            126,
  _CHR_SET_ROT2,            127,
  _CHR_SET_SCALE2,          128,
  _CHR_SET_MOTION2,         129,
  _CHR_ADD_POS2,            130,
  _CHR_ADD_ROT2,            131,
  _CHR_ADD_SCALE2,          132,
  _CHR_GET_MOT_WAIT,        133,
  _CHR_SET_SHOW2,           134,
  _CHR_GET_FRAME_POS,       135,
  _CHR_SET_FRAME_SHOW,      252,
  _CHR_CHK_MOT_END,         253,
  _CHR_SET_LIGHT_COLOR,     136,
  _SPT_ASSIGN_SPRITE,       150,
  _SPT_DELETE_SPRITE,       151,
  _SPT_SET_TEXNAME,         152,
  _SPT_SET_ALPHAB,          153,
  _SPT_INIT_SPRITE,         154,
  _SPT_SET_UV_SIZE,         157,
  _SPT_SET_PUT_SIZE,        158,
  _SPT_SET_DRAW_FLAG,       155,
  _SPT_GET_DRAW_FLAG,       156,
  _SPT_SET_POS,             159,
  _SPT_GET_POS,             160,
  _SPT_SET_ROTZ,            161,
  _SPT_GET_ROTZ,            162,
  _SPT_SET_SCALE,           163,
  _SPT_GET_SCALE,           164,
  _SPT_SET_COLOR,           165,
  _SPT_GET_COLOR,           166,
  _SPT_VAN_SET_POS,         167,
  _SPT_VAN_SET_ROT,         168,
  _SPT_ADD_POS,             169,
  _SPT_ADD_ROTZ,            170,
  _SPT_ADD_COLOR,           171,
  _SPT_WORLD_ROT,           172,
  _SPT_SET_LIFE,            173,
  _SPT_SET_VELO_POS,        174,
  _SPT_SET_ACC_POS,         175,
  _SPT_SET_VELO_ROTZ,       176,
  _SPT_SET_ACC_ROTZ,        177,
  _SPT_SET_VELO_COL,        178,
  _SPT_SET_ACC_COL,         179,
  _SPT_SET_BLINKING,        180,
  _SPT_VAN_SET_COL,         181,
  _SPT_SET_VELO_SCL,        182,
  _SPT_SET_ACC_SCL,         183,
  _SPT_VAN_SET_SCL,         184,
  _SPT_SCALE_CONV,          185,
  _SPT_COLOR_CONV,          186,
  _SCN_GET_CHR_POS,         200,
  _SCN_GET_CHR_ROT,         201,
  _SCN_GET_CHR_FRM_POS,     202,
  _INTERSECTION_POINT,      203,
  _MON_SE_PLAY,             220,
  _MON_SE_STOP,             221,
  _BTL_SE_PLAY,             222,
  _BTL_SE_STOP,             223,
  _BSE_SE_PLAY,             224,
  _BSE_SE_STOP,             225,
  _MON_SE_PLAY2,            226,
  _MON_SE_STOP2,            227,
  _SET_LIGHT_FLAG,          230,
  _SCN_GET_CHR_ENTOBJ_POS,  231,
  _SCN_GET_CHR_FRM_DIR,     232,
  _SCN_GET_CHR_FRM_ROT,     233,
  _SCN_GET_ENTRY_OBJ_POS,   234,
  _CREATE_DAMAGE,           204,
  _DELETE_DAMAGE,           205,
  _DMG_SET_POS,             206,
  _DMG_SET_FRONT_VECT,      207,
  _DMG_SET_DAMAGE,          208,
  _COLPRIM_CREATE,          210,
  _COLPRIM_SET_COORD,       211,
  _COLPRIM_DELETE,          212,
  _COLPRIM_GET_HITCNT,      213,
  _COLPRIM_SET_DAMAGE,      214,
  _COLPRIM_GET_HIT_POS,     215,
  _COLPRIM_GET_GIFT,        216,
  _COLPRIM_GET_REVCNT,      217,
  _ES_CREATE,               240,
  _ES_SET_VECT1,            241,
  _ES_SET_VECT2,            242,
  _ES_SET_TARGET_ID,        243,
  _ES_SET_COLPRIM,          244,
  _ES_SET_VALUE,            245,
  _GET_EOH_POS,             251,
  nullptr, -1
};

// 002D20D0
bool SetEffectScript(CRunScript* run_script, char* rs_program, mgCMemory* stack)
{
  log_trace("{}({}, {}, {})", __func__, fmt::ptr(run_script), fmt::ptr(rs_program), fmt::ptr(stack));

  todo;
  return false;
}

// 002D2160
void SetEffectScriptFunc()
{
  log_trace("{}()", __func__);

  todo;
}
