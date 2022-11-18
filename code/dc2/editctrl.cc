#include <glm/glm.hpp>

#include "common/log.h"

#include "dc2/editctrl.h"

set_log_channel("editctrl");

// 01E9B1C0
static MoveCheckInfo MoveInfo{};
// 01E9B2D0
static glm::vec4 OldFixCameraPos{ 0 };
// 01E9B2E0
static glm::vec4 OldCameraPos{ 0 };
// 01E9B2F0
static SLadderData LadderData{};
// 01E9B3C0
static glm::vec4 LdrPos{ 0 };
// 01E9B3D0
static glm::vec4 StdPos{ 0 };
// 01E9B3E0
static glm::vec4 LdrBottomPos{ 0 };
// 01E9B3F0
static glm::vec4 LdrTopPos{ 0 };
// 01E9B400
static glm::vec4 LdrTopWalk{ 0 };
// 01E9B410
static glm::vec4 LdrCamPos{ 0 };
