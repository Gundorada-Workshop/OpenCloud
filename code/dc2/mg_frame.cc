#include <string.h>

#include "common/log.h"

#include "dc2/mg_frame.h"

set_log_channel("mg_frame");

// 00376C70
s32 mgScreenWidth{0};
// 00376C74
s32 mgScreenHeight{0};
// 00380DA0
static mgCFrameAttr dmy_attr{};

// 00133740
int mgCVisual::Iam()
{
  log_trace("mgCVisual::{}()", __func__);

  return 0;
}

// 00134300
int mgCVisual::GetMaterialNum()
{
  log_trace("mgCVisual::{}()", __func__);

  return 0;
}

// 00134310
_UNKNOWNPOINTER mgCVisual::GetpMaterial()
{
  log_trace("mgCVisual::{}()", __func__);

  return nullptr;
}

// 00134320
_UNKNOWNPOINTER mgCVisual::GetMaterial(ssize index)
{
  log_trace("mgCVisual::{}({})", __func__, index);

  return nullptr;
}

// 00133750
mgCVisual* mgCVisual::Copy(mgCMemory& stack)
{
  log_trace("mgCVisual::{}({})", __func__, fmt::ptr(&stack));

  return this;
}

// 00134330
bool mgCVisual::CreateBBox(vec4& v1, vec4& v2, matrix4& m1)
{
  log_trace("mgCVisual::{}({}, {}, {})", __func__, fmt::ptr(&v1), fmt::ptr(&v2), fmt::ptr(&m1));

  return false;
}

// 00134340
_UNKNOWNPOINTER mgCVisual::CreateRenderInfoPacket(_UNKNOWNPOINTER p, matrix4& m1, mgRENDER_INFO& render_info)
{
  log_trace("mgCVisual::{}({}, {}, {})", __func__, fmt::ptr(p), fmt::ptr(&m1), fmt::ptr(&render_info));

  return nullptr;
}
// 001342F0
_UNKNOWNPOINTER mgCVisual::CreatePacket(mgCMemory& mem1, mgCMemory& mem2)
{
  log_trace("mgCVisual::{}({}, {})", __func__, fmt::ptr(&mem1), fmt::ptr(&mem2));

  return nullptr;
}

// 00134360
_UNKNOWNPOINTER mgCVisual::Draw(matrix4& m1, mgCDrawManager& draw_man)
{
  log_trace("mgCVisual::{}({}, {})", __func__, fmt::ptr(&m1), fmt::ptr(&draw_man));

  return Draw(nullptr, m1, draw_man);
}

// 00134350
_UNKNOWNPOINTER mgCVisual::Draw(_UNKNOWNPOINTER p, matrix4& m1, mgCDrawManager& draw_man)
{
  log_trace("mgCVisual::{}({}, {}, {})", __func__, fmt::ptr(p), fmt::ptr(&m1), fmt::ptr(&draw_man));

  return nullptr;
}

// 00132DC0
mgCVisual::mgCVisual()
{
  log_trace("mgCVisual::mgCVisual()");

  m_unk_field_0 = 0;
  m_unk_field_4 = 0;
  m_unk_field_8 = 0;
  m_unk_field_10 = 0;
  m_unk_field_14 = 0;
}

// 00134280
int mgCVisualMDT::Iam()
{
  log_trace("mgCVisualMDT::{}()", __func__);

  return 1;
}

// 00134290
int mgCVisualMDT::GetMaterialNum()
{
  log_trace("mgCVisualMDT::{}()", __func__);

  return m_material_num;
}

// 001342A0
_UNKNOWNPOINTER mgCVisualMDT::GetpMaterial()
{
  log_trace("mgCVisualMDT::{}()", __func__);

  return m_p_material;
}

// 0013EF60
_UNKNOWNPOINTER mgCVisualMDT::GetMaterial(ssize index)
{
  log_trace("mgCVisualMDT::{}({})", __func__, index);

  todo;
  return nullptr;
}

// 0013EFC0
bool mgCVisualMDT::CreateBBox(vec4& v1, vec4& v2, matrix4& m1)
{
  log_trace("mgCVisualMDT::{}({}, {}, {})", __func__, fmt::ptr(&v1), fmt::ptr(&v2), fmt::ptr(&m1));

  if (m_unk_field_20 <= 0)
  {
    return false;
  }

  matrix4* mat = m_unk_field_30;
  if (mat == nullptr)
  {
    return false;
  }
  else
  {
    // 0013EFF0
    todo;
    return true;
  }
}

