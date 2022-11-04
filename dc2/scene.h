#pragma once
#include <array>
#include <glm/glm.hpp>
#include "common/debug.h"
#include "common/types.h"
#include "character.h"
#include "effect.h"
#include "effect_script.h"
#include "dng_main.h"
#include "mds_img.h"
#include "mg_frame.h"
#include "snd_mngr.h"
#include "villager.h"


// TODO
class CCameraControl;
class CCPoly;
class CMap;
class CMapSky;
class ClsMes;
class mgCCamera {};
struct InScreenFuncInfo {};


enum class ESceneDataType
{
  Character = 1,
  Map = 2,
  Message = 3,
  Camera = 4,
  GameObj_6 = 6,
  GameObj_7 = 7
};

template<>
struct fmt::formatter<ESceneDataType> : fmt::formatter<std::string_view>
{
  template<typename FormatContext>
  auto format(const ESceneDataType& data_type, FormatContext& ctx)
  {
    std::string out;
    switch (data_type)
    {
      case ESceneDataType::Character:
        out = "Character";
        break;
      case ESceneDataType::Map:
        out = "Map";
        break;
      case ESceneDataType::Message:
        out = "Message";
        break;
      case ESceneDataType::Camera:
        out = "Camera";
        break;
      case ESceneDataType::GameObj_6:
        out = "GameObj (6)";
        break;
      case ESceneDataType::GameObj_7:
        out = "GameObj (7)";
        break;
      default:
        out = "Unknown";
        break;
    }

    constexpr std::string_view tpl =
    {
      "ESceneDataType({})"
    };

    return fmt::format_to(ctx.out(), tpl, out);
  }
};

enum class ESceneDataStatus
{
  Initial = 0,
  UNK_1 = 1,
  Active = 2,
  Assigned = 4,
  UNK_8 = 8,
  UNK_10 = 16,
  UNK_20 = 32,
};
IMPLEMENT_ENUM_CLASS_BITWISE_OPERATORS(ESceneDataStatus);

template<>
struct fmt::formatter<ESceneDataStatus> : fmt::formatter<std::string_view>
{
  template<typename FormatContext>
  auto format(const ESceneDataStatus& data_status, FormatContext& ctx)
  {
    constexpr std::string_view tpl =
    {
      "ESceneDataStatus({})"
    };

    return fmt::format_to(ctx.out(), tpl, std::to_underlying(data_status));
  }
};

struct SCN_LOADMAP_INFO2 
{
public:
  // 00285150
  void Initialize();
};

class CSceneData
{
public:
  void Initialize(void);

  // 0
  ESceneDataStatus m_status;
  // 4
  // NOTE: Retrieved in CScene::GetType; some enumeration, maybe?
  _UNKNOWN m_unk_field_4;
  // 8
  char m_name[32];
  // 28
  s32 m_unk_field_28;
  // 2C
  _UNKNOWN m_unk_field_2C;
  // 30
  _UNKNOWN m_unk_field_30;
};

class CSceneCharacter : public CSceneData
{
public:
  // 00282AE0
  bool AssignData(CCharacter2* chara, const char* name);
  // 00282B40
  void Initialize(void);

  // 34
  CCharacter2* m_character;
  // 38
  s32 m_texb;
  // 3C
  s32 m_chara_no;
};

class CSceneMap : public CSceneData
{
public:
  // 00282B60
  void Initialize(void);
  // 00282B70
  bool AssignData(CMap* map, const char* name);

  // 34
  CMap* m_map;
};

class CSceneMessage : public CSceneData
{
public:
  // 00282BF0
  void Initialize(void);
  // 00282C00
  bool AssignData(ClsMes* message, const char* name);

  // 34
  ClsMes* m_message;
};

class CSceneCamera : public CSceneData
{
public:
  // 00282C80
  bool AssignData(mgCCamera* camera, const char* name);
  // 00282D00
  void Initialize(void);

  // 34
  mgCCamera* m_camera;
};

class CSceneSky : public CSceneData
{
public:
  // 00282D10
  bool AssignData(CMapSky* sky, const char* name);
  // 00282D90
  void Initialize(void);

