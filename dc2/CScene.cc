#include "common/debug.h"
#include "common/log.h"
#include "CScene.h"

set_log_channel("CScene");

void CSceneData::Initialize()
{
	log_trace("CSceneData::Initialize()");

	m_unk_field_0 = 0;
	m_unk_field_4 = 0;
	m_name[0] = '\0';
	m_unk_field_28 = -1;
	m_unk_field_2C = 0;
	m_unk_field_30 = 0;
}

bool CSceneCharacter::AssignData(CCharacter2& chara, char* name)
{
	log_trace("CSceneCharacter::AssignData({}, {})", fmt::ptr(&chara), name);

	todo;
	return false;
}

void CSceneCharacter::Initialize()
{
	log_trace("CSceneCharacter:Initialize()");

	m_character = nullptr;
	m_texb = -1;
	m_chara_no = -1;
	CSceneData::Initialize();
}

void CSceneMap::Initialize()
{
	log_trace("CSceneMap:Initialize()");

	m_map = nullptr;
	CSceneData::Initialize();
}

bool CSceneMap::AssignData(CMap& map, char* name)
{
	log_trace("CSceneMap::AssignData({}, {})", fmt::ptr(&map), name);

	todo;
	return false;
}

void CSceneMessage::Initialize()
{
	log_trace("CSceneMessage::Initialize()");

	m_message = nullptr;
	CSceneData::Initialize();
}

bool CSceneMessage::AssignData(ClsMes& message, char* name)
{
	log_trace("CSceneMessage::AssignData({}, {})", fmt::ptr(&message), name);

	todo;
	return false;
}

bool CSceneCamera::AssignData(mgCCamera& camera, char* name)
{
	log_trace("CSceneCamera::AssignData({}, {})", fmt::ptr(&camera), name);

	todo;
	return false;
}

void CSceneCamera::Initialize()
{
	log_trace("CSceneCamera::Initialize()");

	m_camera = nullptr;
	CSceneData::Initialize();
}

bool CSceneSky::AssignData(CMapSky& sky, char* name)
{
	log_trace("CSceneSky::AssignData({}, {})", fmt::ptr(&sky), name);

	todo;
	return false;
}

void CSceneSky::Initialize()
{
	log_trace("CSceneSky::Initialize()");

	m_sky = nullptr;
	CSceneData::Initialize();
}

void CSceneGameObj::Initialize()
{
	log_trace("CSceneGameObj::Initialize()");

	CSceneCharacter::Initialize();
}

void CSceneEffect::Initialize()
{
	log_trace("CSceneEffect::Initialize()");

	m_effect = nullptr;
	CSceneData::Initialize();
}

bool CSceneEffect::AssignData(CEffectScriptMan& script_manager, char* name)
{
	log_trace("CSceneEffect::AssignData({}, {})", fmt::ptr(&script_manager), name);

	todo;
	return false;
}

// 00282E40
void CScene::InitAllData()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 00282EA0
void CScene::Initialize()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 00283150
void CScene::SetStack(ssize stack_index, mgCMemory& stack)
{
	log_trace("CScene::{}({}, {})", __func__, stack_index, fmt::ptr(&stack));

	todo;
}

// 00283150
mgCMemory* CScene::GetStack(ssize stack_index)
{
	log_trace("CScene::{}({})", __func__, stack_index);

	todo;
	return nullptr;
}

// 002831D0
void CScene::ClearStack(ssize stack_index)
{
	log_trace("CScene::{}({})", __func__, stack_index);

	todo;
}

// 00283270
void CScene::AssignStack(ssize stack_index)
{
	log_trace("CScene::{}({})", __func__, stack_index);

	todo;
}

// 00283340
CSceneCharacter* GetSceneCharacter(ssize character_index)
{
	log_trace("CScene::{}({})", __func__, character_index);

	todo;
	return nullptr;
}

// 00283340
CSceneMap* CScene::GetSceneMap(ssize map_index)
{
	log_trace("CScene::{}({})", __func__, map_index);

	todo;
	return nullptr;
}