// 001404D0
_UNKNOWNPOINTER mgCVisualMDT::CreateRenderInfoPacket(_UNKNOWNPOINTER p, matrix4& m1, mgRENDER_INFO& render_info)
{
  log_trace("mgCVisualMDT::{}({}, {}, {})", __func__, fmt::ptr(p), fmt::ptr(&m1), fmt::ptr(&render_info));

  todo;
  return nullptr;
}

// 001342B0
_UNKNOWNPOINTER mgCVisualMDT::Draw(matrix4& m1, mgCDrawManager& draw_man)
{
  log_trace("mgCVisualMDT::{}({}, {})", __func__, fmt::ptr(&m1), fmt::ptr(&draw_man));

  return Draw(nullptr, m1, draw_man);
}

// 0013F4E0
_UNKNOWNPOINTER mgCVisualMDT::Draw(_UNKNOWNPOINTER p, matrix4& m1, mgCDrawManager& draw_man)
{
  log_trace("mgCVisualMDT::{}({}, {}, {})", __func__, fmt::ptr(p), fmt::ptr(&m1), fmt::ptr(&draw_man));

  return nullptr;
}


// 0013EAC0
mgCVisualMDT::mgCVisualMDT()
{
  log_trace("mgCVisualMDT::mgCVisualMDT()");

  m_unk_field_20 = 0;
  m_unk_field_30 = nullptr;
  m_unk_field_24 = 0;
  m_unk_field_34 = 0;
  m_unk_field_38 = 0;
  m_unk_field_3C = 0;
  m_material_num = 0;
  m_p_material = nullptr;
  m_unk_field_48 = 0;
  
  m_unk_field_10 = 60;
  m_unk_field_14 = 180;
}

// 0013F6A0
_DWORD mgCVisualMDT::CreatePacket(mgCDrawManager& draw_man)
{
  log_trace("mgCVisualMDT::{}({})", __func__, fmt::ptr(&draw_man));

  todo;
  return 0;
}

// 0013FF60
_DWORD mgCVisualMDT::CreateFacePacket(_UNKNOWNPOINTER p, mgCFace& face)
{
  log_trace("mgCVisualMDT::{}({}, {})", __func__, fmt::ptr(p), fmt::ptr(&face));

  todo;
  return 0;
}

// 0013F010
mgCFace* mgCVisualMDT::CreateFace(FACES_ID& faces_id, mgCMemory& mem1, mgCMemory& mem2, mgCFace&& faces)
{
  log_trace("mgCVisualMDT::{}({}, {}, {}, {})", __func__, fmt::ptr(&faces_id), fmt::ptr(&mem1), fmt::ptr(&mem2), fmt::ptr(&faces));

  todo;
  return nullptr;
}

// 00140BE0
_UNKNOWNPOINTER mgCVisualMDT::CreateExtRenderInfoPacket(_UNKNOWNPOINTER p, matrix4& m1, mgRENDER_INFO& render_info)
{
  log_trace("mgCVisualMDT::{}({}, {}, {})", __func__, fmt::ptr(p), fmt::ptr(&m1), fmt::ptr(&render_info));

  return nullptr;
}

// 0013F290
bool mgCVisualMDT::DataAssignMT(MDT_HEADER* mdt_header, mgCMemory& stack, mgCTextureManager* texture_man)
{
  log_trace("mgCVisualMDT::{}({}, {}, {})", __func__, fmt::ptr(mdt_header), fmt::ptr(&stack), fmt::ptr(texture_man));

  todo;
  return false;
}

// 0013BCB0
mgC3DSprite::mgC3DSprite()
{
  log_trace("mgC3DSprite::mgC3DSprite()");

  m_unk_field_20 = 0;
}

// 00134410
mgCDrawPrim::mgCDrawPrim(mgCMemory* memory, sceVif1Packet* vif1_packet)
{
  log_trace("mgCDrawPrim::mgCDrawPrim({}, {})", fmt::ptr(memory), fmt::ptr(vif1_packet));

  todo;
}

// 001344A0
void mgCDrawPrim::Begin(int i)
{
  log_trace("mgCDrawPrim::{}({})", __func__, i);

  todo;
}


