#pragma once

// ~ 001A2080 - 001A76C0

// TODO THIS FILE
class CEditCollision
{
  // SIZE 0x50
};

struct MoveCheckInfo
{
  // TODO
  // SIZE 0x110
};

struct SLadderData
{
  // TODO
  // SIZE 0xD0
};

enum class EViewMode
{
  Walk = 0,
  _1 = 1,
  _2 = 2,
};

enum class ELadderMode
{
  Off = 0,
  _1 = 1,
  _2 = 2,
};

enum class ECharaMotionMode
{
  _0 = 0,
  _1 = 1,
};

// 001A4120
bool EditOnGround();

// 001A4160
bool IsWalkMode();
