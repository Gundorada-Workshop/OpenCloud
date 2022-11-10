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

// 0023A5C0
void CMENU_USERPARAM::Initialize()
{
  log_trace("CMENU_USERPARAM::Initialize()");

  m_unk_field_4 = 0;
  m_unk_field_0 = 0;
  m_unk_field_8 = 0;
  m_unk_field_C = 0;
  m_unk_field_10 = 0;
  m_unk_field_14 = 0;
}

// 0023A670
void MENU_ASKMODE_PARA::Initialize()
{
  log_trace("MENU_ASKMODE_PARA::Initialize()");

  memset(this, 0, sizeof(this));
}

// 002370B0
CBaseMenuClass::CBaseMenuClass()
{
  log_trace("CBaseMenuClass::CBaseMenuClass()");
  
  // BUG: The constructor sets member variables before this,
  // and this also destroys the virtual function table ptr!!
  // I hope one day to be able to understand the internal machinations of Kenji.
  memset(this, 0, sizeof(this));
}

// 00239DA0
void CBaseMenuClass::SetAskParam(MENU_ASKMODE_PARA* param)
{
  log_trace("CBaseMenuClass::SetAskParam({})", fmt::ptr(param));

  if (param == nullptr)
  {
    m_unk_field_58.Initialize();
  }
  else
  {
    m_unk_field_58 = *param;
  }
}