// 002833C0
CSceneMessage* CScene::GetSceneMessage(ssize message_index)
{
	log_trace("CScene::{}({})", __func__, message_index);

	todo;
	return nullptr;
}

// 00283400
CSceneCamera* CScene::GetSceneCamera(ssize camera_index)
{
	log_trace("CScene::{}({})", __func__, camera_index);

	todo;
	return nullptr;
}

// 00283440
CSceneSky* CScene::GetSceneSky(ssize sky_index)
{
	log_trace("CScene::{}({})", __func__, sky_index);

	todo;
	return nullptr;
}

// 00283480
CSceneGameObj* CScene::GetSceneGameObj(ssize gameobj_index)
{
	log_trace("CScene::{}({})", __func__, gameobj_index);

	todo;
	return nullptr;
}

// 002834C0
CSceneEffect* CScene::GetSceneEffect(ssize effect_index)
{
	log_trace("CScene::{}({})", __func__, effect_index);

	todo;
	return nullptr;
}

// 00283500
bool CScene::CheckIMGName(ssize map_index, const char* img_name)
{
	log_trace("CScene::{}({}, {})", __func__, map_index, img_name);

	todo;
	return false;
}

// 002835D0
bool CScene::CheckMDSName(ssize map_index, const char* mds_name)
{
	log_trace("CScene::{}({}, {})", __func__, map_index, mds_name);

	todo;
	return false;
}

// 002836A0
CSceneData* CScene::GetData(ESceneDataType data_type, ssize index)
{
	log_trace("CScene::{}()", __func__, data_type, index);

	todo;
	return nullptr;
}

// 00283740
s32 CScene::AssignCamera(ssize camera_index, mgCCamera& camera, const char* name)
{
	log_trace("CScene::{}({}, {}, {})", __func__, camera_index, fmt::ptr(&camera), name);

	todo;
	return -1;
}

// 00283820
ssize CScene::GetCameraID(const char* name)
{
	log_trace("CScene::{}({})", __func__, name);

	todo;
	return -1;
}

// 002838C0
mgCCamera* CScene::GetCamera(ssize camera_index)
{
	log_trace("CScene::{}({})", __func__, camera_index);

	todo;
	return nullptr;
}

// 00283910
s32 CScene::AssignMessage(ssize message_index, ClsMes& message, const char* name)
{
	log_trace("CScene::{}({}, {}, {})", __func__, message_index, fmt::ptr(&message), name);

	todo;
	return -1;
}

// 002839E0
ClsMes* CScene::GetMessage(ssize message_index)
{
	log_trace("CScene::{}({})", __func__, message_index);

	todo;
	return nullptr;
}

// 00283A30
s32 CScene::AssignChara(ssize character_index, CCharacter2& character, const char* name)
{
	log_trace("CScene::{}({}, {}, {})", __func__, character_index, fmt::ptr(&character), name);

	todo;
	return -1;
}

// 00283B00
void CScene::SetCharaNo(ssize character_index, ssize character_no)
{
	log_trace("CScene::{}({})", __func__, character_index, character_no);

	todo;
}

// 00283B30
ssize CScene::GetCharaNo(ssize character_index)
{
	log_trace("CScene::{}({})", __func__, character_index);

	todo;
	return -1;
}
;
// 00283B60
CCharacter2* CScene::GetCharacter(ssize character_index)
{
	log_trace("CScene::{}({})", __func__, character_index);

	todo;
	return nullptr;
}

// 00283BB0
ssize CScene::AssignMap(ssize map_index, CMap& map, const char* name)
{
	log_trace("CScene::{}({}, {}, {})", __func__, map_index, fmt::ptr(&map), name);

	todo;
	return -1;
}

// 00283C90
const char* CScene::GetMapName(ssize map_index)
{
	log_trace("CScene::{}({})", __func__, map_index);

	todo;
	return "";
}

// 00283CC0
ssize CScene::GetMapID(const char* name)
{
	log_trace("CScene::{}()", __func__);

	todo;
	return -1;
}

// 00283D60
CMap* CScene::GetMap(ssize map_index)
{
	log_trace("CScene::{}({})", __func__, map_index);

	todo;
	return nullptr;
}

