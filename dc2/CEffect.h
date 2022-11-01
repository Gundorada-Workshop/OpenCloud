#pragma once
#include <array>
#include "common/debug.h"
#include "common/types.h"
#include "mgCTexture.h"

class CEffect
{
public:

};

class CFireRaster : public mgCTexture
{
public:
  // 001847C0
  void Initialize();

  // FIXME: Unknown inner type (or even if it is an array?) (size 0x20)
  std::array<std::array<char, 32>, 20> m_unk_field_70;
};