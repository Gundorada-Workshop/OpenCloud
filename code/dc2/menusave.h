#pragma once
#include <array>

#include "dc2/dng_main.h"
#include "dc2/editdata.h"
#include "dc2/quest.h"
#include "dc2/userdata.h"

// ~ 002F12D0 - 002F76C0

// TODO THIS FILE
class CMemoryCardManager {};
class CSphidaData {};
struct GYORACE_DATA {};
class CGyoRaceData {};
class CSubGameData {};

struct SV_CONFIG_OPTION
{
  // NOTE: These correspond to menu indices and are not necessarily like bools
  // Refer to the options menu

  // 0
  s32 m_cursor_location_memory{}; // ON, OFF
  // 4
  s32 m_vibration{}; // ON, OFF
  // 8
  s32 m_message_speed{}; // ON, OFF
  // C
  s32 m_sound{}; // STEREO, MONO
  // 10
  s32 m_time_speed{}; // NORMAL, FAST
  // 14
  s32 m_map_display{}; // 1, 2, 3
  // 1C
  s32 m_enemy_hp_display{}; // ON, OFF
  // 20
  s32 m_damage_points{}; // ON, OFF
  // 24
  s32 m_character_name_display{}; // ON, OFF
  // 28
  s32 m_display_monster_name{}; // ON, OFF
  // 2C
  s32 m_anger_counter{}; // ON, OFF
  // 30
  s32 m_blur_background{}; // ON, OFF
  // 34
  s8 m_display_captions{}; // ON, OFF
  // 35
  s8 m_pause_display{}; // ON, OFF
  // 36
  s8 m_camera_pitch{}; // NORMAL, REVERSE
  // 37
  s8 m_camera_rotation{}; // NORMAL, REVERSE

  // SIZE 0x40
};

class CSaveDataDungeon
{
public:
  // 0019b160
  void Initialize();

  // 002F73F0
  void SetFloorID(sint floor);

  EDungeonID m_now_dungeon_id{};
  std::array<sint, static_cast<usize>(EDungeonID::COUNT)> m_now_floors{};
  std::array<sint, static_cast<usize>(EDungeonID::COUNT)> m_old_floors{};
};

class CMenuSystemData
{
public:
  // 002F12D0
  CMenuSystemData();
  // 002f1300
  void MenuSystemDataInit();
};

class CSaveData
{
public:
  // 002f61f0
  void Initialize();

  // 002f6780
  void InitBitCtrl();

  // ?

  // 1C24
  std::array<CEditData, 5> m_edit_data{};
  // 1C574
  SV_CONFIG_OPTION m_sv_config_option{};
  // 1C5B4
  CSaveDataDungeon m_save_data_dungeon{};
  // 1D2A0
  CUserDataManager m_user_data_manager{};
  // 62A40
  CQuestData m_quest_data{};
  // 65930
  CMenuSystemData m_menu_system_data{};
};