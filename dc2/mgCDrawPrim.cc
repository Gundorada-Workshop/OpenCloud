#include "mgCDrawPrim.h"

void mgCDrawPrim::Flush()
{
  EndDma();
  BeginDma();
}

void mgCDrawPrim::Vertex(int x, int y, int z)
{
  Vertex4(x << 4, y << 4, z);
}

void mgCDrawPrim::Vertex4(float v[3])
{
  Vertex4(static_cast<int>(v[0]), static_cast<int>(v[1]), static_cast<int>(v[2]));
}

void mgCDrawPrim::Vertex4(int v[3])
{
  Vertex4(v[0], v[1], v[2]);
}

void mgCDrawPrim::Color(float rgba[4])
{
  Color(static_cast<int>(rgba[0]), static_cast<int>(rgba[1]),
  static_cast<int>(rgba[2]), static_cast<int>(rgba[3]));
}

void mgCDrawPrim::TextureCrd(int s, int t)
{
  TextureCrd4(s << 4, t << 4);
}