  // 34
  CMapSky* m_sky;
};

class CSceneGameObj : public CSceneCharacter
{
public:
  // 00282DA0
  void Initialize(void);
};

class CSceneEffect : public CSceneData
{
public:
  // 00282DB0
  void Initialize(void);
  // 00282DC0
  bool AssignData(CEffectScriptMan* script_manager, const char* name);

  // 34
  CEffectScriptMan* m_effect_script_manager;
};

class CSceneEventData
{
public:

};

class CScene
{
public:
  struct BGM_INFO
  {
  public:
    // 002A5B00
    void Initialize();

    // 0
    _UNKNOWN m_unk_field_0;
    // 4
    s32 m_unk_field_4;
    // 8
    s32 m_unk_field_8;
    // C
    float m_unk_field_C;
    // 10
    s32 m_volume;
    // 14
    _UNKNOWN m_unk_field_14;
    // 18
    float m_unk_field_18;
    // 1C
    _UNKNOWN m_unk_field_1C;
    // 20
    _UNKNOWN m_unk_field_20;
    // 24
    _UNKNOWN m_unk_field_24;

    // ?

    // 430
    mgCMemory m_stack;
  };

  struct BGM_STATUS
  {
  public:

  };

  struct InScreenCharaInfo
  {
  public:

  };

