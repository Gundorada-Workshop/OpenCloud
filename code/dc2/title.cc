#include "common/debug.h"

#include "dc2/title.h"

// 01F06070
static mgCMemory DataBuffer{};
// 01F060A0
static mgCMemory TitleMapBuffer{};
// 01F060D0
static mgCMemory TitleWorkBuffer{};
// 01F06100
static mgCMemory Stack_ReadBuff{};
// 01F06130
static mgCMemory Stack_MenuCharaBuff_Fix{};
// 01F06160
static std::array<mgCMemory, 5> Stack_MenuCharaBuff{};
// 01F062D0
static SHDDINFO HDDINFO{};
