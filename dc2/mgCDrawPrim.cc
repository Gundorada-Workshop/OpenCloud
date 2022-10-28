#include "mgCDrawPrim.h"

void mgCDrawPrim::BeginDma()
{
  // TODO
}

void mgCDrawPrim::EndDma()
{
  // TODO
}

void mgCDrawPrim::Color(sint, sint, sint, sint)
{
  // TODO
}

void mgCDrawPrim::TextureCrd4(int, int)
{
  // TODO
}

void mgCDrawPrim::Vertex4(int, int, int)
{
  // TODO
}

void mgCDrawPrim::Flush()
{
  EndDma();
  BeginDma();
}

void mgCDrawPrim::Vertex(sint x, sint y, sint z)
{
  Vertex4(x << 4, y << 4, z);
}

void mgCDrawPrim::Vertex4(vec3 v)
{
  Vertex4(static_cast<sint>(v[0]), static_cast<sint>(v[1]), static_cast<sint>(v[2]));
}

void mgCDrawPrim::Vertex4(ivec3 v)
{
  Vertex4(v[0], v[1], v[2]);
}

void mgCDrawPrim::Color(vec4 rgba)
{
  Color(static_cast<sint>(rgba[0]), static_cast<sint>(rgba[1]),
  static_cast<sint>(rgba[2]), static_cast<sint>(rgba[3]));
}

void mgCDrawPrim::TextureCrd(sint s, sint t)
{
  TextureCrd4(s << 4, t << 4);
}