// 00283DB0
CMapSky* CScene::GetSky(ssize sky_index)
{
	log_trace("CScene::{}({})", __func__, sky_index);

	todo;
	return nullptr;
}

// 00283E00
ssize CScene::GetMainMapNo()
{
	log_trace("CScene::{}()", __func__);

	todo;
	return -1;
}

// 00283E30
_UNKNOWNPOINTER CScene::InScreenFunc(InScreenFuncInfo& func_info)
{
	log_trace("CScene::{}({})", __func__, fmt::ptr(&func_info));

	todo;
	return nullptr;
}
;
// 002842F0
void CScene::DrawScreenFunc(mgCFrame& frame)
{
	log_trace("CScene::{}({})", __func__, fmt::ptr(&frame));

	todo;
}

// 00284390
ssize CScene::AssignSky(ssize sky_index, CMapSky& sky, const char* name)
{
	log_trace("CScene::{}({}, {}, {})", __func__, sky_index, fmt::ptr(&sky), name);

	todo;
	return -1;
}

// 00284460
bool CScene::DeleteSky(ssize sky_index)
{
	log_trace("CScene::{}({})", __func__, sky_index);

	todo;
	return false;
}

// 002844A0
ssize CScene::AssignEffect(ssize effect_index, CEffect& effect, const char* name)
{
	log_trace("CScene::{}({}, {}, {})", __func__, effect_index, fmt::ptr(&effect), name);

	todo;
	return -1;
}

// 00284510
void CScene::DeleteEffect(ssize effect_index)
{
	log_trace("CScene::{}({})", __func__, effect_index);

	todo;
}

// 00284540
CEffect* CScene::GetEffect(ssize effect_index)
{
	log_trace("CScene::{}({})", __func__, effect_index);

	todo;
	return nullptr;
}

// 00284570
void CScene::StepEffectScript(ssize effect_index)
{
	log_trace("CScene::{}({})", __func__, effect_index);

	todo;
}

// 00284600
void CScene::DrawEffectScript(ssize effect_index)
{
	log_trace("CScene::{}({})", __func__, effect_index);

	todo;
}

// 00284690
bool CScene::IsActive(ESceneDataType data_type, ssize data_index)
{
	log_trace("CScene::{}({}, {})", __func__, data_type, data_index);

	todo;
	return false;
}

// 002846D0
void CScene::SetActive(ESceneDataType data_type, ssize data_index)
{
	log_trace("CScene::{}({}, {})", __func__, data_type, data_index);

	todo;
}

// 00284700
void CScene::ResetActive(ESceneDataType data_type, ssize data_index)
{
	log_trace("CScene::{}({}, {})", __func__, data_type, data_index);

	todo;
}

// 00284740
void CScene::SetStatus(ESceneDataType data_type, ssize data_index, s32 status_bitmask)
{
	log_trace("CScene::{}({}, {}, {})", __func__, data_type, data_index, status_bitmask);

	todo;
}

// 00284780
void CScene::ResetStatus(ESceneDataType data_type, ssize data_index, s32 status_bitmask)
{
	log_trace("CScene::{}({}, {}, {})", __func__, data_type, data_index, status_bitmask);

	todo;
}

// 002847C0
s32 CScene::GetStatus(ESceneDataType data_type, ssize data_index)
{
	log_trace("CScene::{}({}, {})", __func__, data_type, data_index);

	todo;
	return -1;
}

// 002847F0
void CScene::SetType(ESceneDataType data_type, ssize data_index, _UNKNOWN _data_type)
{
	log_trace("CScene::{}({}, {}, {})", __func__, data_type, data_index, _data_type);

	todo;
}

// 00284820
_UNKNOWN CScene::GetType(ESceneDataType data_type, ssize data_index)
{
	log_trace("CScene::{}({}, {})", __func__, data_type, data_index);

	todo;
	return 0;
}

// 00284850
// Stores active maps in maps_dest, returns amount of active maps.
usize CScene::GetActiveMaps(CMap** maps_dest, usize maps_capacity)
{
	log_trace("CScene::{}({}, {})", __func__, fmt::ptr(maps_dest), maps_capacity);

	todo;
	return 0;
}

