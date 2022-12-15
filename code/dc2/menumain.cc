#include "common/log.h"

#include "dc2/font.h"
#include "dc2/menumain.h"
#include "dc2/mg/mg_lib.h"

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

// 002506C0
sint GetRandI(sint n)
{
  return rand() % n;
}

// 00250700
f32 GetRandF(f32 n)
{
  return mgRnd() * n;
}

// 002507D0
f32 MenuAdjustPolygonScale(mgCFrame* frame, f32 scale)
{
  log_trace("{}({}, {})", __func__, fmt::ptr(frame), scale);

  todo;
  return 0.0f;
}

// 002516C0
// Returns number of digits in a number
u32 GetNumberKeta(s32 n)
{
  log_trace("{}({})", __func__, n);

  n = std::abs(n);
  u32 digits = 1;
  
  for (; n < 10; ++digits)
  {
    n /= 10;
  }

  return digits;
}

// 00251720
s32 GetDispVolumeForFloat(f32 f)
{
  s32 result = static_cast<s32>(f);

  if (f - result < 0.00005f)
  {
    return result;
  }
  return result + 1;
}

// 00251780
f32 GetFloatCommaValue(f32 f)
{
  log_trace("{}({})", __func__, f);

  return f - truncf(f);
}
