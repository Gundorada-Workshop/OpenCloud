#include "common/log.h"

#include "dc2/camera.h"
#include "dc2/fishing.h"
#include "dc2/mg/mg_lib.h"

// 01F59880
static mgCMemory EsaStack{};
// 01F598B0
static mgCMemory SndStack{};
// 01F598E0
static CCameraControl CameraInfo{};
// 01F59AD0
static CCameraControl UkiCameraInfo{};
// 01F59D30
static mgCMemory MotionBuff{};
// 01F59D60
static mgCMemory ReadStack{};
// 01F59D90
static mgCMemory FishingBuff{};
// 01F59DC0
static mgCMemory FishStack{};