// 00284900
s32 CScene::GetCharaTexb(ssize character_index)
{
	log_trace("CScene::{}({})", __func__, character_index);

	todo;
	return -1;
}

// 00284900
void CScene::SetCharaTexb(ssize character_index, s32 texb)
{
	log_trace("CScene::{}({}, {})", __func__, character_index, texb);

	todo;
}

// 002849C0
void CScene::SetTime(float time)
{
	log_trace("CScene::{}({})", __func__, time);

	todo;
}

// 00284A60
void CScene::AddTime(float time)
{
	log_trace("CScene::{}({})", __func__, time);

	todo;
}

// 00284A70
void CScene::TimeStep(float time)
{
	log_trace("CScene::{}({})", __func__, time);

	todo;
}

// 00284B30
void CScene::SetWind(const glm::vec4& wind_direction, float wind_velocity)
{
	log_trace("CScene::{}()", __func__, fmt::ptr(&wind_direction), wind_velocity);

	todo;
}

// 00284B40
void CScene::ResetWind()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 00284B50
// Stores direction in direction; returns velocity.
float CScene::GetWind(glm::vec4& direction)
{
	log_trace("CScene::{}({})", __func__, fmt::ptr(&direction));

	todo;
	return 0.0f;
}

// 00284B60
void CScene::SetNowMapNo(s32 now_map_no)
{
	log_trace("CScene::{}({})", __func__, now_map_no);

	todo;
}

// 00284B80
void CScene::SetNowSubMapNo(s32 now_sub_map_no)
{
	log_trace("CScene::{}({})", __func__, now_sub_map_no);

	todo;
}

// 00284BA0
void CScene::LoadChara(_UNKNOWN i1, _UNKNOWNPOINTER p1, _UNKNOWNPOINTER p2, mgCMemory& m1, mgCMemory& m2, mgCMemory& m3, _UNKNOWN i2, _UNKNOWN i3)
{
	log_trace("CScene::{}({}, {}, {}, {}, {}, {}, {}, {})", __func__, i1, fmt::ptr(p1), fmt::ptr(p2), fmt::ptr(&m1), fmt::ptr(&m2), fmt::ptr(&m3), i2, i3);

	todo;
}

// 002853B0
void CScene::DeleteChara(ssize character_index)
{
	log_trace("CScene::{}({})", __func__, character_index);

	todo;
}

// 002853E0
void CScene::CopyChara(ssize character_index1, ssize character_index2, mgCMemory& memory)
{
	log_trace("CScene::{}({}, {}, {})", __func__, character_index1, character_index2, fmt::ptr(&memory));

	todo;
}

// 00285670
s32 CScene::LoadMapFromMemory(int i, SCN_LOADMAP_INFO2& info)
{
	log_trace("CScene::{}({}, {})", __func__, i, fmt::ptr(&info));

	todo;
	return -1;
}

// 002856F0
s32 CScene::LoadMapFromMemory(int i1, int i2, SCN_LOADMAP_INFO2& info)
{
	log_trace("CScene::{}({}, {}, {})", __func__, i1, i2, fmt::ptr(&info));

	todo;
	return -1;
}

// 00285C30
bool CScene::LoadMapBGStep(SCN_LOADMAP_INFO2& info)
{
	log_trace("CScene::{}()", __func__);

	todo;
	return false;
}

// 00285CE0
s32 CScene::LoadMap(int i1, SCN_LOADMAP_INFO2& info, int i2)
{
	log_trace("CScene::{}({}, {}, {})", __func__, i1, fmt::ptr(&info), i2);

	todo;
	return -1;
}

// 00285E70
bool CScene::DeleteMap(ssize map_index, bool b)
{
	log_trace("CScene::{}({}, {})", __func__, map_index, b);

	todo;
	return false;
}

