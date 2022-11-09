#include "common/log.h"
#include "font.h"
#include "menumain.h"
#include "mg_lib.h"

set_log_channel("menumain");

// 01ECD4F0
mgCMemory MainMenuStack;
// 01ECD520
mgCMemory MainMenuStack_Next;
// 01ECD590
mgCMemory MenuMainTextureReadBuf;
// 01ECD5C0
mgCMemory MenuSoundBuffer;
// 01ECD730
CFont TopicFont;

namespace menumain
{
  // 00374440
  void SInit()
  {
    log_trace("SInit()");

    MainMenuStack.Initialize();
    MainMenuStack_Next.Initialize();
    MenuMainTextureReadBuf.Initialize();
    MenuSoundBuffer.Initialize();
    new (&TopicFont) CFont();
  }
}