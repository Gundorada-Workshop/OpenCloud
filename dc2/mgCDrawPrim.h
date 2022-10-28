#pragma once

class mgCDrawPrim
{
public:
  mgCDrawPrim();

  // 00134c80
  void Color(int r, int g, int b, int a);

  // 00134b20
  // note: x and y are fixed point (>> 4)
  void Vertex(int x, int y, int z);
};