// 002A5B30
void CScene::InitSnd()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A5C00
void CScene::InitBGM()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A5C50
void CScene::InitSeSrc()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A5E10
void CScene::InitSeEnv()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A5EE0
void CScene::InitSeBattle()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A5F60
void CScene::InitSeBas()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A5FE0
void CScene::SeAllStop()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A6020
void CScene::SoundAllStop()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A6060
void CScene::InitLoopSeMngr()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A60E0
CScene::BGM_INFO* CScene::GetActiveBGMInfo()
{
	log_trace("CScene::{}()", __func__);

	todo;
	return nullptr;
}

// 002A6110
void CScene::PlayBGM(int i1, int i2, float f)
{
	log_trace("CScene::{}({}, {}, {})", __func__, i1, i2, f);

	todo;
}

// 002A6210
void CScene::PauseBGM()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A6240
void CScene::ReplayBGM()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A6280
void CScene::StopBGM(int i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}

// 002A62E0
void CScene::SetVolBGM(s32 volume)
{
	log_trace("CScene::{}({})", __func__, volume);

	todo;
}

// 002A6350
s32 CScene::GetVolBGM()
{
	log_trace("CScene::{}()", __func__);

	todo;
	return -1;
}

// 002A6370
s32 CScene::GetBGMState()
{
	log_trace("CScene::{}()", __func__);

	todo;
	return -1;
}

// 002A63A0
void CScene::SetVolfBGM(float volume)
{
	log_trace("CScene::{}({})", __func__, volume);

	todo;
}

// 002A6420
float CScene::GetVolfBGM()
{
	log_trace("CScene::{}()", __func__);

	todo;
	return 0.0f;
}

// 002A6440
void CScene::FadeOutBGM(int i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}

// 002A6480
void CScene::FadeInBGM(int i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}

// 002A64E0
void CScene::AutoChangeBGMVol(int i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}
;
// 002A6510
s32 CScene::GetActiveBGMStatus(BGM_STATUS& status_dest)
{
	log_trace("CScene::{}({})", __func__, fmt::ptr(&status_dest));

	todo;
	return -1;
}

// 002A6580
void CScene::SetActiveBGMStatus(BGM_STATUS& status)
{
	log_trace("CScene::{}()", __func__, fmt::ptr(&status));

	todo;
}

// 002A6690
void CScene::PlayEnvBGM(int i, float f)
{
	log_trace("CScene::{}({}, {})", __func__, i, f);

	todo;
}

// 002A6720
void CScene::SetEnvBGMVol(float volume)
{
	log_trace("CScene::{}({})", __func__, volume);

	todo;
}

// 002A67C0
void CScene::StopEnvBGMVol()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A6820
void CScene::AutoChangeEnvBGM(int i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}

// 002A6830
void CScene::AutoChangeEnvOffset(int i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}

// 002A6840
void CScene::PlayEnvBGM()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A68F0
s32 CScene::GetSeSrcID(int i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return -1;
}

// 002A6940
void CScene::GetNumber3(char* c, int i)
{
	log_trace("CScene::{}({}, {})", __func__, c, i);

	todo;
}

// 002A69D0
void CScene::GetBGMFile(char* c, int i)
{
	log_trace("CScene::{}({}, {})", __func__, c, i);

	todo;
}

// 002A6A10
void CScene::GetSeSrcFile(char* c, int i)
{
	log_trace("CScene::{}({}, {})", __func__, c, i);

	todo;
}

// 002A6A50
void CScene::GetSeEnvFile(char* c, int i)
{
	log_trace("CScene::{}({}, {})", __func__, c, i);

	todo;
}

// 002A6A90
void CScene::GetSeBaseFile(char* c, int i)
{
	log_trace("CScene::{}({}, {})", __func__, c, i);

	todo;
}

// 002A6AD0
void CScene::GetSeBattleFile(char* c, int i)
{
	log_trace("CScene::{}({}, {})", __func__, c, i);

	todo;
}

// 002A6B10
bool CScene::CheckLoadBGM(int i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return false;
}

// 002A6B50
bool CScene::CheckLoadSeSrc(int i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return false;
}

// 002A6BA0
bool CScene::CheckLoadSeEnv(int i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return false;
}