  // 00282E40
  void InitAllData();
  // 00282EA0
  // BUG: ? No reason for this method to be virtual
  virtual void Initialize();
  // 00283150
  void SetStack(ssize stack_index, mgCMemory& stack);
  // 00283150
  mgCMemory* GetStack(ssize stack_index);
  // 002831D0
  void ClearStack(ssize stack_index);
  // 00283270
  void AssignStack(ssize stack_index);
  // 00283340
  CSceneCharacter* GetSceneCharacter(ssize character_index);
  // 00283340
  CSceneMap* GetSceneMap(ssize map_index);
  // 002833C0
  CSceneMessage* GetSceneMessage(ssize message_index);
  // 00283400
  CSceneCamera* GetSceneCamera(ssize camera_index);
  // 00283440
  CSceneSky* GetSceneSky(ssize sky_index);
  // 00283480
  CSceneGameObj* GetSceneGameObj(ssize gameobj_index);
  // 002834C0
  CSceneEffect* GetSceneEffect(ssize effect_index);
  // 00283500
  bool CheckIMGName(ssize map_index, const char* img_name);
  // 002835D0
  bool CheckMDSName(ssize map_index, const char* mds_name);
  // 002836A0
  CSceneData* GetData(ESceneDataType data_type, ssize index);
  // 00283740
  s32 AssignCamera(ssize camera_index, mgCCamera* camera, const char* name);
  // 00283820
  ssize GetCameraID(const char* name);
  // 002838C0
  mgCCamera* GetCamera(ssize camera_index);
  // 00283910
  s32 AssignMessage(ssize message_index, ClsMes* message, const char* name);
  // 002839E0
  ClsMes* GetMessage(ssize message_index);
  // 00283A30
  s32 AssignChara(ssize character_index, CCharacter2* character, const char* name);
  // 00283B00
  void SetCharaNo(ssize character_index, ssize character_no);
  // 00283B30
  ssize GetCharaNo(ssize character_index);
  // 00283B60
  CCharacter2* GetCharacter(ssize character_index);
  // 00283BB0
  ssize AssignMap(ssize map_index, CMap* map, const char* name);
  // 00283C90
  const char* GetMapName(ssize map_index);
  // 00283CC0
  ssize GetMapID(const char* name);
  // 00283D60
  CMap* GetMap(ssize map_index);
  // 00283DB0
  CMapSky* GetSky(ssize sky_index);
  // 00283E00
  ssize GetMainMapNo();
  // 00283E30
  _UNKNOWNPOINTER InScreenFunc(InScreenFuncInfo& func_info);
  // 002842F0
  void DrawScreenFunc(mgCFrame& frame);
  // 00284390
  ssize AssignSky(ssize sky_index, CMapSky* sky, const char* name);
  // 00284460
  bool DeleteSky(ssize sky_index);
  // 002844A0
  ssize AssignEffect(ssize effect_index, CEffectScriptMan* effect, const char* name);
  // 00284510
  void DeleteEffect(ssize effect_index);
  // 00284540
  CEffectScriptMan* GetEffect(ssize effect_index);
  // 00284570
  void StepEffectScript(ssize effect_index);
  // 00284600
  void DrawEffectScript(ssize effect_index);
  // 00284690
  bool IsActive(ESceneDataType data_type, ssize data_index);
  // 002846D0
  void SetActive(ESceneDataType data_type, ssize data_index);
  // 00284700
  void ResetActive(ESceneDataType data_type, ssize data_index);
  // 00284740
  void SetStatus(ESceneDataType data_type, ssize data_index, ESceneDataStatus status);
  // 00284780
  void ResetStatus(ESceneDataType data_type, ssize data_index, ESceneDataStatus status);
  // 002847C0
  ESceneDataStatus GetStatus(ESceneDataType data_type, ssize data_index);
  // 002847F0
  void SetType(ESceneDataType data_type, ssize data_index, _UNKNOWN _data_type);
  // 00284820
  _UNKNOWN GetType(ESceneDataType data_type, ssize data_index);
  // 00284850
  // Stores active maps in maps_dest, returns amount of active maps.
  usize GetActiveMaps(CMap** maps_dest, usize maps_capacity);
  // 00284900
  s32 GetCharaTexb(ssize character_index);
  // 00284900
  void SetCharaTexb(ssize character_index, s32 texb);
  // 002849C0
  void SetTime(float time);
  // 00284A60
  void AddTime(float time);
  // 00284A70
  void TimeStep(float time);
  // 00284B30
  void SetWind(const glm::vec4& wind_dir, float wind_velocity);
  // 00284B40
  void ResetWind();
  // 00284B50
  // Stores direction in direction; returns velocity.
  float GetWind(glm::vec4& direction);
  // 00284B60
  void SetNowMapNo(s32 now_map_no);
  // 00284B80
  void SetNowSubMapNo(s32 now_sub_map_no);
  // 00284BA0
  void LoadChara(_UNKNOWN i1, _UNKNOWNPOINTER p1, _UNKNOWNPOINTER p2, mgCMemory& m1, mgCMemory& m2, mgCMemory& m3, _UNKNOWN i2, _UNKNOWN i3);
  // 002853B0
  void DeleteChara(ssize character_index);
  // 002853E0
  void CopyChara(ssize character_index1, ssize character_index2, mgCMemory& memory);
  // 00285670
  s32 LoadMapFromMemory(int i, SCN_LOADMAP_INFO2& info);
  // 002856F0
  s32 LoadMapFromMemory(int i1, int i2, SCN_LOADMAP_INFO2& info);
  // 00285C30
  bool LoadMapBGStep(SCN_LOADMAP_INFO2& info);
  // 00285CE0
  s32 LoadMap(int i1, SCN_LOADMAP_INFO2& info, int i2);
  // 00285E70
  bool DeleteMap(ssize map_index, bool b);
  // 002A5B30
  void InitSnd();
  // 002A5C00
  void InitBGM();
  // 002A5C50
  void InitSeSrc();
  // 002A5E10
  void InitSeEnv();
  // 002A5EE0
  void InitSeBattle();
  // 002A5F60
  void InitSeBas();
  // 002A5FE0
  void SeAllStop();
  // 002A6020
  void SoundAllStop();
  // 002A6060
  void InitLoopSeMngr();
  // 002A60E0
  BGM_INFO* GetActiveBGMInfo();
  // 002A6110
  void PlayBGM(int i1, int i2, float f);
  // 002A6210
  void PauseBGM();
  // 002A6240
  void ReplayBGM();
  // 002A6280
  void StopBGM(int i);
  // 002A62E0
  void SetVolBGM(s32 volume);
  // 002A6350
  s32 GetVolBGM();
  // 002A6370
  s32 GetBGMState();
  // 002A63A0
  void SetVolfBGM(float volume);
  // 002A6420
  float GetVolfBGM();
  // 002A6440
  void FadeOutBGM(int i);
  // 002A6480
  void FadeInBGM(int i);
  // 002A64E0
  void AutoChangeBGMVol(int i);
  // 002A6510
  s32 GetActiveBGMStatus(BGM_STATUS& status_dest);
  // 002A6580
  void SetActiveBGMStatus(BGM_STATUS& status);
  // 002A6690
  void PlayEnvBGM(int i, float f);
  // 002A6720
  void SetEnvBGMVol(float volume);
  // 002A67C0
  void StopEnvBGMVol();
  // 002A6820
  void AutoChangeEnvBGM(int i);
  // 002A6830
  void AutoChangeEnvOffset(int i);
  // 002A6840
  void PlayEnvBGM();
  // 002A68F0
  s32 GetSeSrcID(int i);
  // 002A6940
  void GetNumber3(char* c, int i);
  // 002A69D0
  void GetBGMFile(char* c, int i);
  // 002A6A10
  void GetSeSrcFile(char* c, int i);
  // 002A6A50
  void GetSeEnvFile(char* c, int i);
  // 002A6A90
  void GetSeBaseFile(char* c, int i);
  // 002A6AD0
  void GetSeBattleFile(char* c, int i);
  // 002A6B10
  bool CheckLoadBGM(int i);
  // 002A6B50
  bool CheckLoadSeSrc(int i);
  // 002A6BA0
  bool CheckLoadSeEnv(int i);
  // 002A6BD0
  bool CheckLoadSeBattle(int i);
  // 002A6C00
  bool CheckLoadSeBase(int i);
  // 002A6C30
  _UNKNOWNPOINTER SearchSndDataID(int i);
  // 002A6CC0
  s16 GetDefBGMNo(int i);
  // 002A6CF0
  bool GetDefEventSeFile(int i, char* c);
  // 002A7290
  bool LoadBGMPack(int i, _UNKNOWNPOINTER p);
  // 002A7340
  bool LoadSeSrcPack(int i, _UNKNOWNPOINTER p);
  // 002A7410
  bool LoadSeEnvPack(int i, _UNKNOWNPOINTER p);
  // 002A74C0
  bool LoadSeBattlePack(int i, _UNKNOWNPOINTER p);
  // 002A7560
  bool LoadSeBasePack(int i, _UNKNOWNPOINTER p);
  // 002A7600
  void PrePlaySeSrc();
  // 002A7670
  void PlaySeSrc(int i, float f1, float f2);
  // 002A77B0
  s32 CheckSePlay(int i);
  // 002A7870
  float GetTimeBGMVolf();
  // 002A7940
  void StepSnd();
  // 002A7F00
  void StopSeSrc();
  // 002A7FB0
  void PlayMapSeSrc();
  // 002A80A0
  void SePlayOpenDoor(int i, float* unused);
  // 002A80C0
  void SePlayCloseDoor(int i, float* unused);
  // 002A80E0
  void SePlayFoot(int i1, int i2, float* fp);
  // 002A8160
  int GetLine(_UNKNOWNPOINTER p1, _UNKNOWNPOINTER p2, _UNKNOWNPOINTER p3);
  // 002A8300
  void LoadSndRevInfo(_UNKNOWNPOINTER p1, int i);
  // 002A8320
  void LoadSndFileInfo(_UNKNOWNPOINTER p1, int i);
  // 002C79F0
  void UpdateMapInfo();
  // 002C7B50
  void GetColPoly(CCPoly& col_poly, mgVu0FBOX& box, int i);
  // 002C7C20
  void GetCameraPoly(CCPoly& col_poly, mgVu0FBOX& box, int i);
  // 002C7CF0
  void RunEvent(int i, CSceneEventData& event_data);
  // 002C7E60
  bool GetMapEvent(glm::vec4& v, int i, CSceneEventData& event_data);
  // 002C8070
  bool GetFixCameraPos(glm::vec4& v1, glm::vec4& v2);
  // 002C8120
  void FixCameraPartsOnOff(glm::vec4& v);
  // 002C81A0
  void EyeViewDrawOnOff(int i);
  // 002C8260
  void GetSunPosition(glm::vec4& sun_position);
  // 002C8330
  void GetMoonPosition(glm::vec4& moon_position);
  // 002C8370
  void DrawSky(s32 i);
  // 002C8520
  void DrawLensFlare(ssize map_index, _UNKNOWNPOINTER p1, _UNKNOWNPOINTER p2);
  // 002C8790
  void EffectStep();
  // 002C8820
  void DrawEffect(int i);
  // 002C8B70
  bool CheckDrawChara(ssize character_index);
  // 002C8BF0
  bool CheckDrawCharaShadow(ssize character_index);
  // 002C8C70
  bool StepChar(ssize character_index);
  // 002C8D70
  void GetCharaLighting(glm::mat4& m, glm::vec4& v);
  // 002C8F80
  bool DrawChara(ssize character_index, int i);
  // 002C9280
  bool DrawCharaShadow(ssize character_index);
  // 002C93D0
  void DrawExclamationMark(mgCFrame& frame);
  // 002C94F0
  s32 SearchCharaTexb(int i);
  // 002C9590
  void PreLoadVillager(ssize villager_index, _UNKNOWNPOINTER p);
  // 002C9640
  void DeleteVillager(ssize villager_index);
  // 002C9660
  void DeleteSubVillager();
  // 002C9710
  void DeleteVillager();
  // 002C97C0
  s32 SearchCharaID(int i);
  // 002C9830
  bool GetNowVillagerTime();
  // 002C9880
  usize GetLoadVillagerList(_UNKNOWN i, _UNKNOWNPOINTER pi, CVillagerPlaceInfo&& place_info);
  // 002C9980
  s32 SearchCopyModel(_UNKNOWN i);
  // 002C9B80
  void CharaObjectOnOff(ssize character_index, mgCMemory& stack);
  // 002C9D40
  u32 LoadVillager(int i1, int i2);
  // 002CA3D0
  u32 LoadSubVillager(int i1, int i2);
  // 002CA3D0
  bool RegisterVillager(int i1, int i2, int i3);
  // 002CA430
  bool RegisterVillager(int i1, int i2, CVillagerPlaceInfo& place_info);
  // 002CA450
  bool RegisterVillager(int i1, int i2, mgCMemory& stack);
  // 002CA540
  bool GetTalkEvent(glm::vec4& v, CSceneEventData& event_data);
  // 002CA880
  void StepVillager();
  // 002CACD0
  void StayNearVillager(glm::vec4& v, _UNKNOWNPOINTER pi);
  // 002CAE60
  void CancelStayVillager(_UNKNOWNPOINTER pi);
  // 002CAEE0
  void StayVillager(int i);
  // 002CAF20
  void CancelStayVillager(int i);
  // 002CAFD0
  void ExModeVillager(int i);
  // 002CB010
  void SetActiveVillager();
  // 002CB110
  void InScreenChara(InScreenCharaInfo& chara_info, float* unused);
  // 002CB5A0
  void LoadGameObject(int i1, int i2, mgCMemory& stack);
  // 002CB900
  s32 GetGameObjectEvent(glm::vec4& v, CSceneEventData& event_data);
  // 002CBAA0
  void DrawGameObject(ssize gameobj_index);


