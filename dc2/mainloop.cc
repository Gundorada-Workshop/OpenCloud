#include <string>

#include "common/debug.h"
#include "common/log.h"

#include "dc2/editdata.h"
#include "dc2/ls_mes.h"
#include "dc2/mainloop.h"
#include "dc2/menusave.h"
#include "dc2/mg_memory.h"
#include "dc2/mg_texture.h"
#include "dc2/scene.h"
#include "dc2/quest.h"
#include "dc2/userdata.h"

set_log_channel("mainloop")

// 00376FB4
u32 s_system_snd_id{ 0 };

// 00376FC0
Language LanguageCode{ Language::English };

// 00376FE4
static CSaveData* ActiveSaveData{};

// 00376FEC
static bool PlayTimeCountFlag{ false };

// 003D8070
static SDebugInfo DebugInfo{};
// 003D8090
static CFont Font{};
// 003D8140
static SInitArg InitArg{};
// 003D8190
static SInitArg NextInitArg{};
// 003D81E0
static SInitArg PrevInitArg{};
// 003D8230
// FIXME: 0x1A000000 bytes (26MB) in PS2. Might need to adjust slightly for windows.
// Bumped up to 40MB (0x28000000) on Windows (to adjust for slightly bigger datatypes)
static alignas(16) std::array<char, 0x28000000> main_buffer{};
// 01DD8230
static mgCMemory MainBuffer{};
// 01DD8260
static CScene MainScene{};
// 01DE87B0
static std::array<char, 0x1900> SystemSeBuff{};
// 01DEA0B0
static mgCMemory SystemSeStack{};
// 01E017E0
static mgCMemory InfoStack{};
// 01E01810
static CSaveData SaveData{};
// 01E67180
static mgCMemory MenuBuffer{};
// 01E672B0
static std::array<mgCTexture, 2> FontTex{};
// 01E67390
static ClsMes PauseMes{};

// 00190840
CFont* GetDebugFont()
{
	log_trace("{}()", __func__);

	return &Font;
}

// 00190860
u32 GetSystemSndId(void)
{
	return s_system_snd_id;
}

// 00190880
CSaveData* GetSaveData()
{
	return ActiveSaveData;
}

// 001908F0
mgCMemory* GetMainStack()
{
	log_trace("{}()", __func__);

	return &MainBuffer;
}

// 00190BE0
void PlayTimeCount(bool flag)
{
	PlayTimeCountFlag = flag;
}

// 00190BF0
bool GetPlayTimeCountFlag()
{
	return PlayTimeCountFlag;
}

// 00190CB0
void MainLoop()
{
	log_trace("{}()", __func__);

	todo;
}