// 002A6BD0
bool CScene::CheckLoadSeBattle(int i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return false;
}

// 002A6C00
bool CScene::CheckLoadSeBase(int i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return false;
}

// 002A6C30
_UNKNOWNPOINTER CScene::SearchSndDataID(int i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return nullptr;
}

// 002A6CC0
s16 CScene::GetDefBGMNo(int i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return -1;
}

// 002A6CF0
bool CScene::GetDefEventSeFile(int i, char* c)
{
	log_trace("CScene::{}({}, {})", __func__, i, c);

	todo;
	return false;
}

// 002A7290
bool CScene::LoadBGMPack(int i, _UNKNOWNPOINTER p)
{
	log_trace("CScene::{}({}, {})", __func__, i, fmt::ptr(p));

	todo;
	return false;
}

// 002A7340
bool CScene::LoadSeSrcPack(int i, _UNKNOWNPOINTER p)
{
	log_trace("CScene::{}({}, {})", __func__, i, fmt::ptr(p));

	todo;
	return false;
}

// 002A7410
bool CScene::LoadSeEnvPack(int i, _UNKNOWNPOINTER p)
{
	log_trace("CScene::{}({}, {})", __func__, i, fmt::ptr(p));

	todo;
	return false;
}

// 002A74C0
bool CScene::LoadSeBattlePack(int i, _UNKNOWNPOINTER p)
{
	log_trace("CScene::{}({}, {})", __func__, i, fmt::ptr(p));

	todo;
	return false;
}

// 002A7560
bool CScene::LoadSeBasePack(int i, _UNKNOWNPOINTER p)
{
	log_trace("CScene::{}({}, {})", __func__, i, fmt::ptr(p));

	todo;
	return false;
}

// 002A7600
void CScene::PrePlaySeSrc()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A7670
void CScene::PlaySeSrc(int i, float f1, float f2)
{
	log_trace("CScene::{}({}, {}, {})", __func__, i, f1, f2);

	todo;
}

// 002A77B0
s32 CScene::CheckSePlay(int i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return -1;
}

// 002A7870
float CScene::GetTimeBGMVolf()
{
	log_trace("CScene::{}()", __func__);

	todo;
	return 0.0f;
}

// 002A7940
void CScene::StepSnd()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A7F00
void CScene::StopSeSrc()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A7FB0
void CScene::PlayMapSeSrc()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002A80A0
void CScene::SePlayOpenDoor(int i, float* unused)
{
	log_trace("CScene::{}({}, {})", __func__, i, fmt::ptr(unused));

	todo;
}

// 002A80C0
void CScene::SePlayCloseDoor(int i, float* unused)
{
	log_trace("CScene::{}({}, {})", __func__, i, fmt::ptr(unused));

	todo;
}

// 002A80E0
void CScene::SePlayFoot(int i1, int i2, float* fp)
{
	log_trace("CScene::{}({}, {}, {})", __func__, i1, i2, fmt::ptr(fp));

	todo;
}

// 002A8160
int CScene::GetLine(_UNKNOWNPOINTER p1, _UNKNOWNPOINTER p2, _UNKNOWNPOINTER p3)
{
	log_trace("CScene::{}()", __func__, fmt::ptr(p1), fmt::ptr(p2), fmt::ptr(p3));

	todo;
	return -1;
}

// 002A8300
void CScene::LoadSndRevInfo(_UNKNOWNPOINTER p1, int i)
{
	log_trace("CScene::{}({}, {})", __func__, fmt::ptr(p1), i);

	todo;
}

// 002A8320
void CScene::LoadSndFileInfo(_UNKNOWNPOINTER p1, int i)
{
	log_trace("CScene::{}({}, {})", __func__, fmt::ptr(p1), i);

	todo;
}

// 002C79F0
void CScene::UpdateMapInfo()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002C7B50
void CScene::GetColPoly(CCPoly& col_poly, mgVu0FBOX& box, int i)
{
	log_trace("CScene::{}({}, {}, {})", __func__, fmt::ptr(&col_poly), fmt::ptr(&box), i);

	todo;
}

