#pragma once

#include "mgCMemory.h"
#include "mgCTexture.h"

class mgCDrawPrim
{
public:
  // 001343a0
  mgCDrawPrim();

  // 00134410
  void Initialize(mgCMemory* memory);

  // 001344a0
  void Begin();

  // 00134530
  void BeginDma();

  // 001345c0
  void EndDma();

  // 00134660
  void Flush();

  // 00134690
  void End();

  // 001346d0
  void Begin2();

  // 00134860
  void BeginPrim2(int);

  // 00134890
  void BeginPrim2(unsigned int, unsigned int, int);

  // 00134940
  void EndPrim2();

  // 00134a20
  void End2();

  // 00134aa0
  void Data0(float[4]);

  // 00134ac0
  void Data4(float[4]);

  // 00134ae0
  void Data(int[4]);

  // 00134b00
  void DirectData(int);

  // 00134b20
  // note: x and y are fixed point (>> 4)
  void Vertex(int x, int y, int z);

  // 00134b30
  void Vertex(float x, float y, float z);

  // 00134bb0
  void Vertex4(int x, int y, int z);

  // 00134b70
  void Vertex4(float v[3]);

  // 00134c60
  void Vertex4(int v[3]);

  // 00134c80
  void Color(int r, int g, int b, int a);

  // 00134cf0
  void Color(float rgba[4]);

  // 00134d30
  // fixed point (<< 4)
  void TextureCrd4(int s, int t);

  // 00134d70
  void TextureCrd(int s, int t);

  // 00134d80
  void Direct(unsigned long, unsigned long);

  // 00134da0
  void Texture(mgCTexture* texture);

  // 00134ec0
  void AlphaBlendEnable(int);

  // 00134ee0
  void AlphaBlend(int);

  // 00134ef0
  void AlphaTestEnable(int);

  // 00134f10
  void AlphaTest(int, int);

  // 00134f50
  // destination alpha
  void DAlphaTest(int, int);

  // 00134f90
  void DepthTestEnable(int);

  // 00134ff0
  void DepthTest(int);

  // 00135090
  void ZMask(int);

  // 001350a0
  void TextureMapEnable(int);

  // 001350c0
  void Bilinear(int);

  // 001350d0
  void Shading(int);

  // 001350f0
  void AntiAliasing(int);

  // 00135110
  void FogEnable(int);

  // 00135130
  void Coord(int);

  // 00135140
  void GetOffset(int*, int*);
};
