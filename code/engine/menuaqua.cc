#include "common/log.h"

#include "engine/menuaqua.h"
#include "engine/mg/mg_lib.h"

set_log_channel("menuaqua");

// 01ECC410
mgCMemory Aquarium_NameregistStack{};
// 01ECC530
CAquarium Aquarium{};
// 01ECC900
mgCMemory GyoraceFishSelStack{};
// 01ECC990
mgCMemory GyoraceStack{};