// 002C7C20
void CScene::GetCameraPoly(CCPoly& col_poly, mgVu0FBOX& box, int i)
{
	log_trace("CScene::{}({}, {}, {})", __func__, fmt::ptr(&col_poly), fmt::ptr(&box), i);

	todo;
}

// 002C7CF0
void CScene::RunEvent(int i, CSceneEventData& event_data)
{
	log_trace("CScene::{}({}, {})", __func__, i, fmt::ptr(&event_data));

	todo;
}

// 002C7E60
bool CScene::GetMapEvent(glm::vec4& v, int i, CSceneEventData& event_data)
{
	log_trace("CScene::{}({}, {}, {})", __func__, fmt::ptr(&v), i, fmt::ptr(&event_data));

	todo;
	return false;
}

// 002C8070
bool CScene::GetFixCameraPos(glm::vec4& v1, glm::vec4& v2)
{
	log_trace("CScene::{}({}, {})", __func__, fmt::ptr(&v1), fmt::ptr(&v2));

	todo;
	return false;
}

// 002C8120
void CScene::FixCameraPartsOnOff(glm::vec4& v)
{
	log_trace("CScene::{}({})", __func__, fmt::ptr(&v));

	todo;
}

// 002C81A0
void CScene::EyeViewDrawOnOff(int i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}

// 002C8260
void CScene::GetSunPosition(glm::vec4& sun_position)
{
	log_trace("CScene::{}({})", __func__, fmt::ptr(&sun_position));

	todo;
}

// 002C8330
void CScene::GetMoonPosition(glm::vec4& moon_position)
{
	log_trace("CScene::{}({})", __func__, fmt::ptr(&moon_position));

	todo;
}

// 002C8370
void CScene::DrawSky(s32 i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}

// 002C8520
void CScene::DrawLensFlare(ssize map_index, _UNKNOWNPOINTER p1, _UNKNOWNPOINTER p2)
{
	log_trace("CScene::{}({}, {}, {})", __func__, map_index, fmt::ptr(p1), fmt::ptr(p2));

	todo;
}

// 002C8790
void CScene::EffectStep()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002C8820
void CScene::DrawEffect(int i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}

// 002C8B70
bool CScene::CheckDrawChara(ssize character_index)
{
	log_trace("CScene::{}({})", __func__, character_index);

	todo;
	return false;
}

// 002C8BF0
bool CScene::CheckDrawCharaShadow(ssize character_index)
{
	log_trace("CScene::{}({})", __func__, character_index);

	todo;
	return false;
}

// 002C8C70
bool CScene::StepChar(ssize character_index)
{
	log_trace("CScene::{}({})", __func__, character_index);

	todo;
	return false;
}

// 002C8D70
void CScene::GetCharaLighting(glm::mat4& m, glm::vec4& v)
{
	log_trace("CScene::{}({}, {})", __func__, fmt::ptr(&m), fmt::ptr(&v));

	todo;
}

// 002C8F80
bool CScene::DrawChara(ssize character_index, int i)
{
	log_trace("CScene::{}({}, {})", __func__, character_index, i);

	todo;
	return false;
}

// 002C9280
bool CScene::DrawCharaShadow(ssize character_index)
{
	log_trace("CScene::{}({})", __func__, character_index);

	todo;
	return false;
}

// 002C93D0
void CScene::DrawExclamationMark(mgCFrame& frame)
{
	log_trace("CScene::{}({})", __func__, fmt::ptr(&frame));

	todo;
}

// 002C94F0
s32 CScene::SearchCharaTexb(int i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return -1;
}

// 002C9590
void CScene::PreLoadVillager(ssize villager_index, _UNKNOWNPOINTER p)
{
	log_trace("CScene::{}({}, {})", __func__, villager_index, fmt::ptr(p));

	todo;
}

// 002C9640
void CScene::DeleteVillager(ssize villager_index)
{
	log_trace("CScene::{}({})", __func__, villager_index);

	todo;
}

// 002C9660
void CScene::DeleteSubVillager()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002C9710
void CScene::DeleteVillager()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002C97C0
s32 CScene::SearchCharaID(int i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return -1;
}

