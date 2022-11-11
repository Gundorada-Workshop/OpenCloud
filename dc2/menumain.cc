#include "common/log.h"
#include "font.h"
#include "menumain.h"
#include "mg_lib.h"

set_log_channel("menumain");

// 01ECD4F0
mgCMemory MainMenuStack{};
// 01ECD520
mgCMemory MainMenuStack_Next{};
// 01ECD590
mgCMemory MenuMainTextureReadBuf{};
// 01ECD5C0
mgCMemory MenuSoundBuffer{};
// 01ECD730
CFont TopicFont{};

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
    new (&m_unk_field_58) MENU_ASKMODE_PARA();
  }
  else
  {
    m_unk_field_58 = *param;
  }
}