#pragma once
#include <array>

#include "engine/character.h"
#include "engine/scene.h"
#include "engine/mg/mg_camera.h"

#include "common/debug.h"
#include "common/types.h"

// ~ 00254E60 - 00255B80

// 00377CCC
extern CScene* EventScene;

// 002554C0
void SkipEventStart();

// 00255B20
mgCCamera* GetActiveCamera();

// 00255B50
CCharacter2* GetCharacter(ssize chara_id);
