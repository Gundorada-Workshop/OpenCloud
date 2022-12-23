#include <cmath>

#include "common/bits.h"
#include "common/log.h"
#include "common/math.h"
#include "common/macros.h"
#include "common/constants.h"
#include "common/types.h"

#include "dc2/camera.h"
#include "dc2/dng_main.h"
#include "dc2/dng_event.h"
#include "dc2/dngmenu.h"
#include "dc2/effect.h"
#include "dc2/event.h"
#include "dc2/event_edit.h"
#include "dc2/event_func.h"
#include "dc2/gamedata.h"
#include "dc2/inventmn.h"
#include "dc2/mainloop.h"
#include "dc2/mapjump.h"
#include "dc2/menumain.h"
#include "dc2/nowload.h"
#include "dc2/rain.h"
#include "dc2/run_script.h"
#include "dc2/scene.h"
#include "dc2/subgame.h"
#include "dc2/mg/mg_lib.h"

#include "host/host_interface_dwm.h"

set_log_channel("event_func");

// 00377CD4
static CMarker EventMarker{};
// 00377CD8
static std::unique_ptr<CSwordAfterImage> SwordEffect{ nullptr };
// 00377CE4
static bool SetWorldCoordFlg{};
// 01ECD5F0
static MENU_INIT_ARG MenuArg{};
// 01ECE880
static CEohMother EventObjHandleMother{};
// 01ECEA80
static CEventSpriteMother esMother{};
// 01ECEEC0
static std::array<u32, 0x40> EventLocalFlag{};
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

// 0025F860
static sint GetStackInt(RS_STACKDATA* stack)
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

// 0025F8A0
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

// 0025F8D0
static vec3 GetStackVector(RS_STACKDATA* stack)
{
  log_trace("{}()", __func__, fmt::ptr(stack));

  return {
    GetStackFloat(&stack[0]),
    GetStackFloat(&stack[1]),
    GetStackFloat(&stack[2]),
  };
}

// 0025F920
static const char* GetStackString(RS_STACKDATA* stack)
{
  log_trace("{}()", __func__, fmt::ptr(stack));

  return stack->m_data.s;
}

// 0025F930
static void SetStack(RS_STACKDATA* stack, sint value)
{
  log_trace("{}()", __func__, fmt::ptr(stack));

  if (stack->m_data_type != EStackDataType::Pointer)
  {
    return;
  }

  stack->m_data.p->m_data.i = value;
}

// 0025F950
static void SetStack(RS_STACKDATA* stack, f32 value)
{
  log_trace("{}()", __func__, fmt::ptr(stack));

  if (stack->m_data_type != EStackDataType::Pointer)
  {
    return;
  }

  stack->m_data.p->m_data.f = value;
}

// 00260F70
void InitWorldCoord()
{
  log_trace("{}()", __func__);
  
  EdEventInfo.m_unk_field_0 = { 0, 0, 0, 0 };
  EdEventInfo.m_unk_field_10 = { 0, 0, 0, 0 };
  SetWorldCoordFlg = false;
}

// 01ECEFC0
static std::array<sint, 64> EventLocalCnt{ 0 };

// 002610D0
sint GetLocalCnt(ssize index) // Not static as it's used by ClsMes apparently
{
  if (index < 0 || index >= EventLocalCnt.size())
  {
    return -1;
  }

  return EventLocalCnt[index];
}

// 00261110
static bool SetLocalCnt(ssize index, sint value)
{
  if (index < 0 || index >= EventLocalCnt.size())
  {
    return false;
  }

  EventLocalCnt[index] = value;
  return true;
}

// 00261150
static sint GetLocalCnt2(sint count)
{
  // Retrieves the index of a count?
  for (usize i = 0; i < EventLocalCnt.size(); ++i)
  {
    if (EventLocalCnt[i] == count)
    {
      return i;
    }
  }

  return -1;
}

// 002611A0
static void InitLocalCnt()
{
  log_trace("{}()", __func__);

  EventLocalCnt.fill(0);
}

// 002614F0
void EdEventInit()
{
  log_trace("{}()", __func__);

  todo;
}

// 002620A0
bool EdEventFinish()
{
  log_trace("{}()", __func__);

  todo;
  return false;
}

