#include "common/debug.h"
#include "common/log.h"

#include "CDngFloorManager.h"
#include "CScriptInterpreter.h"

set_log_channel("CDngFloorManager");

// 0037843C
static CDngFloorManager* _tree_dngmap{ nullptr };
// 00378440
static _UNKNOWNPOINTER dword_378440{ nullptr };
// 00378444
static mgCMemory* _tree_spi_stack{ nullptr };
// 00378448
static _UNKNOWNPOINTER dword_378448{ nullptr };
// 0037844C
static _UNKNOWNPOINTER dword_37844C{ nullptr };
// 00378450
static u16 _menu_dng_debug_glidcnt{ 0 };

// 002f8ce0
static bool _TREE_MAPINFO(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 002f8db0
static bool _GLID_INFO(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 002f8ea0
static bool _ROOT_INFO(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 002f8f00
static bool _ROOM_INFO(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 002f8fd0
static bool _ROOM_LINK(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 002f9050
static bool _ROOM_OPTION(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 002f91d0
static bool _ROOM_TEXNO(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 002f9160
static bool _ROOM_KEYROOM(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 002f9230
static bool _ROOM_FLOOR_INFO(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 002f93a0
static bool _ROOM_TITLE(SPI_STACK* stack, int stack_count)
{
  trace_script_call(stack, stack_count);

  todo;

  return true;
}

// 0035d010
static const std::array<SPI_TAG_PARAM, 12> tree_map_tag =
{
  "TREE_INFO",  _TREE_MAPINFO,
  "GI",         _GLID_INFO,
  "RT",         _ROOT_INFO,
  "RI",         _ROOM_INFO,
  "RI_LINK",    _ROOM_LINK,
  "RI_OP",      _ROOM_OPTION,
  "RI_TEX",     _ROOM_TEXNO,
  "RI_KEYROOM", _ROOM_KEYROOM,
  "RF_INFO",    _ROOM_FLOOR_INFO,
  "RI_TITLE",   _ROOM_TITLE,
  NULL, nullptr
};

// 002F8CC0
void CDngFloorManager::Initialize()
{
  log_trace("Initialize()");

  m_map_id = 0;
  m_unk_field_4 = nullptr;
  m_unk_field_8 = 0;
  m_unk_field_C = 0;
  m_unk_field_E = 0;
}

// 002f9420
void CDngFloorManager::AnalyzeFile(const char* script, int script_size, mgCMemory* tree_stack)
{
  log_trace("AnalyzeFile({}, {}, {})", fmt::ptr(script), script_size, fmt::ptr(tree_stack));

  _tree_dngmap = this;
  _tree_spi_stack = tree_stack;

  tree_stack->Align64();
  _menu_dng_debug_glidcnt = 0;

  CScriptInterpreter interpreter{ };
  interpreter.SetTag(tree_map_tag.data());
  interpreter.SetScript(script, script_size);
  interpreter.Run();

  _tree_spi_stack->Align64();

  RelationGlid();
}

// 002F94B0
void CDngFloorManager::LoadDataTable(s8 map_id, mgCMemory* tree_stack)
{
  log_trace("LoadDataTable({}, {})", map_id, fmt::ptr(tree_stack));

  if (tree_stack == nullptr)
  {
    return;
  }

  // FIXME: MAGIC ?
  if (map_id < 0 || 7 <= map_id)
  {
    map_id = 0;
  }

  Initialize();
  char cfg_file_name[0x60];
  sprintf(cfg_file_name, "menu/dngmap/dmap%d.cfg", map_id);

  // (sp + 0xC0 to sp + 0xA0C0)
  char file_buf_raw[0xA000];
  todo;
  //char *file_buf_aligned = MenuCalcBufAlignment(file_buf_raw);
  char* file_buf_aligned;
  

  usize file_size;
  todo;
  //LoadFile2(cfg_file_name, file_buf_aligned, &file_size, 0);

  if (file_size > 0)
  {
    AnalyzeFile(file_buf_aligned, file_size, tree_stack);
  }

  sprintf(cfg_file_name, "menu/dngmap/dflr%d.cfg", map_id);

  todo;
  //file_buf_aligned = MenuCalcBufAlignment(file_buf_raw);

  todo;
  //LoadFile2(cfg_file_name, file_buf_aligned, &file_size, 0);

  if (file_size > 0)
  {
    AnalyzeFile(file_buf_aligned, file_size, tree_stack);
  }

  char txt_file_name[0x40];
  sprintf(txt_file_name, "flrtitle%d.txt", map_id);

  todo;
  //file_size = LoadFileMenu(txt_file_name, file_buf_aligned, true);

  if (file_size > 0)
  {
    AnalyzeFile(file_buf_aligned, file_size, tree_stack);
  }
}

// 002F9610
GLID_INFO* CDngFloorManager::GetDngMapFloorGlidInfo(s8 floor)
{
  log_trace("GetDngMapFloorGlidInfo({})", floor);

  todo;
  return nullptr;
}

// 002F9690
bool CDngFloorManager::IsGeoStone(s8 floor)
{
  log_trace("IsGeoStone({})", floor);

  todo;
  return false;
}

// 002F96C0
bool CDngFloorManager::GetSphedaPrize(s8 floor, s32 i2, _UNKNOWNPOINTER p1, _UNKNOWNPOINTER p2)
{
  log_trace("GetSphedaPrize({}, {}, {}, {})", floor, i2, fmt::ptr(p1), fmt::ptr(p2));

  todo;
  return false;
}

// 002F9760
bool CDngFloorManager::GetSphedaPrize(s32 i2, _UNKNOWNPOINTER p1, _UNKNOWNPOINTER p2)
{
  log_trace("GetSphedaPrize({}, {}, {})", i2, fmt::ptr(p1), fmt::ptr(p2));

  todo;
  return false;
}

// 002F97E0
u8 CDngFloorManager::IsPlaySubGame()
{
  log_trace("IsPlaySubGame()");

  todo;
  return 0;
}

// 002F9840
u8 CDngFloorManager::IsSealFloor(s8 floor)
{
  log_trace("IsSealFloor({})", floor);

  todo;
  return 0;
}

// 002F9950
u8 CDngFloorManager::IsClearMostFastDestroy()
{
  log_trace("IsClearMostFastDestroy()");

  todo;
  return 0;
}

// 002F9A70
u8 CDngFloorManager::IsClearPractice(usize i)
{
  // 0035D070
  // FIXME: May include align
  static constexpr std::array<bool, 16> diff_conditiontable
  {
    true, true, true, true, true, false, false, false,
    false, false, false, false, true, false, false, false
  };

  // 0035D080
  static constexpr std::array<u16, 18> check_bittable
  {
    0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x1, 0x2, 0x4,
    0x8, 0x10, 0x40, 0x20, 0x2, 0x4, 0x8, 0x10, 0x1
  };

  // 0035D080
  static constexpr std::array<u16, 20> cbit
  {
    0x4, 0x8, 0x10, 0x20, 0x40, 0x2, 0x8, 0x10, 0x20, 0x40,
    0x2, 0x4, 0x10, 0x20, 0x40, 0x2, 0x4, 0x8, 0x20, 0x40
  };

  log_trace("IsClearPractice({})", i);

  todo;
  return 0;
}

// 002F9DA0
_UNKNOWNPOINTER CDngFloorManager::GetDngMapFloorInfo(s8 floor)
{
  log_trace("GetDngMapFloorInfo({})", floor);

  todo;
  return nullptr;
}

// 002F9DA0
_UNKNOWNPOINTER CDngFloorManager::GetActiveMapFloorInfo(s8 floor)
{
  log_trace("GetActiveMapFloorInfo({})", floor);

  todo;
  return nullptr;
}

// 002f9e40
void CDngFloorManager::RelationGlid()
{
  log_trace("RelationGlid()");

  todo;
}

// 002F9F30
void CDngFloorManager::CheckDrawGlidInfo()
{
  log_trace("CheckDrawGlidInfo()");

  todo;
}

// 002FA2C0
_UNKNOWNPOINTER CDngFloorManager::GetNextGlid(GLID_INFO* info, s32* pi)
{
  // 0035D100
  static constexpr std::array<std::array<std::array<u32, 3>, 4>, 3> search_tbl
  {
    0, 2, 3,
    1, 3, 2,
    2, 1, 0,
    3, 0, 1,

    0, 2, 3,
    1, 3, 2,
    2, 0, 1,
    3, 0, 1,

    0, 2, 3,
    1, 2, 3,
    2, 0, 1,
    3, 0, 1
  };

  log_trace("GetNextGlid({}, {})", fmt::ptr(info), fmt::ptr(pi));

  todo;
  return nullptr;
}

// 002FA3B0
_UNKNOWNPOINTER CDngFloorManager::GetNextRoom(s8 floor, usize i2, GLID_INFO* info, int unused, s32* pi)
{
  log_trace("GetNextRoom({}, {}, {}, {})", floor, i2, fmt::ptr(info), fmt::ptr(pi));

  todo;
  return nullptr;
}

// 002FA4E0
_UNKNOWNPOINTER CDngFloorManager::GetKeyNextRoom(s8 floor, usize i2, GLID_INFO* info)
{
  log_trace("GetKeyNextRoom({}, {}, {})", floor, i2, fmt::ptr(info));

  todo;
  return nullptr;
}

// 002FA550
s8 CDngFloorManager::GetDngMapNextFloorID(s8 floor, u8 i2)
{
  log_trace("GetDngMapNextFloorID({}, {})", floor, i2);

  todo;
  return 0;
}

// 002FA680
const char* CDngFloorManager::GetFloorTitle(s8 floor)
{
  log_trace("GetFloorTitle({})", floor);

  todo;
  return nullptr;
}

// 002FA710
u8 CDngFloorManager::GetDngMapNextRoot(s8 floor)
{
  log_trace("GetDngMapNextRoot({})", floor);

  todo;
  return 0;
}