// 00134530
void mgCDrawPrim::BeginDma()
{
  log_trace("mgCDrawPrim::{}()", __func__);

  todo;
}

// 001345C0
void mgCDrawPrim::EndDma()
{
  log_trace("mgCDrawPrim::{}()", __func__);

  todo;
}

// 00134660
void mgCDrawPrim::Flush()
{
  log_trace("mgCDrawPrim::{}()", __func__);

  EndDma();
  BeginDma();
}

// 00134690
void mgCDrawPrim::End()
{
  log_trace("mgCDrawPrim::{}()", __func__);

  todo;
}

// 001346D0
void mgCDrawPrim::Begin2()
{
  log_trace("mgCDrawPrim::{}()", __func__);

  todo;
}

// 00134860
void mgCDrawPrim::BeginPrim2(sint i)
{
  log_trace("mgCDrawPrim::{}({})", __func__, i);

  todo;
}

// 00134860
void mgCDrawPrim::BeginPrim2(sint i1, uint i2, uint i3, uint i4)
{
  log_trace("mgCDrawPrim::{}({}, {}, {}, {})", __func__, i1, i2, i3, i4);

  todo;
}

// 00134940
void mgCDrawPrim::EndPrim2()
{
  log_trace("mgCDrawPrim::{}()", __func__);

  todo;
}

// 00134A20
void mgCDrawPrim::End2()
{
  log_trace("mgCDrawPrim::{}()", __func__);

  todo;
}

// 00134AA0
void mgCDrawPrim::Data0(vec4 v)
{
  log_trace("mgCDrawPrim::{}(({}, {}, {}, {}))", __func__, v.x, v.y, v.z, v.w);

  todo;
}

// 00134AC0
void mgCDrawPrim::Data4(vec4 v)
{
  log_trace("mgCDrawPrim::{}(({}, {}, {}, {}))", __func__, v.x, v.y, v.z, v.w);

  todo;
}

// 00134AE0
void mgCDrawPrim::Data(glm::ivec4 v)
{
  log_trace("mgCDrawPrim::{}(({}, {}, {}, {}))", __func__, v.x, v.y, v.z, v.w);

  todo;
}

// 00134AE0
void mgCDrawPrim::DirectData(int i)
{
  log_trace("mgCDrawPrim::{}({})", __func__, i);

  todo;
}

// 00134B20
void mgCDrawPrim::Vertex(int x, int y, int z)
{
  log_trace("mgCDrawPrim::{}({}, {}, {})", __func__, x, y, z);

  Vertex4(x << 4, y << 4, z);
}

// 00134B30
void mgCDrawPrim::Vertex(float x, float y, float z)
{
  log_trace("mgCDrawPrim::{}({}, {}, {})", __func__, x, y, z);

  todo;
}

// 00134B70
void mgCDrawPrim::Vertex(glm::vec3 v)
{
  log_trace("mgCDrawPrim::{}({}, {}, {})", __func__, v.x, v.y, v.z);

  todo;
}

// 00134BB0
void mgCDrawPrim::Vertex4(int x, int y, int z)
{
  log_trace("mgCDrawPrim::{}({}, {}, {})", __func__, x, y, z);

  todo;
}

// 00134C60
void mgCDrawPrim::Vertex4(glm::ivec3 v)
{
  log_trace("mgCDrawPrim::{}({}, {}, {})", __func__, v.x, v.y, v.z);

  Vertex4(v[0], v[1], v[2]);
}

void mgCDrawPrim::Vertex4(glm::vec3 v)
{
  log_trace("mgCDrawPrim::{}({}, {}, {})", __func__, v.x, v.y, v.z);

  Vertex4(static_cast<sint>(v.x), static_cast<sint>(v.y), static_cast<sint>(v.z));
}

// 00134C80
void mgCDrawPrim::Color(sint r, sint g, sint b, sint a)
{
  log_trace("mgCDrawPrim::{}({}, {}, {}, {})", __func__, r, g, b, a);

  todo;
}

// 00134CF0
void mgCDrawPrim::Color(vec4 rgba)
{
  log_trace("mgCDrawPrim::{}(({}, {}, {}, {}))", __func__, rgba.r, rgba.g, rgba.b, rgba.a);

  Color(static_cast<sint>(rgba[0]), static_cast<sint>(rgba[1]),
    static_cast<sint>(rgba[2]), static_cast<sint>(rgba[3]));
}

