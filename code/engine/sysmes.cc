#include "common/log.h"

#include "engine/ls_mes.h"
#include "engine/mg/mg_memory.h"
#include "engine/sysmes.h"

set_log_channel("sysmes")

// 01E74210
static mgCMemory SystemMesStack{};
// 01E74240
static std::array<char, 0xD000> ALIGN(0x10) SystemMesBuffer{};
// 01E81240
static std::array<char, 80000> ALIGN(0x10) SysMesBuffer{};
// 01E94AC0
static ClsMes SystemMessage{};
// 01E96CA0
static ClsMes SystemMessage2{};
// 01E98E80
static ClsMes SystemMessage3{};