static bool _GET_PADON(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_PADDOWN(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_PADUP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_APAD(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GOTO_INTERIOR(RS_STACKDATA* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  EdEventInfo.m_unk_field_64 = GetStackInt(stack++);
  EdEventInfo.m_unk_field_68 = GetStackString(stack++);
  EdEventInfo.m_unk_field_88 = (stack_count >= 3 ? GetStackInt(stack++): 100);
  EdEventInfo.m_unk_field_1CC = (stack_count >= 4 ? GetStackInt(stack++) : 0);
  EdEventInfo.m_unk_field_CC = 4; // FIXME: MAGIC

  return true;
}

static bool _INITIALIZE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  EdEventInit();

  auto camera = static_cast<mgCCameraFollow*>(GetActiveCamera());

  if (camera == nullptr)
  {
    return false;
  }

  camera->FollowOff();
  return true;
}

static bool _GOTO_OUTSIDE(RS_STACKDATA* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  EdEventInfo.m_unk_field_64 = GetStackInt(stack++);
  EdEventInfo.m_unk_field_68 = GetStackString(stack++);
  EdEventInfo.m_unk_field_88 = (stack_count >= 3 ? GetStackInt(stack++) : 100);
  EdEventInfo.m_unk_field_CC = 7; // FIXME: MAGIC

  return true;
}

static bool _LOAD_CHARA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHARA_ACTIVE(RS_STACKDATA* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  switch (stack_count)
  {
    case 2:
    {
      bool active = GetStackInt(stack++);
      auto chara_id = GetStackInt(stack++);

      if (active)
      {
        EventScene->SetActive(ESceneDataType::Character, chara_id);
      }
      else
      {
        EventScene->ResetActive(ESceneDataType::Character, chara_id);
      }

      return true;
    }
    case 1:
    {
      auto chara_id = GetStackInt(stack++);
      EventScene->SetActive(ESceneDataType::Character, chara_id);

      return true;
    }
    default:
      return false;
  }
}

static bool _CLEAR_STACK(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  EventScene->ClearStack(GetStackInt(stack++));
  return true;
}

static bool _ASSIGN_STACK(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  EventScene->AssignStack(GetStackInt(stack++));
  return true;
}

static bool _SET_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_CNT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_CNT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_CURRENT_DIR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DELETE_CHARA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LOAD_MOTION(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _MAP_JUMP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_RAIN(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  bool active = GetStackInt(stack++);

  if (active)
  {
    EventRain.Start();
  }
  else
  {
    EventRain.Stop();
  }

  return true;
}

static bool _DEL_EXT_MOTION(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto chara = EventScene->GetCharacter(GetStackInt(stack++));

  if (chara == nullptr)
  {
    return false;
  }

  chara->DeleteExtMotion();
  return true;
}

static bool _SET_MARKER(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _SET_WORLD_COORD(RS_STACKDATA* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  switch (stack_count)
  {
    case 4:
    {
      EdEventInfo.m_unk_field_0 = {
        GetStackFloat(&stack[0]),
        GetStackFloat(&stack[1]),
        GetStackFloat(&stack[2]),
        1.0f
      };
      EdEventInfo.m_unk_field_10 = {
        0.0f,
        GetStackFloat(&stack[3]),
        0.0f,
        0.0f
      };

      SetWorldCoordFlg = true;
      return true;
    }
    case 1:
      InitWorldCoord();
      return true;
    default:
      return false;
  }
}

static bool _FINISH(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return EdEventFinish();
}

static bool _GET_DUN_WORLD_COORD(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LOAD_IMG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DEL_IMG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_DNG_MAP(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  // Dummy?
  GetStackInt(stack++);
  GetStackInt(stack++);

  return true;
}

static bool _LOAD_ITEM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GOTO_USE_ITEM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_LOCAL_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_LOCAL_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GOTO_SELECT_PARTY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_LOADBG_FILE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHECK_LOADBG_FILE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_TB_ITEMNO(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return false;
}

static bool _SET_TB_STATUS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_TB_ANGLE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ADD_ITEM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_ITEM_TYPE(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  ECommonItemDataType item_type = static_cast<ECommonItemDataType>(GetStackInt(stack++));

  using enum ECommonItemDataType;

  if (item_type == Invalid)
  {
    return false;
  }

  if (item_type != Ranged_Monica && item_type != Melee_Monica && item_type != Ranged_Max && item_type != Melee_Max)
  {
    item_type = Invalid;
  }

  SetStack(stack, static_cast<s32>(item_type));
  return true;
}

static bool _GET_ITEM_SPACE(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();

  if (save_data == nullptr)
  {
    return false;
  }

  SetStack(stack, save_data->m_user_data_manager.SearchSpaceUsedData());
  return true;
}

static bool _GET_ADJUST_POLYGON_SCALE(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto chara_id = GetStackInt(stack++);
  f32 scale = GetStackFloat(stack++);

  auto chara = GetCharacter(chara_id);

  if (chara == nullptr)
  {
    return false;
  }

  auto frame = chara->m_frame;

  if (frame == nullptr)
  {
    return false;
  }

  SetStack(stack, MenuAdjustPolygonScale(frame, scale));
  return true;
}

// 00264760
static bool GetConfigCaptionOff()
{
  auto save_data = GetSaveData();
  if (save_data == nullptr)
  {
    return false;
  }

  return save_data->m_sv_config_option.m_display_captions;
}

static bool _LOAD_MOVIE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _INIT_LOCAL_CNT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  InitLocalCnt();
  return true;
}

static bool _SET_CROSSFADE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_TIME(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  EventScene->SetTime(GetStackFloat(stack++));
  return true;
}

static bool _SET_ACTIVE_LIGHT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_PAKU_ANIM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _RESET_PAKU_ANIM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _TRG_PAKU_ANIM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _RESET_CAMERA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_ACTIVE_CHR_NO(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();

  if (save_data == nullptr)
  {
    return false;
  }

  SetStack(stack, static_cast<s32>(save_data->m_user_data_manager.m_active_chara_no));
  return true;
}

static bool _SET_ACTIVE_CHR_NO(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();

  if (save_data == nullptr)
  {
    return false;
  }

  save_data->m_user_data_manager.SetActiveChrNo(static_cast<ECharacterID>(GetStackInt(stack++)));
  return true;
}

static bool _DNG_SET_FLOOR_ID(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();

  if (save_data == nullptr)
  {
    return false;
  }

  save_data->m_save_data_dungeon.SetFloorID(GetStackInt(stack++));
  return true;
}

static bool _DNG_GET_FLOOR_ID(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();

  if (save_data == nullptr)
  {
    return false;
  }

  auto floor_index = static_cast<s32>(save_data->m_save_data_dungeon.m_now_dungeon_id);
  SetStack(stack, save_data->m_save_data_dungeon.m_now_floors[floor_index]);
  return true;
}

static bool _SET_PAKU_MOTION(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _RESET_PAKU_MOTION(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _TRG_PAKU_MOTION(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_BG_COLOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GOTO_DNG_MAP(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  // FIXME: MAGIC values
  MenuArg.m_unk_field_28 = 3;
  MenuArg.m_unk_field_58 = GetStackInt(stack++);
  EdEventInfo.m_unk_field_D0 = 3;
  return true;
}

static bool _GOTO_DNG(RS_STACKDATA* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  if (!EdEventFinish())
  {
    return false;
  }

  INIT_LOOP_ARG init_arg{};
  init_arg.m_unk_field_0 = GetStackInt(stack++);
  init_arg.m_unk_field_44 = (stack_count >= 2 ? GetStackInt(stack++) : -1);
  init_arg.m_unk_field_48 = (stack_count >= 3 ? GetStackInt(stack++) : -1);

  NextLoop(ELoopID::Dungeon, init_arg);
  EdEventInfo.m_unk_field_CC = 3; // FIXME: MAGIC

  return true;
}

static bool _GOTO_EDIT(RS_STACKDATA* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  if (!EdEventFinish())
  {
    return false;
  }

  INIT_LOOP_ARG init_arg{};
  init_arg.m_unk_field_0 = GetStackInt(stack++);
  init_arg.m_unk_field_48 = (stack_count >= 2 ? GetStackInt(stack++) : -1);

  NextLoop(ELoopID::Edit, init_arg);
  EdEventInfo.m_unk_field_CC = 3; // FIXME: MAGIC

  return true;
}

static bool _GET_MENU_PARAM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LOAD_CHARA_NPC(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _AUTO_SET_TREASURE_BOX(RS_STACKDATA* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  // NOTE: game checks < 2, but that's probably just a bug
  if (stack_count < 5)
  {
    AutoSetTreasureBox();
  }
  else
  {
    AutoSetTreasureBox(
      GetStackInt(&stack[0]),
      vec3{
        GetStackFloat(&stack[1]),
        GetStackFloat(&stack[2]),
        GetStackFloat(&stack[3])
      },
      GetStackFloat(&stack[4])
    );
  }

  return true;
}

static bool _AUTO_SET_MONSTER(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LOAD_DUNGEON_MAP_FILE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LOAD_MONSTER_FILE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_NPC_STATUS(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  s32 chara_index = GetStackInt(stack++);

  if (chara_index < 0 || chara_index >= s32(EPartyCharacterID::COUNT))
  {
    return false;
  }

  auto save_data = GetSaveData();

  if (save_data == nullptr)
  {
    return false;
  }

  SetStack(stack, s32(save_data->m_user_data_manager.GetPartyCharaStatus(EPartyCharacterID(chara_index))));
  return true;
}

static bool _SET_NPC_STATUS(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  s32 chara_index = GetStackInt(stack++);
  s32 status = GetStackInt(stack++);

  if (chara_index < 0 || chara_index >= s32(EPartyCharacterID::COUNT))
  {
    return false;
  }

  auto save_data = GetSaveData();

  if (save_data == nullptr)
  {
    return false;
  }

  save_data->m_user_data_manager.SetPartyCharaStatus(EPartyCharacterID(chara_index), EPartyCharacterStatus(status));
  return true;
}

static bool _GET_NOW_PARTY_CHARA(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  auto save_data = GetSaveData();

  if (save_data == nullptr)
  {
    return false;
  }

  SetStack(stack, s32(save_data->m_user_data_manager.NowPartyCharaID()));
  return true;
}

static bool _SET_LOCAL_CNT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  // (index, value)
  SetLocalCnt(GetStackInt(&stack[0]), GetStackInt(&stack[1]));
  return true;
}

static bool _GET_LOCAL_CNT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  sint cnt = GetLocalCnt(GetStackInt(stack++));
  if (cnt < 0)
  {
    return false;
  }

  SetStack(stack++, cnt);
  return true;
}

static bool _GET_LOCAL_CNT2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  sint count = GetStackInt(stack++);
  SetStack(stack++, GetLocalCnt2(count));
  return true;
}

static bool _GET_TRAIN_NPC_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GOTO_DRAW_CHAPTER(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_PROJECTION(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_PROJECTION(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_FADE_IN(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_FADE_OUT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DNG_DEBUG_COMMAND(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  ScriptDebugCommand(bool(GetStackInt(stack)));
  return true;
}

static bool _CD_SEEK(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_ROT_LOOK_POS(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack, atan2f(GetStackFloat(&stack[0]), GetStackFloat(&stack[1])));
  return true;
}

static bool _SET_MOTION_BLUR(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  EventScene->m_fade_in_out.m_motion_blur = bool(GetStackInt(stack));
  return true;
}

static bool _LOAD_SCRIPT(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  const char* script_name = GetStackString(stack++);
  s32 i = GetStackInt(stack++);

  if (script_name == nullptr)
  {
    return false;
  }

  EdEventInfo.m_unk_field_8C = script_name;
  EdEventInfo.m_unk_field_88 = i;
  EdEventInfo.m_unk_field_CC = 15; // FIXME: MAGIC
  return true;
}

static bool _SET_TALK_CAMERA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _HIT_EFFECT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _COPY_CHARA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_START_BUTTON(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack, EdEventInfo.m_unk_field_F0);
  return true;
}

static bool _MOVE_INTERIOR(RS_STACKDATA* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  EdEventInfo.m_unk_field_64 = GetStackInt(stack++);
  EdEventInfo.m_unk_field_68 = GetStackString(stack++);
  EdEventInfo.m_unk_field_88 = (stack_count >= 3 ? GetStackInt(stack++) : 100);
  return true;
}

static bool _GET_MONSTER_TALK_DATA(RS_STACKDATA* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  switch (stack_count)
  {
    case 2:
      SetStack(stack++, EdEventInfo.m_unk_field_1BC);
      SetStack(stack++, EdEventInfo.m_unk_field_1C4);
      return true;
    case 3:
      SetStack(stack++, EdEventInfo.m_unk_field_1BC);
      SetStack(stack++, EdEventInfo.m_unk_field_1C0);
      SetStack(stack++, EdEventInfo.m_unk_field_1C4);
      return true;
    default:
      return false;
  }
}

static bool _FUNC_POINT_SHOW(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_NOW_MAP_NO(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack, EventScene->m_now_map_no);
  return true;
}

static bool _GET_NOW_SUBMAP_NO(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack, EventScene->m_now_submap_no);
  return true;
}

static bool _GET_OLD_MAP_NO(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack, EventScene->m_old_map_no);
  return true;
}

static bool _GET_OLD_SUBMAP_NO(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack, EventScene->m_old_submap_no);
  return true;
}

static bool _SET_RAIN_CHARA_NO(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  EventRain.SetCharNo(GetStackInt(stack++));
  return true;
}

static bool _GET_EDIT_PARTS_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_CHARA_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_CHARA_TALK_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _TURN_CHARA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_CHARA_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_CHARA_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_CHARA_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MOTION(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_STEP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_TEX_ANIM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
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

static bool _SET_REFERENCE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DEL_REFERENCE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SHADOW_CLIP_OFF(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_COORDINATE_ANGLE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_CHARA_WIDTH(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_CHARA_HEIGHT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_CHARA_WEIGHT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_CHARA_SHOW(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_CHARA_SHOW(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHARA_DA_ENABLE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_MOT_NOW_WAIT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHECK_MOTION_END(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ACTCHR_SET_MOTION(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_CHARA_EX_SOUNDID(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ACTCHR_SOUND_INFO_COPY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _MES_MAKE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _MES_CLOSE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _MES_NEXTPAGE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MES_AUTOSET(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MES_SHIPPO(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MES_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MES_DRAWSPEED(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MES_CURSOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MES_OKURI(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MES_FUKIDASHI(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHECK_MES_COMPLETE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHECK_MES_WAIT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHECK_MES(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MES_WIN_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_CAMERA_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_CAMERA_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_CAMERA_REF(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_CAMERA_REF(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_CAMERA_SPEED(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  mgCCamera* camera = GetActiveCamera();

  if (camera == nullptr)
  {
    return false;
  }

  camera->SetSpeed(GetStackFloat(stack++));
  return true;
}

static bool _CAMERA_STEP(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  mgCCamera* camera = GetActiveCamera();

  if (camera == nullptr)
  {
    return false;
  }

  camera->Step(GetStackInt(stack++));
  return true;
}

static bool _SET_MES_WINDOW_MODE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MES_PRESET(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MES_ITEM_DIRECT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MES_ITEM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MES_VALUE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_MES_STATUS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_PARTY_CHARA_MES_NO(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _MES_SET_BUFF(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_MES_WINDOW_MODE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_MES_VOICE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MES_QUESTION_GYOU(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_MES_QUESTION_GYOU(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MES_CLOSE_CNT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MES_ETC(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_MES_ETC(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LOAD_MES(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _MES_SE_PLAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MES_STR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_MES_OKURI(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ASQ_INIT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _ASQ_SYNC_CHARA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _ASQ_SET_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _ASQ_MOVE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _ASQ_MOVE_STEP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _ASQ_ROT_REF(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _ASQ_CLEAR_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _ASQ_WAIT_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _ASQ_ROT_MOVE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _ASQ_ROT_ANGLE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _ASQ_SET_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _ASQ_DELAY_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _ASQ_CHECK(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _ASQ_MOTION_TRG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _ASQ_MOTION_PLAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _ASQ_MOTION_STOP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _ASQ_MOTION_NEXT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _ASQ_ANIME_TRG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _ASQ_ANIME(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _ASQ_SE_PLAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _IMG_SET_DRAW(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _IMG_SET_GET(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _IMG_SET_PUT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _IMG_SET_NAME(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _IMG_SET_MOVE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _IMG_SET_FADE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _IMG_SET_COLOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPRITE_INIT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPRITE_SET_DRAW(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPRITE_SET_TYPE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPRITE_SET_TEXTURE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPRITE_SET_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPRITE_SET_PUTSIZE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPRITE_SET_UVSIZE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPRITE_SET_COLOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPRITE_SET_SCALE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPRITE_SET_ALPHAB(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_CHECK(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_INIT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_PRDELAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_SET_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_SET_REF(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_MOVE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_MOVE_REF(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_INIT_PAS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_SET_PAS_FRM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_ADD_PAS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_START_PAS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_PR_SLOWING(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_PR_KEEP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_PR_RETURN(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_AHDDELAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_SET_ANGLE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_SET_HEIGHT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_SET_DIST(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_SET_AHD(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_MOVE_AHD(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_SYNC_OBJ(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_RELEASE_OBJ(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_AHD_SLOWING(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_AHD_KEEP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_AHD_RETURN(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_FADE_DELAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_FADE_INIT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_FADE_IN(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_FADE_OUT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_QUAKE_DELAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_QUAKE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_MOVE2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_MOVE_AHD2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_CHARA_DELAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_CHARA_ATTACH(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_MOVE_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CMRS_QUAKE2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_CHECK(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_INIT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_SYNC_OBJ(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_POS_DELAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_SET_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_MOVE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_MOVE2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_INIT_PAS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_SET_PAS_FRM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_ADD_PAS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_START_PAS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_JUMP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_SET_EOH_FRAME_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_ADD_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_ATTACH_CAMERA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_ROT_DELAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_SET_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_ROTATION(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_ROTATION2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_REFERENCE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_MOTION_DELAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_SET_MOTION(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_NEXT_MOTION(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_MOTION_WAIT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_SET_STEP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_CHANGE_STEP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_SEQ_MOT_TRG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_SEQ_MOT_TRG_WAIT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_RESET_MOTION(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_SET_MOTION_NOW_TIME(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_SET_MOTION_WAIT_TIME(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_TEXA_DELAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_TEX_ANIME(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_COLOR_DELAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_SET_COLOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_SCALE_DELAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_SET_SCALE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_SE_DELAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_SE_PLAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_RESET_DA_POSITION(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _OBJS_NORMAL_DRIVE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_CONTENTS_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _GET_BPOT_POS(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack++, BTpot.m_position.x);
  SetStack(stack++, BTpot.m_position.y);
  SetStack(stack++, BTpot.m_position.z);
  return true;
}

static bool _GET_BPOT_STATUS(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack++, s32(BTpot.m_status));
  return true;
}

static bool _GET_PERSON_STATUS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return false;
}

static bool _GET_CONTROL_CHRID(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack++, s32(EventScene->m_control_chrid));
  return true;
}

static bool _GET_BEFORE_CAMERA_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_BEFORE_CAMERA_REF(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_CAMERA_NEXT_REF(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GOTO_MENU(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_MENU_STATUS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return false;
}

static bool _LOAD_EQUIP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_EQUIP_ITEMNO(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_TIME_STEP_ENABLE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_DOOR_MATERIAL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _INIT_DRAMA_SCENE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_ACTIVE_CMRID(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack++, EventScene->m_active_cmrid);
  return true;
}

static bool _SET_BEFORE_CMRID(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack++, EventScene->m_before_cmrid);
  return true;
}

static bool _DNGMAP_LOAD(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DNGMAP_DELETE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DNGMAP_MOVE_PIECE(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  EventDngMap.SetPieceMove(static_cast<s16>(GetStackInt(stack++)));
  return true;
}

static bool _DNGMAP_ONOFF(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  EventDngMap.m_unk_field_8 = bool(GetStackInt(stack++));
  return true;
}

static bool _DNGMAP_SET_FADE(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  bool fade_in = bool(GetStackInt(stack++));
  s32 duration = GetStackInt(stack++);

  if (fade_in)
  {
    EventDngMap.FadeIn(duration);
  }
  else
  {
    EventDngMap.FadeOut(duration);
  }

  return true;
}

static bool _GET_BEFORE_CAMERA_NEXT_POS(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  mgCCamera* camera = EventScene->GetCamera(EventScene->m_before_cmrid);

  if (camera == nullptr)
  {
    return false;
  }

  vec3 next_pos = camera->GetNextPos();
  SetStack(stack++, next_pos.x);
  SetStack(stack++, next_pos.y);
  SetStack(stack++, next_pos.z);
  return true;
}

static bool _GET_BEFORE_CAMERA_NEXT_REF(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  mgCCamera* camera = EventScene->GetCamera(EventScene->m_before_cmrid);

  if (camera == nullptr)
  {
    return false;
  }

  vec3 next_ref = camera->GetNextRef();
  SetStack(stack++, next_ref.x);
  SetStack(stack++, next_ref.y);
  SetStack(stack++, next_ref.z);
  return true;
}

static bool _SET_CAMERA_NEXT_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHK_INTERSECTION_POINT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_FCAMERA_FOLLOW(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto camera_follow = static_cast<mgCCameraFollow*>(EventScene->GetCamera(EventScene->m_active_cmrid));

  if (camera_follow == nullptr)
  {
    return false;
  }

  vec3 follow = GetStackVector(stack).xyz();
  camera_follow->SetFollow(follow);

  return true;
}

static bool _SET_FCAMERA_FOLLOW_A(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto camera_follow = static_cast<mgCCameraFollow*>(EventScene->GetCamera(EventScene->m_active_cmrid));

  if (camera_follow == nullptr)
  {
    return false;
  }

  vec3 follow = GetStackVector(stack).xyz();
  camera_follow->SetFollow(follow);

  return true;
}

static bool _SET_FCAMERA_FOLLOW_OFS(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto camera_follow = static_cast<mgCCameraFollow*>(EventScene->GetCamera(EventScene->m_active_cmrid));

  if (camera_follow == nullptr)
  {
    return false;
  }

  vec3 follow_offset = GetStackVector(stack).xyz();
  camera_follow->SetFollowOffset(follow_offset);

  return true;
}

static bool _SET_FCAMERA_FOLLOW_FLAG(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto camera_follow = static_cast<mgCCameraFollow*>(EventScene->GetCamera(EventScene->m_active_cmrid));

  if (camera_follow == nullptr)
  {
    return false;
  }

  bool active = bool(GetStackInt(stack++));

  if (active)
  {
    camera_follow->FollowOn();
  }
  else
  {
    camera_follow->FollowOff();
  }

  return true;
}

static bool _FCAMERA_STEP(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto camera_follow = static_cast<mgCCameraFollow*>(EventScene->GetCamera(EventScene->m_active_cmrid));

  if (camera_follow == nullptr)
  {
    return false;
  }

  camera_follow->Step(GetStackInt(stack++));
  return true;
}

static bool _SET_FCAMERA_ANGLE(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto camera_follow = static_cast<mgCCameraFollow*>(EventScene->GetCamera(EventScene->m_active_cmrid));

  if (camera_follow == nullptr)
  {
    return false;
  }

  camera_follow->SetAngle(GetStackFloat(stack++));
  return true;
}

static bool _SET_FCAMERA_HEIGHT(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto camera_follow = static_cast<mgCCameraFollow*>(EventScene->GetCamera(EventScene->m_active_cmrid));

  if (camera_follow == nullptr)
  {
    return false;
  }

  camera_follow->SetHeight(GetStackFloat(stack++));
  return true;
}

static bool _SET_FCAMERA_DIST(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto camera_follow = static_cast<mgCCameraFollow*>(EventScene->GetCamera(EventScene->m_active_cmrid));

  if (camera_follow == nullptr)
  {
    return false;
  }

  camera_follow->SetDistance(GetStackFloat(stack++));
  return true;
}

static bool _GET_REF_ANGLE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DNG_SET_STAGE_ID(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();

  if (save_data == nullptr)
  {
    return false;
  }

  save_data->m_save_data_dungeon.m_now_dungeon_id = EDungeonID(GetStackInt(stack++));
  return true;
}

static bool _DNG_GET_STAGE_ID(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();

  if (save_data == nullptr)
  {
    return false;
  }

  SetStack(stack, s32(save_data->m_save_data_dungeon.m_now_dungeon_id));
  return true;
}

static bool _SET_CAMERA_CTRL(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto camera_control = static_cast<CCameraControl*>(EventScene->GetCamera(EventScene->m_active_cmrid));

  if (camera_control == nullptr)
  {
    return false;
  }

  bool active = bool(GetStackInt(stack++));

  if (active)
  {
    camera_control->FollowOn();
    camera_control->ControlOn();
  }
  else
  {
    camera_control->FollowOff();
    camera_control->ControlOff();
  }

  return true;
}

static bool _GET_FCAMERA_ANGLE(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto camera_follow = static_cast<mgCCameraFollow*>(EventScene->GetCamera(EventScene->m_active_cmrid));

  if (camera_follow == nullptr)
  {
    return false;
  }

  SetStack(stack, camera_follow->GetAngle());
  return true;
}

static bool _GET_FCAMERA_HEIGHT(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto camera_follow = static_cast<mgCCameraFollow*>(EventScene->GetCamera(EventScene->m_active_cmrid));

  if (camera_follow == nullptr)
  {
    return false;
  }

  SetStack(stack, camera_follow->GetHeight());
  return true;
}

static bool _GET_FCAMERA_DIST(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto camera_follow = static_cast<mgCCameraFollow*>(EventScene->GetCamera(EventScene->m_active_cmrid));

  if (camera_follow == nullptr)
  {
    return false;
  }

  SetStack(stack, camera_follow->GetDistance());
  return true;
}

static bool _GET_INVENTION_ID(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();

  if (save_data == nullptr)
  {
    return false;
  }

  auto& invent_user_data = save_data->m_user_data_manager.m_invent_user_data;

  SetStack(
    stack, 
    sint(
      invent_user_data.IsAlreadyCreatedItem(
        ECommonItemData(
          GetStackInt(stack)
        )
      )
    )
  );
  return true;
}

static bool _FUNCTION_MAP_JUMP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto& event_data = EventScene->m_scene_event_data;

  // FIXME: MAGIC
  if ((event_data.m_unk_field_0 & 0x10A) == 0)
  {
    return false;
  }

  EdEventInfo.m_unk_field_64 = -1;
  EdEventInfo.m_unk_field_88 = 100;

  if (event_data.m_unk_field_18 == "exit")
  {
    // FIXME: MAGIC
    EdEventInfo.m_unk_field_CC = 7;
  }
  else
  {
    EdEventInfo.m_unk_field_68 = event_data.m_unk_field_18;
    // FIXME: MAGIC
    EdEventInfo.m_unk_field_CC = 4;
  }

  return true;
}

static bool _FUNCTION_DOOR_MODE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto& event_data = EventScene->m_scene_event_data;

  EdEventInfo.m_unk_field_13C = 0;
  EdEventInfo.m_unk_field_140 = event_data.m_unk_field_C;
  EdEventInfo.m_unk_field_144 = event_data.m_unk_field_10;
  EdEventInfo.m_unk_field_17C = event_data.m_unk_field_A0.x;
  EdEventInfo.m_unk_field_180 = event_data.m_unk_field_A0.y;
  EdEventInfo.m_unk_field_184 = event_data.m_unk_field_A0.z;
  EdEventInfo.m_unk_field_188 = atan2f(event_data.m_unk_field_90.x, event_data.m_unk_field_90.z);
  EdEventInfo.m_unk_field_D0 = 4; // FIXME: MAGIC

  return true;
}

static bool _GET_MONEY(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();

  if (save_data == nullptr)
  {
    return false;
  }

  SetStack(stack, save_data->m_user_data_manager.m_money);
  return true;
}

static bool _ADD_MONEY(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();

  if (save_data == nullptr)
  {
    return false;
  }

  save_data->m_user_data_manager.m_money += GetStackInt(stack++);
  return true;
}

static bool _GET_ITEM_NUM(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();

  if (save_data == nullptr)
  {
    return false;
  }

  auto& user_data = save_data->m_user_data_manager;
  SetStack(
    stack,
    s32(
      user_data.GetNumSameItem(
        ECommonItemData(
          GetStackInt(stack++)
        )
      )
    )
  );

  return true;
}

static bool _CHECK_BUTTON(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  bool btn_down = false;
  using enum host::pad_handler::buttons;

  switch (GetStackInt(stack++))
  {
    case 0:
      // Cross
      if (LanguageCode == Language::Japanese)
      {
        btn_down = g_host_interface->pad_button_any_down(circle);
      }
      else
      {
        btn_down = g_host_interface->pad_button_any_down(cross);
      }
      break;
    case 1:
      // Circle
      if (LanguageCode == Language::Japanese)
      {
        btn_down = g_host_interface->pad_button_any_down(cross);
      }
      else
      {
        btn_down = g_host_interface->pad_button_any_down(circle);
      }
      break;
    case 2:
      // Square
      btn_down = g_host_interface->pad_button_any_down(square);
      break;
    case 3:
      // Select
      btn_down = g_host_interface->pad_button_any_down(select);
      break;
    default:
      // Invalid call
      return false;
  }

  SetStack(stack++, static_cast<sint>(btn_down));
  return true;
}

static bool _GET_LANGUAGE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack, s32(LanguageCode));
  return true;
}

static bool _CHECK_INVENT_ITEM(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(&stack[1], CheckInventItem(static_cast<ECommonItemData>(GetStackInt(&stack[0]))));
  return true;
}

static bool _SET_AI(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  sint villager_id = GetStackInt(stack++);
  bool active = common::bits::to_bool(stack++);
  
  if (active)
  {
    EventScene->CancelStayVillager(villager_id);
  }
  else
  {
    EventScene->StayVillager(villager_id);
  }

  return true;
}

static bool _CHECK_INVENT_PHOTO(RS_STACKDATA* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  switch (stack_count)
  {
    case 2:
      SetStack(&stack[1], static_cast<sint>(CheckInventPhoto(GetStackInt(&stack[0]), 0)));
      return true;
    case 3:
      SetStack(&stack[2], static_cast<sint>(CheckInventPhoto(GetStackInt(&stack[0]), GetStackInt(&stack[1]))));
      return true;
    default:
      return false;
  }
}

static bool _GET_PHOTO_NUM(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();
  if (save_data == nullptr)
  {
    return false;
  }
  
  SetStack(stack++, static_cast<sint>(save_data->m_user_data_manager.m_invent_user_data.GetNowHavePictureNum()));
  return true;
}

static bool _SET_CONTENTS_ETC(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return true;
}

static bool _SET_STATUS(RS_STACKDATA* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  sint data_type = GetStackInt(stack++);
  sint data_index = GetStackInt(stack++);
  sint data_status = GetStackInt(stack++);
  bool flag = (stack_count >= 4 ? common::bits::to_bool(GetStackInt(stack++)) : true);

  if (flag)
  {
    EventScene->SetStatus(
      static_cast<ESceneDataType>(data_type),
      data_index,
      static_cast<ESceneDataStatus>(data_status)
    );
  }
  else
  {
    EventScene->ResetStatus(
      static_cast<ESceneDataType>(data_type),
      data_index,
      static_cast<ESceneDataStatus>(data_status)
    );
  }

  return true;
}

static bool _GOTO_SUBGAME(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto game_id = ESubGameID(GetStackInt(stack++));

  SubGameInfo sub_game_info;
  sub_game_info.m_scene = EventScene;
  sub_game_info.m_unk_field_4 = EventScene->m_unk_field_3E68;
  sub_game_info.m_unk_field_8 = EventScene->m_unk_field_3E6C;

  sgInitSubGame(game_id, &sub_game_info);
  return true;
}

static bool _SET_GYORACE_ETC(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_GYORACE_ETC(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_SAVEDATA_ETC(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  switch (GetStackInt(stack++))
  {
    case 0:
    {
      // 26A07C
      auto save_data = GetSaveData();
      if (save_data == nullptr)
      {
        return false;
      }

      save_data->m_unk_field_1A08 = GetStackInt(stack++);
      return true;
    }
    case 1:
    {
      // 26A0A8
      auto save_data = GetSaveData();
      if (save_data == nullptr)
      {
        return false;
      }

      auto badge_data = save_data->m_user_data_manager.GetMonsterBadgeDataPtrMosId(static_cast<EMonsterID>(GetStackInt(stack++)));
      if (badge_data == nullptr)
      {
        return false;
      }

      badge_data->m_unk_field_A = 1;
      return true;
    }
    case 2:
    {
      // 26A104
      auto save_data = GetSaveData();
      if (save_data == nullptr)
      {
        return false;
      }

      save_data->m_user_data_manager.AllWeaponRepair();
      return true;
    }
    case 3:
    {
      // 26A144
      auto save_data = GetSaveData();
      if (save_data == nullptr)
      {
        return false;
      }

      save_data->m_unk_field_643C9 = GetStackInt(stack++);
      return true;
    }
    case 4:
      // 26A178
      DeleteErekiFish();
      return true;
    default:
      return false;
  }
}

static bool _GET_SAVEDATA_ETC(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();
  if (save_data == nullptr)
  {
    return false;
  }

  switch (GetStackInt(stack++))
  {
    case 0:
      // 26A208
      SetStack(stack++, save_data->m_unk_field_1A08);
      return true;
    case 1:
    {
      // 26A21C
      sint monster_id = GetStackInt(stack++);
      auto badge_data = save_data->m_user_data_manager.GetMonsterBadgeDataPtrMosId(static_cast<EMonsterID>(monster_id));
      if (badge_data == nullptr)
      {
        return false;
      }

      SetStack(stack++, badge_data->m_unk_field_A);
      return true;
    }
    case 2:
      // 26A270
      SetStack(stack++, static_cast<sint>(save_data->m_user_data_manager.CheckElectricFish()));
      return true;
    case 3:
    {
      // 26A2A8
      auto bait = save_data->m_user_data_manager.GetActiveBait(static_cast<ECommonItemData>(GetStackInt(stack++)));
      if (bait == nullptr)
      {
        return false;
      }

      SetStack(stack++, static_cast<sint>(bait->m_common_index));
      return true;
    }
    case 4:
      // 26A2FC
      PlayTimeCount(true);
      SetStack(stack++, static_cast<sint>(save_data->m_play_time_count));
      return true;
    case 5:
      // 26A318
      SetStack(stack++, static_cast<sint>(GetConfigCaptionOff()));
      return true;
    case 6:
      // 26A334
      SetStack(stack++, static_cast<sint>(save_data->CheckNowTourType()));
      return true;
    default:
      return false;
  }
}

static bool _DEL_MONSTER(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MENU_ETC(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_MENU_ETC(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_ANALYZE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_DIORAMA_PERCENT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GEORAMA_FUNC(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_CHARA_ID(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto chara_id = EventScene->SearchCharaID(static_cast<ECharacterID>(GetStackInt(stack++)));
  SetStack(stack, chara_id);
  return true;
}

static bool _SET_LOADBG_FILE_MONS_TALK(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LOAD_MES_MONS_TALK(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GOTO_EDITMODE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  EdEventInfo.m_unk_field_CC = 17; // FIXME: MAGIC
  return true;
}

static bool _GET_CHAPTER(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();

  if (save_data == nullptr)
  {
    return false;
  }

  SetStack(stack, GetNowChapter(save_data));
  return true;
}

static bool _GET_NPC_TRAIN_ETC(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _REGISTER_VILLAGER(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EYE_VIEW_DRAW_ON_OFF(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  EventScene->EyeViewDrawOnOff(bool(GetStackInt(stack)));
  return true;
}

static bool _SET_QUEST_ETC(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  sint command = GetStackInt(stack++);
  uint quest_index = GetStackInt(stack++);
  bool flag = GetStackInt(stack++);

  switch (command)
  {
    case 0:
      QuestRequestSetFlag(quest_index, flag);
      return true;
    case 1:
      QuestRequestClear(quest_index, flag);
      return true;
    default:
      return false;
  }
}

static bool _GET_QUEST_ETC(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  sint command = GetStackInt(stack++);
  uint quest_index = GetStackInt(stack++);

  switch (command)
  {
    case 0:
      SetStack(stack, s32(GetQuestRequestStatus(quest_index)));
      return true;
    default:
      return false;
  }
}

static bool _CHK_INTERSECTION_POINT_PIPE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_OLD_INTERIOR_MAP_NO(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack, GetOldInteriorMapNo());
  return true;
}

static bool _SET_EVENT_DATA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _STOPWATCH(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_FUNC_ETC(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_FISHINGTOURNAMENT_ETC(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_CHARA_FAR_DIST(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto character = GetCharacter(GetStackInt(stack++));
  if (character == nullptr)
  {
    return false;
  }

  character->SetFarDist(GetStackFloat(stack++));
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

static bool _GET_OMAKE_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_WIND(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  f32 wind_vel = GetStackFloat(stack++);

  if (wind_vel < 0.0f)
  {
    EventScene->ResetWind();
  }
  else
  {
    EventScene->SetWind(
      {
        GetStackFloat(&stack[0]),
        GetStackFloat(&stack[1]),
        GetStackFloat(&stack[2]),
      },
      wind_vel
    );
  }

  return true;
}

static bool _SET_OMAKE_FLAG(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  OmakeFlag = GetStackInt(stack++);
  return true;
}

static bool _SND_INIT_PORT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SND_LOAD_SOUND(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SND_SE_PLAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_SND_ID(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SND_SE_PAUSE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SND_SE_STOP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SND_SET_SE_VOL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SND_SET_SE_PAN(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SND_SET_SE_PITCH(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SND_SE_ALL_STOP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LOAD_BGM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _PLAY_BGM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _STOP_BGM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _STREAM_OPEN(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _STREAM_PLAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _STREAM_STOP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _STREAM_STANDBY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _STREAM_GET_STATUS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_SYS_SND_ID(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _STREAM_OPEN_CHECK(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LOAD_SE_ENV(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _PLAY_ENV_BGM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SYS_SE_PLAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _INIT_SE_SRC(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _INIT_SE_ENV(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _INIT_SE_BAS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LOAD_SE_SRC(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LOAD_SE_FOOT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LOAD_SE_DOOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LOAD_SE_BOX(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LOAD_SE_BATTLE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SND_DELETE_PORT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _STOP_ENV_BGM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _FADE_IN_BGM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _FADE_OUT_BGM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_BGM_VOL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SND_SET_REVERB(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SND_SET_ENV_VOL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _STREAM_SILENT_CHECK(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _AUTO_CHANGE_ENV(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _BGM_LOAD_CANCEL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SOUND_LOAD_CANCEL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _BGM_LOAD_ENABLE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SOUND_LOAD_ENABLE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LOAD_SE_BASE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LOAD_SOUND(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _STREAM_CLOSE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _STREAM_OPEN2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LOAD_BGM_PACK(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_BGM_NO(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_MASTER_VOL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MASTER_VOL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_BTL_BGM_VOL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_BTL_BGM_VOL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SND_IN_REVERB(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SND_STOP_SRC(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SND_PAUSE_BGM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _STREAM_OPEN3(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_ACTIVE_BGM_STATUS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_ACTIVE_BGM_STATUS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_BGM_STATUS_NOW_NO(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_SE_STATUS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SE_ALL_STOP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SOUND_ALL_STOP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _BGM_PLAY_CANCEL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _BGM_PLAY_ENABLE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_DEF_BGM_NO(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MOVIE_CC(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _REGISTER_VILLAGER2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_FISHINGTOURNAMENT_ETC(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SYNC_CHARA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SYNC_OBJ(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SET_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SET_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_GET_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_GET_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SET_MOTION(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SET_STEP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SET_TEX_ANIM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SET_SCALE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SET_SHOW(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_GET_SHOW(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SET_FRAME_SHOW(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SET_SHADOW(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SET_TRANSLATE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SYNC_SPRITE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SET_FOOT_SOUND_ID(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SET_FRAME_STATUS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_GET_FRAME_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SET_SOUND_ID(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_GET_FRAME_STATUS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SYNC_CHROBJ(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SET_FADE_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_RESET_DA_POSITION(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SET_SHADOW_FRAME_STATUS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SYNC_GEOSTONE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SYNC_SEARCH_CHARA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_NORMAL_DRIVE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SYNC_EDIT_OBJ(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SET_FRAME_ALPHA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SYNC_FUNCP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SET_FOOT_SE_ID(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _EOH_SYNC_DOOR_PARTS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_INIT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_SET_UP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_SET_PLAY_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_SET_MINIMAP_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_SET_MM_LINE_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_SET_MM_LINE_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_SET_PIN_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_GET_PIN_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_SET_BALL_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_GET_BALL_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_SET_PIN_COL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_GET_PIN_COL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_SET_BALL_COL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_GET_BALL_COL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_SET_PAR_COUNT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_GET_PAR_COUNT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_GET_MINI_LEVEL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_GET_TEXB(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_SET_STATUS_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_RESET_POWGAGE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_START_POWGAGE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_TRIGGER_POWGAGE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_GET_SHOT_POW(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_GET_POWGAGE_CODE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_SET_POWGAGE_SAFE_LEVEL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_GET_CLUB_DEF(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_SET_SPIN_MARK_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_SET_CLUB_NO(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_CALC_CARRY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_GET_PG_CURSOR_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_SET_COL_MODEL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_GET_PRIZE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_SET_LAST_CHALLENGE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_GET_LAST_CHALLENGE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_GET_OMAKE_MODE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_SET_NOW_HOLE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_GET_NOW_HOLE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_SET_SCORE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SPHIDA_GET_SCORE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ZERO_VECTOR(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack++, 0.0f);
  SetStack(stack++, 0.0f);
  SetStack(stack++, 0.0f);
  return true;
}

static bool _NORMAL_VECTOR(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  vec3 v
  {
    GetStackFloat(&stack[0]),
    GetStackFloat(&stack[1]),
    GetStackFloat(&stack[2]),
  };

  v = glm::normalize(v);

  SetStack(&stack[0], v.x);
  SetStack(&stack[1], v.y);
  SetStack(&stack[2], v.z);

  return true;
}

static bool _COPY_VECTOR(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  vec3 v = GetStackVector(&stack[3]);

  SetStack(&stack[0], v.x);
  SetStack(&stack[1], v.y);
  SetStack(&stack[2], v.z);

  return true;
}

static bool _ADD_VECTOR(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  vec3 lhs = GetStackVector(&stack[0]);
  vec3 rhs = GetStackVector(&stack[3]);
  lhs += rhs;

  SetStack(&stack[0], lhs.x);
  SetStack(&stack[1], lhs.y);
  SetStack(&stack[2], lhs.z);

  return true;
}

static bool _SUB_VECTOR(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  vec3 lhs = GetStackVector(&stack[0]);
  vec3 rhs = GetStackVector(&stack[3]);
  lhs += rhs;

  SetStack(&stack[0], lhs.x);
  SetStack(&stack[1], lhs.y);
  SetStack(&stack[2], lhs.z);

  return true;
}

static bool _SCALE_VECTOR(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  vec3 lhs = GetStackVector(&stack[0]);
  vec3 rhs = GetStackVector(&stack[3]);
  lhs *= rhs;

  SetStack(&stack[0], lhs.x);
  SetStack(&stack[1], lhs.y);
  SetStack(&stack[2], lhs.z);

  return true;
}

static bool _DIV_VECTOR(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  // Check for division by zero
  f32 divisor = GetStackFloat(&stack[3]);

  if (divisor == 0.0f)
  {
    return false;
  }

  // The division proper
  vec3 lhs = GetStackVector(&stack[0]);
  
  lhs /= divisor;

  SetStack(&stack[0], lhs.x);
  SetStack(&stack[1], lhs.y);
  SetStack(&stack[2], lhs.z);

  return true;
}

static bool _DIST_VECTOR(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack, mgDistVector(GetStackVector(stack).xyz));
  return true;
}

static bool _DIST_VECTOR2(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack, mgDistVector2(GetStackVector(stack).xyz));
  return true;
}

static bool _SQRT(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack, sqrtf(GetStackFloat(stack)));
  return true;
}

static bool _ATAN2F(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack, atan2f(GetStackFloat(&stack[0]), GetStackFloat(&stack[1])));
  return true;
}

static bool _ANGLE_CMP(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack, mgAngleCmp(GetStackFloat(&stack[0]), GetStackFloat(&stack[1]), GetStackFloat(&stack[2])));
  return true;
}

static bool _ANGLE_LIMIT(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack, mgAngleLimit(GetStackFloat(stack)));
  return true;
}

static bool _GET_RAND(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  if ((stack++)->m_data_type == EStackDataType::Float)
  {
    f32 n = GetStackFloat(stack++);
    SetStack(stack, rand() / f32(common::constants::s32_max) * n);
  }
  else
  {
    s32 n = GetStackInt(stack++);
    SetStack(stack, s32(rand() / f32(common::constants::s32_max) * f32(n)));
  }

  return true;
}

static bool _LINE_POINT_DIST(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  vec3 start = GetStackVector(&stack[0]);
  vec3 end = GetStackVector(&stack[3]);
  vec3 point = GetStackVector(&stack[6]);
  RS_STACKDATA* dist_dest = &stack[9];

  f32 dist = mgDistVector(start, end);

  vec3 v1 = point - start;
  vec3 dir = glm::normalize(end - start);

  f32 inner_product = glm::dot(v1, dir);

  if (inner_product < 0.0f || inner_product > dist)
  {
    SetStack(dist_dest, -1.0f);
    return true;
  }
  else
  {
    dir *= inner_product;
    dir += start;
    SetStack(dist_dest, mgDistVector(point, dir));
    return true;
  }
}

static bool _CREATE_SWORD_EFFECT(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  s32 stack_id = GetStackInt(stack++); // unused
  s32 i1 = GetStackInt(stack++);
  s32 i2 = GetStackInt(stack++);

  SwordEffect = std::make_unique<CSwordAfterImage>();

  if (SwordEffect == nullptr)
  {
    // panicf likely will not work with OOM
    common::debug::panic("_CREATE_SWORD_EFFECT: Out Of Memory");
  }

  SwordEffect->Initialize(EventScene->GetStack(stack_id), i1, i2);
  return true;
}

static bool _DELETE_SWORD_EFFECT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SwordEffect.reset();
  return true;
}

static bool _SWORD_EFFECT_COLOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SWORD_EFFECT_ADD_POINT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ADD_CHARA_POS(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  s32 chara_id = GetStackInt(stack++);
  vec3 delta = GetStackVector(stack).xyz();

  auto chara = GetCharacter(chara_id);
  if (chara == nullptr)
  {
    return false;
  }

  vec3 pos = chara->GetPosition() + delta;
  chara->SetPosition(pos);
  return true;
}

static bool _ADD_CHARA_ROT(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  s32 chara_id = GetStackInt(stack++);
  vec3 delta = GetStackVector(stack).xyz();

  auto chara = GetCharacter(chara_id);
  if (chara == nullptr)
  {
    return false;
  }

  vec3 rot = chara->GetRotation() + delta;
  rot.x = mgAngleLimit(rot.x);
  rot.y = mgAngleLimit(rot.y);
  rot.z = mgAngleLimit(rot.z);
  chara->SetRotation(rot);
  return true;
}

static bool _POST_TREASURE_BOX(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_PARTS_ORIGIN(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CTRLC_STEP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CTRLC_SET_ROTATE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CTRLC_MOVE_CAMERA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CTRLC_SET_ROT_CANCEL(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  static_cast<CCameraControl*>(GetActiveCamera())->SetRotCameraCancel(GetStackInt(stack++));
  return true;
}

static bool _CTRLC_MOVE_RANGE(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto camera_param = static_cast<CCameraControl*>(GetActiveCamera())->GetActiveParam();

  camera_param.m_unk_field_8 = GetStackFloat(stack++);
  camera_param.m_unk_field_C = GetStackFloat(stack++);
  camera_param.m_unk_field_0 = GetStackFloat(stack++);
  camera_param.m_unk_field_4 = GetStackFloat(stack++);
  return true;
}

static bool _GET_NEAR_TBOX_POS(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  CTreasureBoxManager* treasure_box_man = EventScene->m_battle_area_scene.m_treasure_box_manager;
  
  // Grab the position to check against
  vec3 check_position = GetStackVector(stack);
  stack += 3;

  // We want to find the nearest treasure box index and position
  std::optional<usize> box_index{ std::nullopt };
  f32 near_distance{ 9999.0f };
  vec3 near_position{ 0.0f };

  // Iterate over all treasure boxes in the manager to find the closest treasure box
  for (usize i = 0; i < treasure_box_man->m_treasure_boxes.size(); ++i)
  {
    CTreasureBox* box = &treasure_box_man->m_treasure_boxes[i];
    vec3 box_position = box->GetPosition();
    f32 distance = math::vector_distance(box_position, check_position);

    if (distance < near_distance)
    {
      // We found a new nearest closest treasure box
      near_distance = distance;
      box_index = i;
    }
  }

  // If we found a valid box, grab its position.
  if (box_index.has_value())
  {
    near_position = treasure_box_man->m_treasure_boxes[box_index.value()].GetPosition();
  }

  // Put the nearest position/index onto the stack
  // ({0, 0, 0} and -1 if not found)
  SetStack(stack++, near_position.x);
  SetStack(stack++, near_position.y);
  SetStack(stack++, near_position.z);
  SetStack(stack++, static_cast<sint>(box_index.value_or(-1)));

  return true;
}

static bool _CONV_CHRNO_S2L(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return false;
}

static bool _SWE_INIT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SWE_SET_COLOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SWE_SET_TEXTURE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SWE_START_EFFECT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_CHARA_TYPE(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto chara_index = GetStackInt(stack++);
  auto chara_type = GetStackInt(stack++);
  EventScene->SetType(ESceneDataType::Character, chara_index, chara_type);
  return true;
}

static bool _GET_EVENT_DATA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DNG_SET_PREV_FLOOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DNG_GET_PREV_FLOOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DNG_SET_FAST_FLOOR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  return false;
}

static bool _SET_FLOOR_INFO(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_FLOOR_INFO(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_NEXT_FLOOR(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  sint i1 = GetStackInt(stack++);
  sint i2 = GetStackInt(stack++);
  SetStack(stack++, EventScene->m_battle_area_scene.m_dng_floor_manager.GetDngMapNextFloorID(i1, i2));
  return true;
}

static bool _PAD_AUTO_REPEAT_OFF(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _PAD_SET_AUTO_REPEAT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DNG_PAUSE(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  uint mask = GetStackInt(stack++);
  bool active = common::bits::to_bool(GetStackInt(stack++));

  if (active)
  {
    EventScene->m_battle_area_scene.m_unk_field_8 |= mask;
  }
  else
  {
    EventScene->m_battle_area_scene.m_unk_field_8 &= ~(mask);
  }
  return true;
}

static bool _DNG_CHECK_PAUSE(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack++, static_cast<sint>(EventScene->m_battle_area_scene.m_unk_field_8));
  return true;
}

static bool _DNG_RESET_TIMER(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  EventScene->m_battle_area_scene.m_timer = 0;
  return true;
}

static bool _DNG_GET_TIMER(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack++, EventScene->m_battle_area_scene.m_timer);
  return true;
}

static bool _LOAD_SKIN(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHK_CAMERA_COL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_PARTS_FUNC_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _RANDOM_CIRCLE_GET_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _RANDOM_CIRCLE_OFF(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DNG_XCHG_MAP_LIGHT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GEOSTONE_ANIME_OFF(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GEOSTONE_SET_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GEOSTONE_SET_REFERENCE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GEOSTONE_DEL_REFERENCE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_ROBO_MOVE_TYPE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_EXIT_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_EXIT_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_E3_VERSION(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack, false);
  return true;
}

static bool _CHK_PAD_CTRL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CTRLC_STAY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _BSCN_SET_BLIGHT_RATE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_RND_CIRCLE_TRAPID(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_RND_CIRCLE_STATUS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_STATUSBAR_SHOW(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_PULL_ITEM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _MENU_CHARA_CHANGE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_EVENT_INFO_SNDID(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_PARTS_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CANCEL_DRAMA_SCENE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_RNDC_MOT_NOWT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_CHARA_MOT_NOWT(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack, RandomCircle.m_character.m_now_frame);
  return true;
}

static bool _CHARA_NORMAL_DRIVE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHARA_RESET_DA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DNG_SETUP_MAIN_UNIT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _JOIN_PARTY_MEMBER(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_CHARA_CHANGE_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_CHARA_CHANGE_MASK(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHANGE_DIR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SUB_ITEM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_CHARA_EQUIP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LOAD_PACK_FILE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_BIT_CTRL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_BIT_CTRL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LOAD_ARG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_ITEM_HAVE_NUM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_SKIP_BUTTON(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_SKIP_FCOL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_DEBUG_MODE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_MAP_TYPE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DNG_COLLISION_ALL_CLR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MAP_DRAW(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHECK_MC_LOAD(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_NOW_MAP_NO(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_TBOX_PARAM(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CANCEL_LOAD_VILLAGER(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CANCEL_NOW_LOADING(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_INITIALIZE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_INIT_FIX(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_CLEAR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ESM_LOAD_BASE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
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

static bool _ESM_SET_VECT2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
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

static bool _ESM_LOAD_BASE_PACK(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
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

static bool _SET_CHARA_CONDITION(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ADD_WHP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ADD_HP_RATE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_TIME(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHECK_GET_ITEM_LIMIT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHECK_ITEM_OVER(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_NOW_LOOP_NO(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _IS_CLEAR_DESTROY(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _IS_CLEAR_PRACTICE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _IS_PLAY_SUB_GAME(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _RESET_SUBJECT_COUNTER(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SCR_EFF_INIT_RASTER(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SCR_EFF_START_RASTER(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SCR_EFF_STOP_RASTER(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_MPCHARA_MOTION(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _FUNC_POINT_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CTRLC_ROT_BACK(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _PARTS_NAME_STRCMP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_TRIAL_VERSION(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  SetStack(stack, false);
  return true;
}

static bool _SET_FLOOR_EPISODE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _FUNC_POINT_GET_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _FUNC_POINT_GET_ROT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ACTCHR_SET_DEF_MOTION(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ADD_FUSION_POINT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_DEBUG_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _MINIMAP_DOOR_ENABLE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DNG_CHECK_BOSS_MAP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DNG_RUN_EVENT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHECK_ENABLE_CHARA_CHANGE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  if (stack_count != 2)
  {
    return false;
  }

  ECharacterID chara_id = static_cast<ECharacterID>(GetStackInt(stack++));

  auto save_data = GetSaveData();
  if (save_data == nullptr)
  {
    return false;
  }

  SetStack(stack++, save_data->m_user_data_manager.CheckEnableCharaChange(chara_id));
  return true;
}

static bool _INIT_SEPIA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _START_SEPIA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  EventScreenEffect.CaptureSepiaScreen();
  EventScreenEffect.SetSepiaFlag(true);
  return true;
}

static bool _END_SEPIA(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  EventScreenEffect.SetSepiaFlag(false);
  return true;
}

static bool _COPY_MONS2SCNCHR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _UNLOCK_STACK(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _RESET_EVENT_TRG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  EventScene->m_unk_field_2E88 = false;
  return true;
}

static bool _SET_CHARA_NO(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  sint character_index = GetStackInt(stack++);
  ECharacterID character_no = static_cast<ECharacterID>(GetStackInt(stack++));
  EventScene->SetCharaNo(character_index, character_no);
  return true;
}

static bool _GET_CHARA_NO(RS_STACKDATA* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);
  if (stack_count != 2)
  {
    return false;
  }

  auto index = EventScene->GetCharaNo(GetStackInt(stack++));
  SetStack(stack++, static_cast<sint>(index));
  return true;
}

static bool _SEARCH_CHARA_NO(RS_STACKDATA* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);
  if (stack_count != 2)
  {
    return false;
  }

  auto index = EventScene->SearchCharaID(static_cast<ECharacterID>(GetStackInt(stack++)));
  SetStack(stack++, index);
  return true;
}

static bool _GET_NEAR_RANDOM_STONE_POS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _INIT_MONO_FLASH(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _START_MONO_FLASH(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  EventScreenEffect.CaptureMonoFlashScreen();
  EventScreenEffect.SetMonoFlashFlag(true, common::bits::to_bool(GetStackInt(stack++)));
  return true;
}

static bool _END_MONO_FLASH(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  EventScreenEffect.SetMonoFlashFlag(false, false);
  return true;
}

static bool _DELETE_VILLAGER(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  EventScene->DeleteVillager(GetStackInt(stack++));
  return true;
}

static bool _DNG_SET_WEATHER(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_CHARA_MAXHP(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();
  if (save_data == nullptr)
  {
    return false;
  }

  ECharacterID chara_id = static_cast<ECharacterID>(GetStackInt(stack++));
  sint max_hp = GetStackInt(stack++);

  auto chara_data = save_data->m_user_data_manager.GetCharaDataPtr(chara_id);

  chara_data->m_chara_hp_gage.m_max = static_cast<f32>(max_hp);
  chara_data->m_chara_hp_gage.SetFillRate(1.0f);
  return true;
}

static bool _SET_CHARA_DEFENCE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();
  if (save_data == nullptr)
  {
    return false;
  }

  ECharacterID chara_id = static_cast<ECharacterID>(GetStackInt(stack++));
  sint defense = GetStackInt(stack++);

  auto chara_data = save_data->m_user_data_manager.GetCharaDataPtr(chara_id);

  chara_data->m_defense = defense;
  return true;
}

static bool _PLACE_PARTS_NAME_STRCMP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GOTO_USE_ITEM2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DBG_SET_ANALYZE_FLAG(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ATRAMIRIA_ON_OFF(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _ADD_YARIKOMI_MEDAL(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();
  if (save_data == nullptr)
  {
    return false;
  }

  save_data->m_user_data_manager.AddYarikomiMedal(GetStackInt(stack++));
  return true;
}

static bool _SET_MAP_EFFECT_ID(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _GET_MAP_EFFECT_ID(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _DNG_FLOOR_INIT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  DungeonFloorInit();
  return true;
}

static bool _DNG_FLOOR_FINISH(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  DungeonFloorFinish();
  return true;
}

static bool _CLEAR_RND_STONE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  AutoMapGen.ClearRandomStone();
  return true;
}

static bool _GET_FLOOR_STATUS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_FLOOR_STATUS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _AMG_GET_ATTR_STATUS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _SET_NEAR_DIST(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  sint chara_index = GetStackInt(stack++);
  f32 near_dist = GetStackFloat(stack++);

  CCharacter2* chara = GetCharacter(chara_index);
  if (chara == nullptr)
  {
    return false;
  }

  chara->SetFadeFlag(true);
  chara->SetNearDist(near_dist);

  return true;
}

static bool _SET_KEEP_TIME(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  EdEventInfo.m_keep_time = GetStackFloat(stack++);
  return true;
}

static bool _GET_KEEP_TIME(RS_STACKDATA* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  if (stack_count != 1)
  {
    return false;
  }

  SetStack(stack++, EdEventInfo.m_keep_time);
  return true;
}

static bool _GET_DOOR_PARTS_ID(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _CHECK_EQUIP_CHANGE(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  CheckEquipChange(ECharacterID::Monica);
  return true;
}

static bool _ADD_HP_RATE2(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();
  if (save_data == nullptr)
  {
    return false;
  }

  auto chara_id = static_cast<ECharacterID>(GetStackInt(stack++));
  f32 delta = GetStackFloat(stack++);
  save_data->m_user_data_manager.AddHp_Rate(chara_id, delta);
  return true;
}

static bool _DNG_EFFECT_ALL_CLEAR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _AUTO_CHANGE_BGM_VOL(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _UDATA_GET_WHP(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();
  if (save_data == nullptr)
  {
    return false;
  }

  auto chara_id = static_cast<ECharacterID>(GetStackInt(stack++));
  sint gauge_index = GetStackInt(stack++);
  sint max_whp;
  sint current_whp = save_data->m_user_data_manager.GetWhp(chara_id, gauge_index, &max_whp);

  switch (stack_count)
  {
    case 3:
      SetStack(stack++, current_whp);
      return true;
    case 4:
      SetStack(stack++, current_whp);
      SetStack(stack++, max_whp);
      return true;
    default:
      return false;
  }
}

static bool _UDATA_ADD_WHP(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();
  if (save_data == nullptr)
  {
    return false;
  }

  auto chara_id = static_cast<ECharacterID>(GetStackInt(stack++));
  sint gauge_index = GetStackInt(stack++);
  sint delta = GetStackInt(stack++);
  save_data->m_user_data_manager.AddWhp(chara_id, gauge_index, delta);
  return true;
}

static bool _UDATA_GET_ABS(RS_STACKDATA* stack, sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();
  if (save_data == nullptr)
  {
    return false;
  }

  auto chara_id = static_cast<ECharacterID>(GetStackInt(stack++));
  sint gauge_index = GetStackInt(stack++);
  sint max_abs;
  sint current_abs = save_data->m_user_data_manager.GetAbs(chara_id, gauge_index, &max_abs);

  switch (stack_count)
  {
    case 3:
      SetStack(stack++, current_abs);
      return true;
    case 4:
      SetStack(stack++, current_abs);
      SetStack(stack++, max_abs);
      return true;
    default:
      return false;
  }
}

static bool _UDATA_ADD_ABS(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();
  if (save_data == nullptr)
  {
    return false;
  }

  auto chara_id = static_cast<ECharacterID>(GetStackInt(stack++));
  sint gauge_index = GetStackInt(stack++);
  sint delta = GetStackInt(stack++);
  save_data->m_user_data_manager.AddAbs(chara_id, gauge_index, delta);
  return true;
}

static bool _DNG_CREATE_EFFECT(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _LEAVE_MONICA_ITEM_CHECK(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  LeaveMonicaItemCheck();
  return true;
}

static bool _PAUSE_ENABLE_FLAG(RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  PauseEnable(common::bits::to_bool(GetStackInt(stack++)));
  return true;
}

static bool _FORCE_BOOT_TOUR(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  auto save_data = GetSaveData();
  if (save_data == nullptr)
  {
    return false;
  }

  save_data->ForceBootTour(save_data->m_unk_field_1A14, true);
  return true;
}

static bool _MT_TEST(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static bool _TEST(MAYBE_UNUSED RS_STACKDATA* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  todo;
  return true;
}

static RS_TAG_PARAM ext_func[]
{
  _GET_PADON,                     0,
  _GET_PADDOWN,                   1,
  _GET_PADUP,                     2,
  _GET_APAD,                      3,
  _GOTO_INTERIOR,                 6,
  _INITIALIZE,                    8,
  _GOTO_OUTSIDE,                  7,
  _LOAD_CHARA,                    9,
  _CHARA_ACTIVE,                  10,
  _CLEAR_STACK,                   11,
  _ASSIGN_STACK,                  12,
  _SET_FLAG,                      13,
  _GET_FLAG,                      14,
  _SET_CNT,                       15,
  _GET_CNT,                       16,
  _SET_CURRENT_DIR,               17,
  _DELETE_CHARA,                  18,
  _LOAD_MOTION,                   19,
  _MAP_JUMP,                      20,
  _SET_RAIN,                      21,
  _DEL_EXT_MOTION,                22,
  _SET_MARKER,                    23,
  _SET_WORLD_COORD,               24,
  _FINISH,                        25,
  _GET_DUN_WORLD_COORD,           26,
  _LOAD_IMG,                      27,
  _DEL_IMG,                       28,
  _SET_DNG_MAP,                   29,
  _LOAD_ITEM,                     30,
  _GOTO_USE_ITEM,                 31,
  _SET_LOCAL_FLAG,                32,
  _GET_LOCAL_FLAG,                33,
  _GOTO_SELECT_PARTY,             34,
  _SET_LOADBG_FILE,               35,
  _CHECK_LOADBG_FILE,             36,
  _GET_TB_ITEMNO,                 37,
  _SET_TB_STATUS,                 38,
  _SET_TB_ANGLE,                  39,
  _ADD_ITEM,                      40,
  _GET_ITEM_TYPE,                 41,
  _GET_ITEM_SPACE,                42,
  _GET_ADJUST_POLYGON_SCALE,      43,
  _LOAD_MOVIE,                    44,
  _INIT_LOCAL_CNT,                45,
  _SET_CROSSFADE,                 46,
  _SET_TIME,                      47,
  _SET_ACTIVE_LIGHT,              48,
  _SET_PAKU_ANIM,                 49,
  _RESET_PAKU_ANIM,               50,
  _TRG_PAKU_ANIM,                 51,
  _RESET_CAMERA,                  52,
  _GET_ACTIVE_CHR_NO,             53,
  _SET_ACTIVE_CHR_NO,             54,
  _DNG_SET_FLOOR_ID,              55,
  _DNG_GET_FLOOR_ID,              56,
  _SET_PAKU_MOTION,               57,
  _RESET_PAKU_MOTION,             58,
  _TRG_PAKU_MOTION,               59,
  _SET_BG_COLOR,                  60,
  _GOTO_DNG_MAP,                  61,
  _GOTO_DNG,                      62,
  _GOTO_EDIT,                     63,
  _GET_MENU_PARAM,                64,
  _LOAD_CHARA_NPC,                65,
  _AUTO_SET_TREASURE_BOX,         66,
  _AUTO_SET_MONSTER,              67,
  _LOAD_DUNGEON_MAP_FILE,         68,
  _LOAD_MONSTER_FILE,             69,
  _GET_NPC_STATUS,                70,
  _SET_NPC_STATUS,                71,
  _GET_NOW_PARTY_CHARA,           72,
  _SET_LOCAL_CNT,                 73,
  _GET_LOCAL_CNT,                 74,
  _GET_LOCAL_CNT2,                75,
  _GET_TRAIN_NPC_POS,             76,
  _GOTO_DRAW_CHAPTER,             77,
  _SET_PROJECTION,                78,
  _GET_PROJECTION,                79,
  _SET_FADE_IN,                   80,
  _SET_FADE_OUT,                  81,
  _DNG_DEBUG_COMMAND,             82,
  _CD_SEEK,                       83,
  _GET_ROT_LOOK_POS,              84,
  _SET_MOTION_BLUR,               85,
  _LOAD_SCRIPT,                   86,
  _SET_TALK_CAMERA,               87,
  _HIT_EFFECT,                    88,
  _COPY_CHARA,                    89,
  _GET_START_BUTTON,              90,
  _MOVE_INTERIOR,                 91,
  _GET_MONSTER_TALK_DATA,         92,
  _FUNC_POINT_SHOW,               93,
  _GET_NOW_MAP_NO,                94,
  _GET_NOW_SUBMAP_NO,             95,
  _GET_OLD_MAP_NO,                96,
  _GET_OLD_SUBMAP_NO,             97,
  _SET_RAIN_CHARA_NO,             98,
  _GET_EDIT_PARTS_POS,            99,
  _GET_CHARA_POS,                 100,
  _GET_CHARA_TALK_POS,            101,
  _TURN_CHARA,                    102,
  _SET_CHARA_POS,                 103,
  _SET_CHARA_ROT,                 104,
  _GET_CHARA_ROT,                 105,
  _SET_MOTION,                    106,
  _SET_STEP,                      107,
  _SET_TEX_ANIM,                  108,
  _SET_SCALE,                     109,
  _SET_REFERENCE,                 110,
  _DEL_REFERENCE,                 111,
  _SHADOW_CLIP_OFF,               112,
  _GET_COORDINATE_ANGLE,          113,
  _GET_CHARA_WIDTH,               114,
  _GET_CHARA_HEIGHT,              115,
  _GET_CHARA_WEIGHT,              116,
  _SET_CHARA_SHOW,                117,
  _GET_CHARA_SHOW,                118,
  _CHARA_DA_ENABLE,               119,
  _GET_MOT_NOW_WAIT,              120,
  _CHECK_MOTION_END,              121,
  _ACTCHR_SET_MOTION,             122,
  _SET_CHARA_EX_SOUNDID,          123,
  _ACTCHR_SOUND_INFO_COPY,        124,

  _MES_MAKE,                      192,
  _MES_CLOSE,                     193,
  _MES_NEXTPAGE,                  194,
  _SET_MES_AUTOSET,               195,
  _SET_MES_SHIPPO,                196,
  _SET_MES_POS,                   197,
  _SET_MES_DRAWSPEED,             198,
  _SET_MES_CURSOR,                199,
  _SET_MES_OKURI,                 203,
  _SET_MES_FUKIDASHI,             204,
  _CHECK_MES_COMPLETE,            200,
  _CHECK_MES_WAIT,                201,
  _CHECK_MES,                     202,
  _SET_MES_WIN_FLAG,              205,
  _SET_CAMERA_POS,                206,
  _GET_CAMERA_POS,                207,
  _SET_CAMERA_REF,                208,
  _GET_CAMERA_REF,                209,
  _SET_CAMERA_SPEED,              210,
  _CAMERA_STEP,                   211,
  _SET_MES_WINDOW_MODE,           212,
  _SET_MES_PRESET,                213,
  _SET_MES_ITEM_DIRECT,           214,
  _SET_MES_ITEM,                  215,
  _SET_MES_VALUE,                 216,
  _GET_MES_STATUS,                217,
  _GET_PARTY_CHARA_MES_NO,        218,
  _MES_SET_BUFF,                  219,
  _GET_MES_WINDOW_MODE,           220,
  _GET_MES_VOICE,                 222,
  _SET_MES_QUESTION_GYOU,         223,
  _GET_MES_QUESTION_GYOU,         224,
  _SET_MES_CLOSE_CNT,             225,
  _SET_MES_ETC,                   226,
  _GET_MES_ETC,                   227,
  _LOAD_MES,                      228,
  _MES_SE_PLAY,                   229,
  _SET_MES_STR,                   230,
  _GET_MES_OKURI,                 231,

  _ASQ_INIT,                      300,
  _ASQ_SYNC_CHARA,                301,
  _ASQ_SET_POS,                   302,
  _ASQ_MOVE,                      303,
  _ASQ_MOVE_STEP,                 304,
  _ASQ_ROT_REF,                   305,
  _ASQ_CLEAR_ROT,                 307,
  _ASQ_WAIT_ROT,                  308,
  _ASQ_ROT_MOVE,                  309,
  _ASQ_ROT_ANGLE,                 306,
  _ASQ_SET_ROT,                   310,
  _ASQ_DELAY_ROT,                 311,
  _ASQ_CHECK,                     312,
  _ASQ_MOTION_TRG,                313,
  _ASQ_MOTION_PLAY,               314,
  _ASQ_MOTION_STOP,               315,
  _ASQ_MOTION_NEXT,               316,
  _ASQ_ANIME_TRG,                 317,
  _ASQ_ANIME,                     318,
  _ASQ_SE_PLAY,                   319,

  _IMG_SET_DRAW,                  320,
  _IMG_SET_GET,                   321,
  _IMG_SET_PUT,                   322,
  _IMG_SET_NAME,                  323,
  _IMG_SET_MOVE,                  324,
  _IMG_SET_FADE,                  325,
  _IMG_SET_COLOR,                 326,

  _SPRITE_INIT,                   350,
  _SPRITE_SET_DRAW,               351,
  _SPRITE_SET_TYPE,               352,
  _SPRITE_SET_TEXTURE,            353,
  _SPRITE_SET_POS,                354,
  _SPRITE_SET_PUTSIZE,            355,
  _SPRITE_SET_UVSIZE,             356,
  _SPRITE_SET_COLOR,              357,
  _SPRITE_SET_SCALE,              358,
  _SPRITE_SET_ALPHAB,             359,

  _CMRS_CHECK,                    400,
  _CMRS_INIT,                     401,
  _CMRS_PRDELAY,                  402,
  _CMRS_SET_POS,                  403,
  _CMRS_SET_REF,                  404,
  _CMRS_MOVE,                     405,
  _CMRS_MOVE_REF,                 406,
  _CMRS_INIT_PAS,                 407,
  _CMRS_SET_PAS_FRM,              408,
  _CMRS_ADD_PAS,                  409,
  _CMRS_START_PAS,                410,
  _CMRS_PR_SLOWING,               423,
  _CMRS_PR_KEEP,                  427,
  _CMRS_PR_RETURN,                428,
  _CMRS_AHDDELAY,                 411,
  _CMRS_SET_ANGLE,                412,
  _CMRS_SET_HEIGHT,               413,
  _CMRS_SET_DIST,                 414,
  _CMRS_SET_AHD,                  415,
  _CMRS_MOVE_AHD,                 416,
  _CMRS_SYNC_OBJ,                 617,
  _CMRS_RELEASE_OBJ,              618,
  _CMRS_AHD_SLOWING,              424,
  _CMRS_AHD_KEEP,                 425,
  _CMRS_AHD_RETURN,               426,
  _CMRS_FADE_DELAY,               419,
  _CMRS_FADE_INIT,                420,
  _CMRS_FADE_IN,                  421,
  _CMRS_FADE_OUT,                 422,
  _CMRS_QUAKE_DELAY,              429,
  _CMRS_QUAKE,                    430,
  _CMRS_MOVE2,                    431,
  _CMRS_MOVE_AHD2,                432,
  _CMRS_CHARA_DELAY,              433,
  _CMRS_CHARA_ATTACH,             434,
  _CMRS_MOVE_POS,                 435,
  _CMRS_QUAKE2,                   436,

  _OBJS_CHECK,                    450,
  _OBJS_INIT,                     451,
  _OBJS_SYNC_OBJ,                 452,
  _OBJS_POS_DELAY,                453,
  _OBJS_SET_POS,                  454,
  _OBJS_MOVE,                     455,
  _OBJS_MOVE2,                    488,
  _OBJS_INIT_PAS,                 456,
  _OBJS_SET_PAS_FRM,              457,
  _OBJS_ADD_PAS,                  458,
  _OBJS_START_PAS,                459,
  _OBJS_JUMP,                     473,
  _OBJS_SET_EOH_FRAME_POS,        483,
  _OBJS_ADD_POS,                  484,
  _OBJS_ATTACH_CAMERA,            489,
  _OBJS_ROT_DELAY,                460,
  _OBJS_SET_ROT,                  461,
  _OBJS_ROTATION,                 462,
  _OBJS_ROTATION2,                490,
  _OBJS_REFERENCE,                463,
  _OBJS_MOTION_DELAY,             464,
  _OBJS_SET_MOTION,               465,
  _OBJS_NEXT_MOTION,              466,
  _OBJS_MOTION_WAIT,              467,
  _OBJS_SET_STEP,                 482,
  _OBJS_CHANGE_STEP,              469,
  _OBJS_SEQ_MOT_TRG,              468,
  _OBJS_SEQ_MOT_TRG_WAIT,         472,
  _OBJS_RESET_MOTION,             476,
  _OBJS_SET_MOTION_NOW_TIME,      479,
  _OBJS_SET_MOTION_WAIT_TIME,     481,
  _OBJS_TEXA_DELAY,               470,
  _OBJS_TEX_ANIME,                471,
  _OBJS_COLOR_DELAY,              474,
  _OBJS_SET_COLOR,                475,
  _OBJS_SCALE_DELAY,              477,
  _OBJS_SET_SCALE,                478,
  _OBJS_SE_DELAY,                 485,
  _OBJS_SE_PLAY,                  486,
  _OBJS_RESET_DA_POSITION,        487,
  _OBJS_NORMAL_DRIVE,             491,

  _GET_CONTENTS_POS,              501,
  _GET_BPOT_POS,                  502,
  _GET_BPOT_STATUS,               503,
  _GET_PERSON_STATUS,             504,
  _GET_CONTROL_CHRID,             505,
  _GET_BEFORE_CAMERA_POS,         506,
  _GET_BEFORE_CAMERA_REF,         507,
  _SET_CAMERA_NEXT_REF,           508,
  _GOTO_MENU,                     509,
  _GET_MENU_STATUS,               510,
  _LOAD_EQUIP,                    511,
  _GET_EQUIP_ITEMNO,              512,
  _SET_TIME_STEP_ENABLE,          513,
  _SET_DOOR_MATERIAL,             514,
  _INIT_DRAMA_SCENE,              515,
  _SET_ACTIVE_CMRID,              516,
  _SET_BEFORE_CMRID,              517,
  _DNGMAP_LOAD,                   519,
  _DNGMAP_DELETE,                 520,
  _DNGMAP_MOVE_PIECE,             521,
  _DNGMAP_ONOFF,                  522,
  _DNGMAP_SET_FADE,               523,
  _GET_BEFORE_CAMERA_NEXT_POS,    524,
  _GET_BEFORE_CAMERA_NEXT_REF,    525,
  _SET_CAMERA_NEXT_POS,           526,
  _CHK_INTERSECTION_POINT,        527,
  _SET_FCAMERA_FOLLOW,            528,
  _SET_FCAMERA_FOLLOW_A,          529,
  _SET_FCAMERA_FOLLOW_OFS,        530,
  _SET_FCAMERA_FOLLOW_FLAG,       531,
  _FCAMERA_STEP,                  532,
  _SET_FCAMERA_ANGLE,             533,
  _SET_FCAMERA_HEIGHT,            534,
  _SET_FCAMERA_DIST,              535,
  _GET_REF_ANGLE,                 536,
  _DNG_SET_STAGE_ID,              537,
  _DNG_GET_STAGE_ID,              538,
  _SET_CAMERA_CTRL,               539,
  _GET_FCAMERA_ANGLE,             540,
  _GET_FCAMERA_HEIGHT,            541,
  _GET_FCAMERA_DIST,              542,
  _GET_INVENTION_ID,              543,
  _FUNCTION_MAP_JUMP,             544,
  _FUNCTION_DOOR_MODE,            545,
  _GET_MONEY,                     546,
  _ADD_MONEY,                     547,
  _GET_ITEM_NUM,                  548,
  _CHECK_BUTTON,                  549,
  _GET_LANGUAGE,                  550,
  _CHECK_INVENT_ITEM,             551,
  _SET_AI,                        552,
  _CHECK_INVENT_PHOTO,            553,
  _GET_PHOTO_NUM,                 554,
  _SET_CONTENTS_ETC,              555,
  _SET_STATUS,                    556,
  _GOTO_SUBGAME,                  557,
  _SET_GYORACE_ETC,               558,
  _GET_GYORACE_ETC,               559,
  _SET_SAVEDATA_ETC,              560,
  _GET_SAVEDATA_ETC,              561,
  _DEL_MONSTER,                   562,
  _SET_MENU_ETC,                  563,
  _GET_MENU_ETC,                  564,
  _GET_ANALYZE,                   565,
  _GET_DIORAMA_PERCENT,           566,
  _GEORAMA_FUNC,                  567,
  _GET_CHARA_ID,                  568,
  _SET_LOADBG_FILE_MONS_TALK,     569,
  _LOAD_MES_MONS_TALK,            570,
  _GOTO_EDITMODE,                 571,
  _GET_CHAPTER,                   572,
  _GET_NPC_TRAIN_ETC,             573,
  _REGISTER_VILLAGER,             574,
  _EYE_VIEW_DRAW_ON_OFF,          575,
  _SET_QUEST_ETC,                 576,
  _GET_QUEST_ETC,                 577,
  _CHK_INTERSECTION_POINT_PIPE,   578,
  _GET_OLD_INTERIOR_MAP_NO,       579,
  _SET_EVENT_DATA,                581,
  _STOPWATCH,                     582,
  _SET_FUNC_ETC,                  583,
  _GET_FISHINGTOURNAMENT_ETC,     584,
  _SET_CHARA_FAR_DIST,            585,
  _SET_MODEL_LIGHT_SWITCH,        586,
  _SET_MODEL_LIGHT_COLOR,         587,
  _GET_OMAKE_FLAG,                588,
  _SET_WIND,                      589,
  _SET_OMAKE_FLAG,                590,

  _SND_INIT_PORT,                 600,
  _SND_LOAD_SOUND,                601,
  _SND_SE_PLAY,                   602,
  _GET_SND_ID,                    603,
  _SND_SE_PAUSE,                  604,
  _SND_SE_STOP,                   605,
  _SND_SET_SE_VOL,                606,
  _SND_SET_SE_PAN,                607,
  _SND_SET_SE_PITCH,              608,
  _SND_SE_ALL_STOP,               609,
  _LOAD_BGM,                      610,
  _PLAY_BGM,                      611,
  _STOP_BGM,                      612,
  _STREAM_OPEN,                   613,
  _STREAM_PLAY,                   614,
  _STREAM_STOP,                   615,
  _STREAM_STANDBY,                616,
  _STREAM_GET_STATUS,             619,
  _GET_SYS_SND_ID,                620,
  _STREAM_OPEN_CHECK,             621,
  _LOAD_SE_ENV,                   622,
  _PLAY_ENV_BGM,                  623,
  _SYS_SE_PLAY,                   624,
  _INIT_SE_SRC,                   625,
  _INIT_SE_ENV,                   626,
  _INIT_SE_BAS,                   627,
  _LOAD_SE_SRC,                   628,
  _LOAD_SE_FOOT,                  629,
  _LOAD_SE_DOOR,                  630,
  _LOAD_SE_BOX,                   631,
  _LOAD_SE_BATTLE,                632,
  _SND_DELETE_PORT,               633,
  _STOP_ENV_BGM,                  634,
  _FADE_IN_BGM,                   635,
  _FADE_OUT_BGM,                  636,
  _SET_BGM_VOL,                   637,
  _SND_SET_REVERB,                638,
  _SND_SET_ENV_VOL,               639,
  _STREAM_SILENT_CHECK,           640,
  _AUTO_CHANGE_ENV,               641,
  _BGM_LOAD_CANCEL,               642,
  _SOUND_LOAD_CANCEL,             643,
  _BGM_LOAD_ENABLE,               644,
  _SOUND_LOAD_ENABLE,             645,
  _LOAD_SE_BASE,                  646,
  _LOAD_SOUND,                    647,
  _STREAM_CLOSE,                  648,
  _STREAM_OPEN2,                  649,
  _LOAD_BGM_PACK,                 650,
  _GET_BGM_NO,                    651,
  _GET_MASTER_VOL,                652,
  _SET_MASTER_VOL,                653,
  _GET_BTL_BGM_VOL,               654,
  _SET_BTL_BGM_VOL,               655,
  _SND_IN_REVERB,                 656,
  _SND_STOP_SRC,                  657,
  _SND_PAUSE_BGM,                 658,
  _STREAM_OPEN3,                  659,
  _GET_ACTIVE_BGM_STATUS,         660,
  _SET_ACTIVE_BGM_STATUS,         661,
  _GET_BGM_STATUS_NOW_NO,         662,
  _GET_SE_STATUS,                 663,
  _SE_ALL_STOP,                   664,
  _SOUND_ALL_STOP,                665,
  _BGM_PLAY_CANCEL,               666,
  _BGM_PLAY_ENABLE,               667,
  _GET_DEF_BGM_NO,                668,
  _SET_MOVIE_CC,                  669,
  _REGISTER_VILLAGER2,            670,
  _SET_FISHINGTOURNAMENT_ETC,     671,

  _EOH_SYNC_CHARA,                700,
  _EOH_SYNC_OBJ,                  701,
  _EOH_SET_POS,                   702,
  _EOH_SET_ROT,                   703,
  _EOH_GET_POS,                   704,
  _EOH_GET_ROT,                   705,
  _EOH_SET_MOTION,                706,
  _EOH_SET_STEP,                  707,
  _EOH_SET_TEX_ANIM,              708,
  _EOH_SET_SCALE,                 709,
  _EOH_SET_SHOW,                  710,
  _EOH_GET_SHOW,                  711,
  _EOH_SET_FRAME_SHOW,            712,
  _EOH_SET_SHADOW,                713,
  _EOH_SET_TRANSLATE,             714,
  _EOH_SYNC_SPRITE,               715,
  _EOH_SET_FOOT_SOUND_ID,         716,
  _EOH_SET_FRAME_STATUS,          717,
  _EOH_GET_FRAME_POS,             718,
  _EOH_SET_SOUND_ID,              719,
  _EOH_GET_FRAME_STATUS,          720,
  _EOH_SYNC_CHROBJ,               721,
  _EOH_SET_FADE_FLAG,             722,
  _EOH_RESET_DA_POSITION,         723,
  _EOH_SET_SHADOW_FRAME_STATUS,   724,
  _EOH_SYNC_GEOSTONE,             725,
  _EOH_SYNC_SEARCH_CHARA,         726,
  _EOH_NORMAL_DRIVE,              727,
  _EOH_SYNC_EDIT_OBJ,             728,
  _EOH_SET_FRAME_ALPHA,           729,
  _EOH_SYNC_FUNCP,                730,
  _EOH_SET_FOOT_SE_ID,            731,
  _EOH_SYNC_DOOR_PARTS,           732,

  _SPHIDA_INIT,                   750,
  _SPHIDA_SET_UP,                 751,
  _SPHIDA_SET_PLAY_FLAG,          752,
  _SPHIDA_SET_MINIMAP_FLAG,       753,
  _SPHIDA_SET_MM_LINE_FLAG,       754,
  _SPHIDA_SET_MM_LINE_POS,        755,
  _SPHIDA_SET_PIN_POS,            756,
  _SPHIDA_GET_PIN_POS,            757,
  _SPHIDA_SET_BALL_POS,           758,
  _SPHIDA_GET_BALL_POS,           759,
  _SPHIDA_SET_PIN_COL,            760,
  _SPHIDA_GET_PIN_COL,            761,
  _SPHIDA_SET_BALL_COL,           762,
  _SPHIDA_GET_BALL_COL,           763,
  _SPHIDA_SET_PAR_COUNT,          764,
  _SPHIDA_GET_PAR_COUNT,          765,
  _SPHIDA_GET_MINI_LEVEL,         766,
  _SPHIDA_GET_TEXB,               767,
  _SPHIDA_SET_STATUS_FLAG,        768,
  _SPHIDA_RESET_POWGAGE,          769,
  _SPHIDA_START_POWGAGE,          770,
  _SPHIDA_TRIGGER_POWGAGE,        771,
  _SPHIDA_GET_SHOT_POW,           772,
  _SPHIDA_GET_POWGAGE_CODE,       773,
  _SPHIDA_SET_POWGAGE_SAFE_LEVEL, 774,
  _SPHIDA_GET_CLUB_DEF,           775,
  _SPHIDA_SET_SPIN_MARK_POS,      776,
  _SPHIDA_SET_CLUB_NO,            777,
  _SPHIDA_CALC_CARRY,             778,
  _SPHIDA_GET_PG_CURSOR_POS,      779,
  _SPHIDA_SET_COL_MODEL,          780,
  _SPHIDA_GET_PRIZE,              781,
  _SPHIDA_SET_LAST_CHALLENGE,     782,
  _SPHIDA_GET_LAST_CHALLENGE,     783,
  _SPHIDA_GET_OMAKE_MODE,         784,
  _SPHIDA_SET_NOW_HOLE,           785,
  _SPHIDA_GET_NOW_HOLE,           786,
  _SPHIDA_SET_SCORE,              787,
  _SPHIDA_GET_SCORE,              788,

  _ZERO_VECTOR,                   1000,
  _NORMAL_VECTOR,                 1001,
  _COPY_VECTOR,                   1002,
  _ADD_VECTOR,                    1003,
  _SUB_VECTOR,                    1004,
  _SCALE_VECTOR,                  1005,
  _DIV_VECTOR,                    1006,
  _DIST_VECTOR,                   1007,
  _DIST_VECTOR2,                  1008,
  _SQRT,                          1009,
  _ATAN2F,                        1010,
  _ANGLE_CMP,                     1011,
  _ANGLE_LIMIT,                   1012,
  _GET_RAND,                      1013,
  _LINE_POINT_DIST,               1014,
  _CREATE_SWORD_EFFECT,           1015,
  _DELETE_SWORD_EFFECT,           1016,
  _SWORD_EFFECT_COLOR,            1017,
  _SWORD_EFFECT_ADD_POINT,        1018,
  _ADD_CHARA_POS,                 1019,
  _ADD_CHARA_ROT,                 1020,
  _POST_TREASURE_BOX,             1021,
  _GET_PARTS_ORIGIN,              1022,
  _CTRLC_STEP,                    1023,
  _CTRLC_SET_ROTATE,              1024,
  _CTRLC_MOVE_CAMERA,             1025,
  _CTRLC_SET_ROT_CANCEL,          1026,
  _CTRLC_MOVE_RANGE,              1027,
  _GET_NEAR_TBOX_POS,             1028,
  _CONV_CHRNO_S2L,                1029,
  _SWE_INIT,                      1030,
  _SWE_SET_COLOR,                 1031,
  _SWE_SET_TEXTURE,               1032,
  _SWE_START_EFFECT,              1033,
  _SET_CHARA_TYPE,                1034,
  _GET_EVENT_DATA,                1035,
  _DNG_SET_PREV_FLOOR,            1036,
  _DNG_GET_PREV_FLOOR,            1037,
  _DNG_SET_FAST_FLOOR,            1038,
  _SET_FLOOR_INFO,                1039,
  _GET_FLOOR_INFO,                1040,
  _GET_NEXT_FLOOR,                1041,
  _PAD_AUTO_REPEAT_OFF,           1042,
  _PAD_SET_AUTO_REPEAT,           1043,
  _DNG_PAUSE,                     1044,
  _DNG_CHECK_PAUSE,               1045,
  _DNG_RESET_TIMER,               1046,
  _DNG_GET_TIMER,                 1047,
  _LOAD_SKIN,                     1048,
  _CHK_CAMERA_COL,                1049,
  _GET_PARTS_FUNC_POS,            1050,
  _RANDOM_CIRCLE_GET_POS,         1051,
  _RANDOM_CIRCLE_OFF,             1052,
  _DNG_XCHG_MAP_LIGHT,            1053,
  _GEOSTONE_ANIME_OFF,            1054,
  _GEOSTONE_SET_FLAG,             1055,
  _GEOSTONE_SET_REFERENCE,        1056,
  _GEOSTONE_DEL_REFERENCE,        1057,
  _GET_ROBO_MOVE_TYPE,            1058,
  _SET_EXIT_FLAG,                 1059,
  _GET_EXIT_FLAG,                 1060,
  _GET_E3_VERSION,                1061,
  _CHK_PAD_CTRL,                  1062,
  _CTRLC_STAY,                    1063,
  _BSCN_SET_BLIGHT_RATE,          1064,
  _GET_RND_CIRCLE_TRAPID,         1065,
  _SET_RND_CIRCLE_STATUS,         1066,
  _SET_STATUSBAR_SHOW,            1067,
  _SET_PULL_ITEM,                 1068,
  _MENU_CHARA_CHANGE,             1069,
  _GET_EVENT_INFO_SNDID,          1070,
  _GET_PARTS_POS,                 1071,
  _CANCEL_DRAMA_SCENE,            1072,
  _GET_RNDC_MOT_NOWT,             1073,
  _SET_CHARA_MOT_NOWT,            1074,
  _CHARA_NORMAL_DRIVE,            1075,
  _CHARA_RESET_DA,                1076,
  _DNG_SETUP_MAIN_UNIT,           1077,
  _JOIN_PARTY_MEMBER,             1078,
  _SET_CHARA_CHANGE_FLAG,         1079,
  _SET_CHARA_CHANGE_MASK,         1080,
  _CHANGE_DIR,                    1081,
  _SUB_ITEM,                      1082,
  _SET_CHARA_EQUIP,               1083,
  _LOAD_PACK_FILE,                1084,
  _SET_BIT_CTRL,                  1085,
  _GET_BIT_CTRL,                  1086,
  _LOAD_ARG,                      1087,
  _GET_ITEM_HAVE_NUM,             1088,
  _SET_SKIP_BUTTON,               1089,
  _SET_SKIP_FCOL,                 1090,
  _GET_DEBUG_MODE,                1091,
  _GET_MAP_TYPE,                  1092,
  _DNG_COLLISION_ALL_CLR,         1093,
  _SET_MAP_DRAW,                  1094,
  _CHECK_MC_LOAD,                 1095,
  _SET_NOW_MAP_NO,                1096,
  _GET_TBOX_PARAM,                1097,
  _CANCEL_LOAD_VILLAGER,          1098,
  _CANCEL_NOW_LOADING,            1099,

  _ESM_INITIALIZE,                1100,
  _ESM_INIT_FIX,                  1101,
  _ESM_CLEAR,                     1102,
  _ESM_LOAD_BASE,                 1103,
  _ESM_CREATE,                    1104,
  _ESM_FINISH,                    1105,
  _ESM_DELETE,                    1106,
  _ESM_SET_VECT1,                 1107,
  _ESM_SET_VECT2,                 1108,
  _ESM_SET_TARGET_ID,             1109,
  _ESM_LOAD_BASE_PACK,            1110,
  _ESM_SET_VALUE,                 1111,

  _SET_CHARA_CONDITION,           1200,
  _ADD_WHP,                       1201,
  _ADD_HP_RATE,                   1202,
  _GET_TIME,                      1203,
  _CHECK_GET_ITEM_LIMIT,          1204,
  _CHECK_ITEM_OVER,               1205,
  _GET_NOW_LOOP_NO,               1206,
  _IS_CLEAR_DESTROY,              1207,
  _IS_CLEAR_PRACTICE,             1208,
  _IS_PLAY_SUB_GAME,              1209,
  _RESET_SUBJECT_COUNTER,         1210,
  _SCR_EFF_INIT_RASTER,           1211,
  _SCR_EFF_START_RASTER,          1212,
  _SCR_EFF_STOP_RASTER,           1213,
  _SET_MPCHARA_MOTION,            1214,
  _FUNC_POINT_POS,                1215,
  _CTRLC_ROT_BACK,                1216,
  _PARTS_NAME_STRCMP,             1217,
  _GET_TRIAL_VERSION,             1218,
  _SET_FLOOR_EPISODE,             1219,
  _FUNC_POINT_GET_POS,            1220,
  _FUNC_POINT_GET_ROT,            1221,
  _ACTCHR_SET_DEF_MOTION,         1222,
  _ADD_FUSION_POINT,              1223,
  _GET_DEBUG_FLAG,                1224,
  _MINIMAP_DOOR_ENABLE,           1225,
  _DNG_CHECK_BOSS_MAP,            1226,
  _DNG_RUN_EVENT,                 1227,
  _CHECK_ENABLE_CHARA_CHANGE,     1228,
  _INIT_SEPIA,                    1229,
  _START_SEPIA,                   1230,
  _END_SEPIA,                     1231,
  _COPY_MONS2SCNCHR,              1232,
  _UNLOCK_STACK,                  1233,
  _RESET_EVENT_TRG,               1234,
  _SET_CHARA_NO,                  1235,
  _GET_CHARA_NO,                  1236,
  _SEARCH_CHARA_NO,               1237,
  _GET_NEAR_RANDOM_STONE_POS,     1238,
  _INIT_MONO_FLASH,               1239,
  _START_MONO_FLASH,              1240,
  _END_MONO_FLASH,                1241,
  _DELETE_VILLAGER,               1242,
  _DNG_SET_WEATHER,               1243,
  _SET_CHARA_MAXHP,               1244,
  _SET_CHARA_DEFENCE,             1245,
  _PLACE_PARTS_NAME_STRCMP,       1246,
  _GOTO_USE_ITEM2,                1247,
  _DBG_SET_ANALYZE_FLAG,          1248,
  _ATRAMIRIA_ON_OFF,              1249,
  _ADD_YARIKOMI_MEDAL,            1250,
  _SET_MAP_EFFECT_ID,             1251,
  _GET_MAP_EFFECT_ID,             1252,
  _DNG_FLOOR_INIT,                1253,
  _DNG_FLOOR_FINISH,              1254,
  _CLEAR_RND_STONE,               1255,
  _GET_FLOOR_STATUS,              1256,
  _SET_FLOOR_STATUS,              1257,
  _AMG_GET_ATTR_STATUS,           1258,
  _SET_NEAR_DIST,                 1259,
  _SET_KEEP_TIME,                 1260,
  _GET_KEEP_TIME,                 1261,
  _GET_DOOR_PARTS_ID,             1262,
  _CHECK_EQUIP_CHANGE,            1263,
  _ADD_HP_RATE2,                  1264,
  _DNG_EFFECT_ALL_CLEAR,          1265,
  _AUTO_CHANGE_BGM_VOL,           1266,
  _UDATA_GET_WHP,                 1267,
  _UDATA_ADD_WHP,                 1268,
  _UDATA_GET_ABS,                 1269,
  _UDATA_ADD_ABS,                 1270,
  _DNG_CREATE_EFFECT,             1271,
  _LEAVE_MONICA_ITEM_CHECK,       1272,
  _PAUSE_ENABLE_FLAG,             1273,
  _FORCE_BOOT_TOUR,               1274,

  _MT_TEST,                       998,
  _TEST,                          999,

  nullptr,                        -1
};

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
    v = constants::vec4_zero;
  }

  for (auto& v : m_unk_field_100)
  {
    v = constants::vec4_zero;
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
  m_unk_field_10 = constants::vec4_zero;
  m_unk_field_20 = constants::vec4_zero;
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
  m_unk_field_50 = constants::vec4_zero;
  m_unk_field_60 = constants::vec4_zero;
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
  m_unk_field_50 = constants::vec4_zero;
  m_unk_field_60 = constants::vec4_zero;
  m_unk_field_78 = 0;
  m_unk_field_7C = 0;
  m_unk_field_80 = -1;
  m_unk_field_84 = 0;
  m_unk_field_90 = constants::vec4_zero;
  m_unk_field_AC[0] = '\0';
  m_unk_field_A8 = 0;
  m_unk_field_A4 = 0;
  m_unk_field_A0 = 0;
  m_unk_field_D0 = constants::vec4_zero;
  m_unk_field_E0 = constants::vec4_zero;
  m_unk_field_FC = 0;
  m_unk_field_F8 = 0;
  m_unk_field_F0 = 0;
  m_unk_field_100 = constants::vec4_zero;
  m_unk_field_110 = constants::vec4_zero;
  m_unk_field_120 = constants::vec4_zero;
  m_unk_field_130 = constants::vec4_zero;
  m_unk_field_140 = 0;
  m_unk_field_150 = constants::vec4_zero;
  m_unk_field_160 = constants::vec4_zero;
  m_unk_field_170 = constants::vec4_zero;
  m_unk_field_180 = 0;
  m_unk_field_1C0.Initialize();
  m_unk_field_190 = constants::vec4_zero;
  m_unk_field_1A0 = constants::vec4_zero;
  m_unk_field_1B0 = constants::vec4_zero;
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
    v = constants::vec4_zero;
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
  m_unk_field_10 = constants::vec4_zero;
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
  m_unk_field_70 = constants::vec4_zero;
  m_unk_field_80 = constants::vec4_zero;
  m_unk_field_120 = constants::vec4_zero;
  m_unk_field_B0 = constants::vec4_zero;
  m_unk_field_D0 = constants::vec4_zero;
  m_unk_field_F0 = 0;
  m_unk_field_C0 = constants::vec4_zero;
  m_unk_field_E0 = constants::vec4_zero;
  m_unk_field_8 = 0;
  m_unk_field_C = 0;
  m_unk_field_10 = 0;
  m_unk_field_14 = 0;
  m_unk_field_18 = 0;
  m_unk_field_1C = 0;
  m_unk_field_20 = 0;
  m_unk_field_24 = constants::u32_max;
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

// 0025FF40
void CRaster::SetParam(f32 f1, f32 f2, f32 f3)
{
  log_trace("CRaster::{}({}, {}, {})", __func__, f1, f2, f3);

  todo;
}

// 0025FF50
void CRaster::StartRaster(f32 f1, f32 f2, f32 f3, s32 i)
{
  log_trace("CRaster::{}({}, {}, {}, {})", __func__, f1, f2, f3, i);

  todo;
}

// 002600A0
void CRaster::StopRaster(f32 f1, f32 f2, f32 f3, s32 i)
{
  log_trace("CRaster::{}({}, {}, {}, {})", __func__, f1, f2, f3, i);

  todo;
}

// 002601F0
void CRaster::StepRaster()
{
  log_trace("CRaster::{}()", __func__);

  todo;
}

// 00260340
void CRaster::DrawRaster()
{
  log_trace("CRaster::{}()", __func__);

  todo;
}

// 00260640
void CScreenEffect::Step()
{
  log_trace("CScreenEffect::{}()", __func__);

  CRaster::StepRaster();
}

// 002608D0
void CScreenEffect::InitRaster(f32 f1, f32 f2, f32 f3)
{
  log_trace("CScreenEffect::{}({}, {}, {})", __func__, f1, f2, f3);

  todo;
}

// 00260930
void CScreenEffect::StartRaster(f32 f1, f32 f2, f32 f3, s32 i)
{
  log_trace("CScreenEffect::{}({}, {}, {}, {})", __func__, f1, f2, f3, i);

  CRaster::StartRaster(f1, f2, f3, i);
}

// 00260940
void CScreenEffect::StopRaster(f32 f1, f32 f2, f32 f3, s32 i)
{
  log_trace("CScreenEffect::{}({}, {}, {}, {})", __func__, f1, f2, f3, i);

  CRaster::StopRaster(f1, f2, f3, i);
}

// 00260950
void CScreenEffect::SetSepiaTexture(unkptr p1, unkptr p2)
{
  log_trace("CScreenEffect::{}({}, {})", __func__, fmt::ptr(p1), fmt::ptr(p2));

  todo;
}

// 00260970
void CScreenEffect::CaptureSepiaScreen()
{
  log_trace("CScreenEffect::{}()", __func__);

  todo;
}

// 00260BF0
void CScreenEffect::SetSepiaFlag(bool flag)
{
  log_trace("CScreenEffect::{}({})", __func__, flag);

  todo;
}

// 00260C10
void CScreenEffect::SetMonoFlashTexture(unkptr p1, unkptr p2)
{
  log_trace("CScreenEffect::{}({}, {})", __func__, fmt::ptr(p1), fmt::ptr(p2));

  todo;
}

// 00260C60
void CScreenEffect::CaptureMonoFlashScreen()
{
  log_trace("CScreenEffect::{}()", __func__);

  todo;
}

// 00260F30
void CScreenEffect::SetMonoFlashFlag(bool b1, bool b2)
{
  log_trace("CScreenEffect::{}({}, {})", __func__, b1, b2);

  if (m_unk_field_34 && m_unk_field_38)
  {
    m_unk_field_3C = b1;
  }
  else
  {
    m_unk_field_3C = false;
  }

  m_unk_field_40 = b2;
  m_unk_field_44 = 0;
  m_unk_field_48 = 0;
}

// 002901F0
void CMarker::Draw()
{
  log_trace("CMarker::{}()", __func__);

  m_cnt = std::max(m_cnt - 1, 0);
}

// 00290210
void CMarker::Set(sint i)
{
  log_trace("CMarker::{}({})", __func__, i);

  m_cnt = i;
}