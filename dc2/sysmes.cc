#include "common/log.h"
#include "ls_mes.h"
#include "mg_memory.h"
#include "sysmes.h"

set_log_channel("sysmes")

// 01E74210
static mgCMemory SystemMesStack;
// 01E74240
static char alignas(16) SystemMesBuffer[0xD000];
// 01E81240
static char alignas(16) SysMesBuffer[80000];
// 01E94AC0
static ClsMes SystemMessage;
// 01E96CA0
static ClsMes SystemMessage2;
// 01E98E80
static ClsMes SystemMessage3;

namespace sysmes
{
  // 003739D0
  void SInit()
  {
    log_trace("SInit()");

    SystemMesStack.Initialize();
    SystemMessage = ClsMes();
    SystemMessage2 = ClsMes();
    SystemMessage3 = ClsMes();
  }
}