#include "common/log.h"

#include "dc2/menuaqua.h"
#include "dc2/mg/mg_lib.h"

set_log_channel("menuaqua");

// 01ECC410
mgCMemory Aquarium_NameregistStack{};
// 01ECC530
CAquarium Aquarium{};
// 01ECC900
mgCMemory GyoraceFishSelStack{};
// 01ECC990
mgCMemory GyoraceStack{};
