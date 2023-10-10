#include "common/log.h"

#include "engine/helpmes.h"
#include "engine/ls_mes.h"

set_log_channel("helpmes");

// 01F609D0
static ClsMes HelpMes{};
// 01F62BB0
static SHelpMesInfo HelpMesInfo{};