// 002C9830
bool CScene::GetNowVillagerTime()
{
	log_trace("CScene::{}()", __func__);

	todo;
	return false;
}

// 002C9880
usize CScene::GetLoadVillagerList(_UNKNOWN i, _UNKNOWNPOINTER pi, CVillagerPlaceInfo&& place_info)
{
	log_trace("CScene::{}({}, {}, {})", __func__, i, fmt::ptr(pi), fmt::ptr(&place_info));

	todo;
	return 0;
}

// 002C9980
s32 CScene::SearchCopyModel(_UNKNOWN i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
	return -1;
}

// 002C9B80
void CScene::CharaObjectOnOff(ssize character_index, mgCMemory& stack)
{
	log_trace("CScene::{}({}, {})", __func__, character_index, fmt::ptr(&stack));

	todo;
}

// 002C9D40
u32 CScene::LoadVillager(int i1, int i2)
{
	log_trace("CScene::{}({}, {})", __func__, i1, i2);

	todo;
	return 0;
}

// 002CA3D0
u32 CScene::LoadSubVillager(int i1, int i2)
{
	log_trace("CScene::{}({}, {})", __func__, i1, i2);

	todo;
	return 0;
}

// 002CA3D0
bool CScene::RegisterVillager(int i1, int i2, int i3)
{
	log_trace("CScene::{}({}, {}, {})", __func__, i1, i2, i3);

	todo;
	return false;
}

// 002CA430
bool CScene::RegisterVillager(int i1, int i2, CVillagerPlaceInfo& place_info)
{
	log_trace("CScene::{}({}, {}, {})", __func__, i1, i2, fmt::ptr(&place_info));

	todo;
	return false;
}

// 002CA450
bool CScene::RegisterVillager(int i1, int i2, mgCMemory& stack)
{
	log_trace("CScene::{}({}, {}, {})", __func__, i1, i2, fmt::ptr(&stack));

	todo;
	return false;
}

// 002CA540
bool CScene::GetTalkEvent(glm::vec4& v, CSceneEventData& event_data)
{
	log_trace("CScene::{}({}, {})", __func__, fmt::ptr(&v), fmt::ptr(&event_data));

	todo;
	return false;
}

// 002CA880
void CScene::StepVillager()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002CACD0
void CScene::StayNearVillager(glm::vec4& v, _UNKNOWNPOINTER pi)
{
	log_trace("CScene::{}({}, {})", __func__, fmt::ptr(&v), fmt::ptr(pi));

	todo;
}

// 002CAE60
void CScene::CancelStayVillager(_UNKNOWNPOINTER pi)
{
	log_trace("CScene::{}({})", __func__, fmt::ptr(pi));

	todo;
}

// 002CAEE0
void CScene::StayVillager(int i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}

// 002CAF20
void CScene::CancelStayVillager(int i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}

// 002CAFD0
void CScene::ExModeVillager(int i)
{
	log_trace("CScene::{}({})", __func__, i);

	todo;
}

// 002CB010
void CScene::SetActiveVillager()
{
	log_trace("CScene::{}()", __func__);

	todo;
}

// 002CB110
void CScene::InScreenChara(InScreenCharaInfo& chara_info, float* unused)
{
	log_trace("CScene::{}({}, {})", __func__, fmt::ptr(&chara_info), fmt::ptr(unused));

	todo;
}

// 002CB5A0
void CScene::LoadGameObject(int i1, int i2, mgCMemory& stack)
{
	log_trace("CScene::{}({}, {}, {})", __func__, i1, i2, fmt::ptr(&stack));

	todo;
}

// 002CB900
s32 CScene::GetGameObjectEvent(glm::vec4& v, CSceneEventData& event_data)
{
	log_trace("CScene::{}({}, {})", __func__, fmt::ptr(&v), fmt::ptr(&event_data));

	todo;
	return -1;
}

// 002CBAA0
void CScene::DrawGameObject(ssize gameobj_index)
{
	log_trace("CScene::{}()", __func__, gameobj_index);

	todo;
}
