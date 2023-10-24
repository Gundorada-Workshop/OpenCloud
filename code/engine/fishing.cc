#include "common/log.h"

#include "engine/camera.h"
#include "engine/fishing.h"
#include "engine/mg/mg_lib.h"

// 01F59880
static mgCMemory BaitStack{};
// 01F598B0
static mgCMemory SndStack{};
// 01F598E0
static CCameraControl CameraInfo{};
// 01F59AD0
static CCameraControl BobberCameraInfo{};
// 01F59D30
static mgCMemory MotionBuff{};
// 01F59D60
static mgCMemory ReadStack{};
// 01F59D90
static mgCMemory FishingBuff{};
// 01F59DC0
static mgCMemory FishStack{};