// 00134D30
void mgCDrawPrim::TextureCrd4(int s, int t)
{
  log_trace("mgCDrawPrim::{}({}, {})", __func__, s, t);

  todo;
}

// 00134D70
void mgCDrawPrim::TextureCrd(sint s, sint t)
{
  log_trace("mgCDrawPrim::{}({}, {})", __func__, s, t);

  TextureCrd4(s << 4, t << 4);
}

// 00134D80
void mgCDrawPrim::Direct(ulong i1, ulong i2)
{
  log_trace("mgCDrawPrim::{}({}, {})", __func__, i1, i2);

  todo;
}

// 00134DA0
void mgCDrawPrim::Texture(mgCTexture* texture)
{
  log_trace("mgCDrawPrim::{}({})", __func__, fmt::ptr(texture));

  todo;
}

// 00134EC0
void mgCDrawPrim::AlphaBlendEnable(bool value)
{
  log_trace("mgCDrawPrim::{}({})", __func__, value);

  todo;
}

// 00134EE0
void mgCDrawPrim::AlphaBlend(int alpha_mode)
{
  log_trace("mgCDrawPrim::{}({})", __func__, alpha_mode);

  todo;
}

// 00134EF0
void mgCDrawPrim::AlphaTestEnable(bool value)
{
  log_trace("mgCDrawPrim::{}({})", __func__, value);

  todo;
}

// 00134EE0
void mgCDrawPrim::AlphaTest(int i1, int i2)
{
  log_trace("mgCDrawPrim::{}({}, {})", __func__, i1, i2);

  todo;
}

// 00134F50
void mgCDrawPrim::DAlphaTest(int i1, int i2)
{
  log_trace("mgCDrawPrim::{}({}, {})", __func__, i1, i2);

  todo;
}

// 00134EF0
void mgCDrawPrim::DepthTestEnable(bool value)
{
  log_trace("mgCDrawPrim::{}({})", __func__, value);

  todo;
}

// 00134FF0
void mgCDrawPrim::DepthTest(int i)
{
  log_trace("mgCDrawPrim::{}({})", __func__, i);

  todo;
}

// 00135090
void mgCDrawPrim::ZMask(int zmask)
{
  log_trace("mgCDrawPrim::{}({})", __func__, zmask);

  todo;
}

// 001350A0
void mgCDrawPrim::TextureMapEnable(bool value)
{
  log_trace("mgCDrawPrim::{}({})", __func__, value);

  todo;
}

// 001350C0
void mgCDrawPrim::Bilinear(bool value)
{
  log_trace("mgCDrawPrim::{}({})", __func__, value);

  todo;
}

// 001350D0
void mgCDrawPrim::Shading(bool value)
{
  log_trace("mgCDrawPrim::{}({})", __func__, value);

  todo;
}

// 001350F0
void mgCDrawPrim::AntiAliasing(bool value)
{
  log_trace("mgCDrawPrim::{}({})", __func__, value);

  todo;
}

// 00135110
void mgCDrawPrim::FogEnable(bool value)
{
  log_trace("mgCDrawPrim::{}({})", __func__, value);

  todo;
}

// 00135130
void mgCDrawPrim::Coord(int i)
{
  log_trace("mgCDrawPrim::{}({})", __func__, i);

  todo;
}

// 00135140
void mgCDrawPrim::GetOffset(int* i1, int*i2)
{
  log_trace("mgCDrawPrim::{}({}, {})", __func__, fmt::ptr(i1), fmt::ptr(i2));

  todo;
}

// 00135180
mgCDrawManager::mgCDrawManager()
{
  log_trace("mgCDrawManager::mgCDrawManager()");

  m_unk_field_68 = 0x40;
  m_unk_field_6C = 0;
  m_unk_field_70 = 0;
}

// 00138810
void mgCObject::ChangeParam()
{
  log_trace("mgCObject::ChangeParam()");

  m_unk_field_40 = true;
}

// 00138820
void mgCObject::UseParam()
{
  log_trace("mgCObject::UseParam()");

  m_unk_field_40 = true;
}

