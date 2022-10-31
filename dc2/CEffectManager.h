#pragma once

class CEffectManager
{
public:
  void GetBufferNums(const char* script, int script_size, int* unk, int* unk2);
  void GetEffectNums(int unk0, int unk2);

public:
  // 0x34
  int count{ };
  // 0x220
  int alpha_blend{ };
  // 0x224
  int alpha_type{ };
  // 0x228
  int alpha{ };
};
