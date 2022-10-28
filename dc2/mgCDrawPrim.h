#pragma once

#include "common/types.h"

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
  void BeginPrim2(uint, uint, sint);

  // 00134940
  void EndPrim2();

  // 00134a20
  void End2();

  // 00134aa0
  void Data0(vec4);

  // 00134ac0
  void Data4(vec4);

  // 00134ae0
  void Data(ivec4);

  // 00134b00
  void DirectData(sint);

  // 00134b20
  // note: x and y are fixed point (>> 4)
  void Vertex(sint x, sint y, sint z);

  // 00134b30
  void Vertex(f32 x, f32 y, f32 z);

  // 00134bb0
  void Vertex4(sint x, sint y, sint z);

  // 00134b70
  void Vertex4(vec3);

  // 00134c60
  void Vertex4(ivec3);

  // 00134c80
  void Color(sint r, sint g, sint b, sint a);

  // 00134cf0
  void Color(vec4);

  // 00134d30
  // fixed point (<< 4)
  void TextureCrd4(sint s, sint t);

  // 00134d70
  void TextureCrd(sint s, sint t);

  // 00134d80
  void Direct(ulong, ulong);

  // 00134da0
  void Texture(mgCTexture* texture);

  // 00134ec0
  void AlphaBlendEnable(sint);

  // 00134ee0
  void AlphaBlend(sint);

  // 00134ef0
  void AlphaTestEnable(sint);

  // 00134f10
  void AlphaTest(sint, sint);

  // 00134f50
  // destination alpha
  void DAlphaTest(sint, sint);

  // 00134f90
  void DepthTestEnable(sint);

  // 00134ff0
  void DepthTest(sint);

  // 00135090
  void ZMask(sint);

  // 001350a0
  void TextureMapEnable(sint);

  // 001350c0
  void Bilinear(sint);

  // 001350d0
  void Shading(sint);

  // 001350f0
  void AntiAliasing(sint);

  // 00135110
  void FogEnable(sint);

  // 00135130
  void Coord(sint);

  // 00135140
  void GetOffset(sint*, sint*);
};