  // 0
  usize m_n_stacks_capacity;
  // 4
  usize m_n_stacks_length;
  // 8
  std::array<mgCMemory*, 12> m_stacks;
  // 38
  _UNKNOWN m_unk_field_38;
  // 3C
  _UNKNOWN m_unk_field_3C;
  // 40
  usize m_n_characters;
  // 44
  std::array<CSceneCharacter, 128> m_characters;
  // 2044
  usize m_n_cameras;
  // 2048
  std::array<CSceneCamera, 8> m_cameras;
  // 2208
  usize m_n_messages;
  // 220C
  std::array<CSceneMessage, 8> m_messages;
  // 23D0
  CMdsListSet m_mds_list_set;

  // ?

  // 24F0
  CFireRaster m_fire_raster;
  // 27E0
  usize m_n_maps;
  // 27E4
  std::array<CSceneMap, 4> m_maps;
  // 28C4
  usize m_n_skies;
  // 28C8
  std::array<CSceneSky, 4> m_skies;
  // 29A8
  usize m_n_gameobjs;
  // 29AC
  std::array<CSceneGameObj, 4> m_gameobjs;
  // 2AAC
  usize m_n_effects;
  // 2AB0
  std::array<CSceneEffect, 8> m_effects;
  // 2C70
  CFadeInOut m_fade_in_out;
  // 2CA0
  _UNKNOWN m_unk_field_2CA0;
  // 2CA8
  SCN_LOADMAP_INFO2 m_scn_loadmap_info;
  // 2E50
  s32 m_unk_field_2E50;
  // 2E54
  s32 m_unk_field_2E54;
  // 2E58
  s32 m_unk_field_2E58;
  // 2E5C
  s32 m_unk_field_2E5C;
  // 2E60
  s32 m_now_map_no;
  // 2E64
  s32 m_now_sub_map_no;
  // 2E68
  s32 m_last_map_no;
  // 2E6C
  s32 m_last_sub_map_no;
  // 2E70
  _UNKNOWN m_unk_field_2E70;
  // 2E74
  _UNKNOWN m_unk_field_2E74;
  // 2E78
  _UNKNOWN m_unk_field_2E78;
  // 2E7C
  _UNKNOWN m_unk_field_2E7C;
  // 2E80
  _UNKNOWN m_unk_field_2E80;
  // 2E84
  _UNKNOWN m_unk_field_2E84;
  // 2E90
  CSceneEventData m_scene_event_data;
  // 2F64
  _UNKNOWN m_unk_field_2F64;
  // 2F68
  _UNKNOWN m_unk_field_2F68;
  // 2F6C
  _UNKNOWN m_unk_field_2F6C;
  // 2F70
  float m_unk_field_2F70;
  // 2F74
  _UNKNOWN m_unk_field_2F74;
  // 2F78
  float m_wind_velocity;
  // 2F80
  glm::vec4 m_wind_direction;
  // 2F90
  _UNKNOWN m_unk_field_2F90;
  // 2F94
  _UNKNOWN m_unk_field_2F94;