// 00136190
void mgCObject::SetPosition(const vec4& v)
{
  log_trace("mgCObject::SetPosition({}) (x, y, z = {}, {}, {})", fmt::ptr(&v), v.x, v.y, v.z);

  if (static_cast<glm::vec3>(v) == static_cast<glm::vec3>(m_position))
  {
    return;
  }

  m_unk_field_44 = true;
  m_position = v;
  m_position.w = 1.0f;
  m_unk_field_40 = true;
}

// 00136220
void mgCObject::SetPosition(float x, float y, float z)
{
  log_trace("mgCObject::SetPosition({}, {}, {})", x, y, z);

  vec4 pos = vec4(x, y, z, 1.0f);
  SetPosition(pos);
}

// 00136260
vec4 mgCObject::GetPosition()
{
  log_trace("mgCObject::GetPosition()");

  return m_position;
}

// 00136270
void mgCObject::SetRotation(const vec4& v)
{
  log_trace("mgCObject::SetRotation({}) (x, y, z = {}, {}, {})", fmt::ptr(&v), v.x, v.y, v.z);

  if (static_cast<glm::vec3>(v) == static_cast<glm::vec3>(m_rotation))
  {
    return;
  }

  m_unk_field_44 = true;
  m_rotation = v;
  m_rotation.w = 0.0f;
  m_unk_field_40 = true;
}

// 001362F0
void mgCObject::SetRotation(float x, float y, float z)
{
  log_trace("mgCObject::SetRotation({}, {}, {})", x, y, z);

  vec4 rot = vec4(x, y, z, 0.0f);
  SetPosition(rot);
}

// 00136330
vec4 mgCObject::GetRotation()
{
  log_trace("mgCObject::GetRotation()");

  return m_rotation;
}

// 00136340
void mgCObject::SetScale(const vec4& v)
{
  log_trace("mgCObject::SetScale({}) (x, y, z = {}, {}, {})", fmt::ptr(&v), v.x, v.y, v.z);

  if (static_cast<glm::vec3>(v) == static_cast<glm::vec3>(m_scale))
  {
    return;
  }

  m_unk_field_44 = true;
  m_scale = v;
  m_scale.w = 0.0f;
  m_unk_field_40 = true;
}

// 001363C0
void mgCObject::SetScale(float x, float y, float z)
{
  log_trace("mgCObject::SetScale({}, {}, {})", x, y, z);

  vec4 scale = vec4(x, y, z, 0.0f);
  SetScale(scale);
}

// 00136400
vec4 mgCObject::GetScale()
{
  log_trace("mgCObject::GetScale()");

  return m_scale;
}

// 00138840
_UNKNOWNPOINTER mgCObject::Draw()
{
  log_trace("mgCObject::Draw()");

  return nullptr;
}

// 00138830
_UNKNOWNPOINTER mgCObject::DrawDirect()
{
  log_trace("mgCObject::DrawDirect()");

  return nullptr;
}

// 00136410
mgCObject::mgCObject()
{
  log_trace("mgCObject::mgCObject()");

  SetPosition(0.0f, 0.0f, 0.0f);
  SetRotation(0.0f, 0.0f, 0.0f);
  SetScale(1.0f, 1.0f, 1.0f);
  m_unk_field_40 = true;
  m_unk_field_44 = false;
}

void mgCObject::Initialize()
{
  log_trace("mgCObject::Initialize()");
  log_warn("Initialize should not be called (unless the game actually uses this as a virtual method on unknown type)");
  new (this) mgCObject();
}

void mgCFrameBase::Initialize()
{
  log_trace("mgCFrameBase::Initialize()");
  log_warn("Initialize should not be called (unless the game actually uses this as a virtual method on unknown type)");
  new (this) mgCFrameBase();
}

void mgCFrame::Initialize()
{
  log_trace("mgCFrame::Initialize()");
  log_warn("Initialize should not be called (unless the game actually uses this as a virtual method on unknown type)");
  new (this) mgCFrame();
}

// 001387F0
_UNKNOWNPOINTER mgCFrame::Draw()
{
  log_trace("mgCFrame::Draw()");

  todo;
  return nullptr;
}

// 00136890
mgVu0FBOX mgCFrame::GetWorldBBox()
{
  log_trace("mgCFrame::GetWorldBBox()");

  todo;
  return mgVu0FBOX{};
}

