#include "common/log.h"

#include "dc2/subgame.h"

set_log_channel("subgame");

// 01F59E30
static SubGameInfo GameInfo{};

// 00303FC0
void sgInitSubGame(MAYBE_UNUSED ESubGameID game_id, MAYBE_UNUSED SubGameInfo* sub_game_info)
{
  log_trace("{}({}, {})", __func__, s32(game_id), fmt::ptr(sub_game_info));

  todo;
}