  // ?

  // 2FA4
  CDngFloorManager m_dng_floor_manager;
  // 2FB4
  _UNKNOWN m_unk_field_2FB4;

  // ?

  // 2FD4
  s16 m_unk_field_2FD4;

  // ?

  // 2FFC
  float m_unk_field_2FFC;

  // ?

  // 3008
  _UNKNOWN m_unk_field_3008;
  // 300C
  _UNKNOWN m_unk_field_300C;
  // 3010
  _UNKNOWN m_unk_field_3010;

  // ?

  // 3038
  _UNKNOWN m_unk_field_3038;
  // 303C
  _UNKNOWN m_unk_field_303C;
  // 3040
  _UNKNOWN m_unk_field_3040;
  // 3050
  CVillagerMngr m_villager_manager;
  // 3E60
  _UNKNOWN m_unk_field_3E60;
  // 3E64
  _UNKNOWN m_unk_field_3E64;
  // 3E70
  CThunderEffect m_thunder_effect;

  // ?

  // 9080
  std::array<BGM_INFO, 2> m_bgm_info;

  // ?

  // 9DD0
  mgCMemory m_unk_field_9DD0;

  // ?

  // A450
  mgCMemory m_unk_field_A450;

  // ?

  // C4A0
  mgCMemory m_unk_field_C4A0;

  // ?

  // E4E0
  mgCMemory m_unk_field_E4E0;

  // ?

  // 10510
  mgCMemory m_unk_field_10510;
  // 10540
  CLoopSeMngr m_loop_se_manager;
  // NOTE: size 0x1054C (vtable @ 0x10548)
};

// 00284BA0
void LoadMapData(SCN_LOADMAP_INFO2& info, bool b);