// 00137E10
void mgCFrame::Draw(_UNKNOWNPOINTER p)
{
  log_trace("mgCFrame::Draw({})", fmt::ptr(p));

  todo;
}

// 00132D90
void mgCFrame::SetVisual(mgCVisual* visual)
{
  log_trace("mgCFrame::SetVisual({})", fmt::ptr(visual));

  todo;
}

// 00136590
void mgCFrame::SetName(const std::string& name)
{
  log_trace("mgCFrame::{}({})", __func__, name);

  m_name = name;
}

// 001365A0
void mgCFrame::SetTransMatrix(vec4& v)
{
  log_trace("mgCFrame::{}({})", __func__, fmt::ptr(&v));

  todo;
}

// 001365F0
void mgCFrame::SetBBox(vec4& corner1, vec4& corner2)
{
  log_trace("mgCFrame::{}(({}, {}, {}), ({}, {}, {}))", __func__,
    corner1.x, corner1.y, corner1.z, corner2.x, corner2.y, corner2.z);

  if (m_bound_info == nullptr)
  {
    return;
  }

  m_bound_info->m_corner1 = corner1;
  m_bound_info->m_corner2 = corner2;

  /*
  * The following code constructs all points of a 3D box, given the two corners.
  * Consider the following corners:
  * (1, 2, 3), (4, 5, 6)
  * 
  * This loop creates the following points (w/ w component = 1.0f) and stores it in m_bound_info:
  * (4, 5, 6)
  * (1, 5, 6)
  * (4, 2, 6)
  * (1, 2, 6)
  * (4, 5, 3)
  * (1, 5, 3)
  * (4, 2, 3)
  * (1, 2, 3)
  */
  vec4* bounds[2] = { &m_bound_info->m_corner2, &m_bound_info->m_corner1 };

  for (int i = 0; i < std::size(m_bound_info->m_vertices); ++i)
  {
    vec4* bound1 = bounds[(i & 1) != 0];
    vec4* bound2 = bounds[(i & 2) != 0];
    vec4* bound3 = bounds[(i & 4) != 0];

    m_bound_info->m_vertices[i].w = 1.0f;

    m_bound_info->m_vertices[i].x = bound1->x;
    m_bound_info->m_vertices[i].y = bound2->y;
    m_bound_info->m_vertices[i].z = bound3->z;
  }
}

mgCDrawEnv::mgCDrawEnv() : mgCDrawEnv(false) {}

// 001388B0
mgCDrawEnv::mgCDrawEnv(bool b)
{
  log_trace("mgCDrawEnv::mgCDrawEnv({})", b);

  // Pulled these from runtime
  // Metrowerks can go chew on a bag of rocks
  m_unk_field_0 = 0x10000000'00008003;
  m_unk_field_8 = 0x00000000'0000000E;
  m_unk_field_10 = 0x00000000'0005000B;
  m_unk_field_30 = 0x44;

  if (b)
  {
    m_unk_field_18 = 0x48;
    m_unk_field_28 = 0x4F;
    m_unk_field_38 = 0x43;
  }
  else
  {
    m_unk_field_18 = 0x47;
    m_unk_field_28 = 0x4E;
    m_unk_field_38 = 0x42;
  }
}

void mgCDrawEnv::SetAlpha(u8 alpha_mode)
{
  switch (alpha_mode)
  {
    case 4:
      m_unk_field_30 = 0x80'0000002A;
      break;
    case 3:
      m_unk_field_30 = 0x42;
      break;
    case 2:
      m_unk_field_30 = 0x48;
      break;
    case 1:
      m_unk_field_30 = 0x44;
      break;
    default:
      break;
  }
}

// 001389E0
u8 mgCDrawEnv::GetAlphaMacroID()
{
  log_trace("mgCDrawEnv::{}()", __func__);

  switch (m_unk_field_30)
  {
    case 0x80'0000002A:
      return 4;
    case 0x42:
      return 3;
    case 0x48:
      return 2;
    case 0x44:
      return 1;
    default:
      return 0;
  }
}

// 00138A40
void mgCDrawEnv::SetZBuf(int i)
{
  log_trace("mgCDrawEnv::{}({})", __func__, i);

  switch (i)
  {
    case 1:
      m_unk_field_24 &= ~1;
      break;
    case -1:
      m_unk_field_24 |= 1;
      break;
    default:
      break;
  }
}