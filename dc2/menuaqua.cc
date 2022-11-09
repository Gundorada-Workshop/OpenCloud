#include "common/log.h"
#include "menuaqua.h"
#include "mg_lib.h"

set_log_channel("menuaqua");

// 01ECC410
mgCMemory Aquarium_NameregistStack;
// 01ECC530
CAquarium Aquarium;
// 01ECC900
mgCMemory GyoraceFishSelStack;
// 01ECC990
mgCMemory GyoraceStack;

namespace menuaqua
{
  // 003742B0
  void SInit()
  {
    log_trace("SInit()");

    Aquarium_NameregistStack.Initialize();
    new (&Aquarium) CAquarium();
    GyoraceFishSelStack.Initialize();
    GyoraceStack.Initialize();
  }
}