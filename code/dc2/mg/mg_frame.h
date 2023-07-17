#pragma once
#include <array>

#include "common/debug.h"
#include "common/macros.h"
#include "common/types.h"

#include "graph/vector.h"

#include "dc2/mg/mg_math.h"
#include "dc2//mg/mg_memory.h"
#include "dc2/mg/mg_texture.h"

// ~ 00131B60 - 00139900

// THIS FILE TODO
class mgCMDTBuilder
{
};

class mgCVisualFixMDT
{
};

class mgMaterial
{
};

class mgCShadowMDT
{
};

class mgCSprite
{
};

class mgCVisualPrim
{
};

struct mgRENDER_INFO;
class mgCDrawManager;
class mgCTextureManager;
class mgCFrameManager;

extern mgCFrameManager mgFrameManager;

// 00376C70
extern s32 mgScreenWidth;
// 00376C74
extern s32 mgScreenHeight;

//template<typename T>
//struct mgRect
//{
//public:
//  // 0
//  T m_ax;
//
//  // 4
//  T m_ay;
//
//  // 8
//  T m_bx;
//
//  // C
//  T m_by;
//
//  // 0013E390 (s32)
//  // 001F24F0 (float)
//  // 002BFC30 (s16)
//  inline void Set(T ax, T ay, T bx, T by)
//  {
//    //log_trace("mgRect::Set({}, {}, {}, {})", ax, ay, bx, by);
//
//    m_ax = ax;
//    m_ay = ay;
//    m_bx = bx;
//    m_by = by;
//  }
//};

class mgCVisualAttr
{
public:
  // 0
  s32 m_unk_field_0{ -1 };

  // ?

  // 8
  s32 m_unk_field_8{ 1 };

  // ?

  // 14
  s32 m_unk_field_14{ -1 };

  // SIZE 0x18
};

struct FACES_ID
{
};

struct MDT_HEADER
{
};

class mgCFace
{
};

class mgCVisual
{
public:
  // 00132DC0
  mgCVisual();

public:
  // VTABLE 00374F10
  // 0  0
  // 4  0
  // 8  00133740
  virtual sint Iam();

  // C  00134300
  virtual sint GetMaterialNum();

  // 10 00134310
  virtual unkptr GetpMaterial();

  // 14 00134320
  virtual unkptr GetMaterial(ssize index);

  // 18 00133750 (NOTE: this class actually just returns its own reference :( )
  virtual mgCVisual* Copy(mgCMemory& stack);

  // 1C 00134330
  //virtual bool CreateBBox(const vec4& v1, const vec4& v2, const matrix4& m1);

  // 20 00134340
  //virtual unkptr CreateRenderInfoPacket(unkptr p, matrix4& m1, mgRENDER_INFO& render_info);

  // 24 001342F0
  virtual unkptr CreatePacket(mgCMemory& mem1, mgCMemory& mem2);

  // 28 00134360
  //virtual unkptr Draw(matrix4& m1, mgCDrawManager& draw_man);

  // 2C 00134350
  //virtual unkptr Draw(unkptr p, matrix4& m1, mgCDrawManager& draw_man);

  // 30 00132DC0
  //virtual void Initialize();

public:
  // 0
  unk32 m_unk_field_0{ 0 };

  // 4
  unk32 m_unk_field_4{ 0 };

  // 8
  unk32 m_unk_field_8{ 0 };

  // C
  unk32 m_unk_field_C{ 0};

  // 10
  s32 m_unk_field_10{ 0 };

  // 14
  s32 m_unk_field_14{ 0 };

  // 18
  unk32 m_unk_field_18{ 0 };
  
  // SIZE 0x20 (vtable @ 0x1C)
};

class mgCVisualMDT : public mgCVisual
{
public:
  // 0013EAC0
  mgCVisualMDT();

public:
  using mgCVisual::CreatePacket;

  // VTABLE 00375190
  // 0  0
  // 4  0
  // 8  00134280
  virtual sint Iam();

  // C  00134290
  virtual sint GetMaterialNum();

  // 10 001342A0
  virtual unkptr GetpMaterial();

  // 14 0013EF60
  virtual unkptr GetMaterial(ssize index);

  // 18 00133750 (mgCVisual::Copy)
  // 1C 0013EFC0
  //virtual bool CreateBBox(const vec4& v1, const vec4& v2, const matrix4& m1) override;

  // 20 001404D0
  //virtual unkptr CreateRenderInfoPacket(unkptr p, matrix4& m1, mgRENDER_INFO& render_info);

  // 24 001342F0 (mgCVisual::CreatePacket)
  // 28 001342B0
  //virtual unkptr Draw(matrix4& m1, mgCDrawManager& draw_man);

  // 2C 0013F4E0
  //virtual unkptr Draw(unkptr p, matrix4& m1, mgCDrawManager& draw_man);

  // 30 0013EAC0
  //virtual void Initialize();
  // 34 0013F6A0
  virtual unk32 CreatePacket(MAYBE_UNUSED mgCDrawManager& draw_man);

  // 38 0013FF60
  virtual unk32 CreateFacePacket(unkptr p, mgCFace& face);

  // 3C 0013F010
  virtual mgCFace* CreateFace(FACES_ID& faces_id, mgCMemory& mem1, mgCMemory& mem2, mgCFace&& faces);

  // 40 00140BE0
  //virtual unkptr CreateExtRenderInfoPacket(unkptr p, matrix4& m1, mgRENDER_INFO& render_info);

  // 44 0013F290
  virtual bool DataAssignMT(MDT_HEADER* mdt_header, mgCMemory& stack, mgCTextureManager* texture_man);

public:
  // 20
  s32 m_unk_field_20{ 0 };

  // 24
  unk32 m_unk_field_24{ 0 };

  // 28
  unk32 m_unk_field_28{ 0 };

  // 2C
  unk32 m_unk_field_2C{ 0 };

  // 30
  //matrix4* m_unk_field_30;

  // 34
  unk32 m_unk_field_34{ 0 };

  // 38
  unk32 m_unk_field_38{ 0 };

  // 3C
  unk32 m_unk_field_3C{ 0 };

  // 40
  s32 m_material_num{ 0 };

  // 44
  unkptr m_p_material{ nullptr };

  // 48
  unk32 m_unk_field_48{ 0 };

  // SIZE 0x4C
};

class mgC3DSprite : mgCVisual
{
public:
  // 0013BCB0
  mgC3DSprite();

public:
  unk32 m_unk_field_20{ 0 };
};

struct mgPOINT_LIGHT
{
  vec4 field_0{ };
  vec4 field_10{ };

  f32 field_20{ 0.0f };
  f32 field_24{ 0.0f };
};

class mgCDrawManager 
{
public:
  // 00135180
  mgCDrawManager();

public:
  // 64
  unkptr m_unk_field_64{ nullptr };
  // 68
  u32 m_unk_field_68{ 0 };
  // 6C
  unk m_unk_field_6C{ 0 };
  // 70
  unk m_unk_field_70{ 0 };
};

class mgCObject
{
public:
  // 00161DF0
  mgCObject();

public:
  // 8  00138810
  virtual void ChangeParam();

  // C  00138820
  virtual void UseParam();

  // 10 00136190
  //virtual void SetPosition(const vec3&);

  // 14 00136220
  virtual void SetPosition(f32 x, f32 y, f32 z);

  // 18 00136260
  //virtual vec3 GetPosition();

  // 1C 00136270
  //virtual void SetRotation(const vec3&);

  // 20 001362F0
  virtual void SetRotation(f32 x, f32 y, f32 z);

  // 24 00136330
  //virtual vec3 GetRotation();

  // 28 00136340
  //virtual void SetScale(const vec3&);

  // 2C 001363C0
  virtual void SetScale(f32 x, f32 y, f32 z);

  // 30 00136400
  //virtual vec3 GetScale();

  // 34 00138840
  virtual unkptr Draw();

  // 38 00138830
  virtual unkptr DrawDirect();

  // 3C 00136410
  virtual void Initialize();

public:
  // (vtable @ 0x0)
  // 4
  unk32 m_unk_field_4{ 0 };

  // 8
  unk32 m_unk_field_8{ 0 };

  // C
  unk32 m_unk_field_C{ 0 };

  // 10
  vec3 m_position{ };

  // 20
  vec3 m_rotation{ };

  // 30
  vec3 m_scale{ };

  // 40
  bool m_unk_field_40{ true };

  // 44
  bool m_unk_field_44{ false };

  // SIZE 0x48
};

class mgCFrameAttr : public mgCVisualAttr
{
public:
  // 18
  s32 m_unk_field_18{ 1 };

  // ?

  f32 m_unk_field_20{ 100.0f };

  // ?

  // 30
  s32 m_unk_field_30{ 1 };

  // ?

  // 3C
  unk32 m_unk_field_3C{ 0 };

  // ?

  // 44
  f32 m_unk_field_44{ 1.0f };

  // ?

  // 50
  // probably a vec4 to be honest
  unk32 m_unk_field_50{ 0 };

  // 54
  f32 m_unk_field_54{ 1.0f };

  // 58
  unk32 m_unk_field_58{ 0 };

  // 5C
  unk32 m_unk_field_5C{ 0 };

  // ?

  // 70
  // also probably a vec4
  f32 m_unk_field_70{ 128.0f };

  // 74
  f32 m_unk_field_74{ 128.0f };

  // 78
  f32 m_unk_field_78{ 128.0f };

  // 7C
  f32 m_unk_field_7C{ 128.0f };

  // 80
  s32 m_unk_field_80{ 1 };

  // 84
  unk32 m_unk_field_84{ 0 };
  
  // 88
  unk32 m_unk_field_88{ 0 };

  // 8C
  unk32 m_unk_field_8C{ 0 };

  // SIZE 0x90
};

class mgCFrame;
using mgCFrameCollection = std::vector<std::shared_ptr<mgCFrame>>;

class mgCFrameBase : public mgCObject
{
public:
  virtual void Initialize();

private:
  friend class mgCFrameManager;
};

class mgCFrame : public mgCFrameBase, public std::enable_shared_from_this<mgCFrame>
{
public:
  virtual ~mgCFrame() {};
  NO_DISCARD static std::shared_ptr<mgCFrame> Create();
private:
  mgCFrame() = default;

public:
  struct BoundInfo
  {
    // 0
    //mgVu0FBOX8 m_box8;

    // 80
    //mgVu0FBOX m_box;

    // A0
    // NOTE: X, Y, Z is origin; W is radius
    vec4 m_sphere;
  };

  // 34 001387F0
  virtual unkptr Draw();

  // 3C 00136520
  virtual void Initialize();

  // 40 00136890
  //virtual std::optional<mgVu0FBOX> GetWorldBBox();

  // 44 00137E10
  virtual void Draw(unkptr p);

  // 48 00132D90
  virtual void SetVisual(mgCVisual* visual);

  // 00136590
  void SetName(const std::string& name);

  // 001365A0
  //void SetTransMatrix(glm::fquat& quat);

  // 001365F0
  //void SetBBox(const vec4& corner1, const vec4& corner2);

  //void SetBBox(const mgVu0FBOX& box);

  // 001366F0
  //void GetBBox(vec4& corner1, vec4& corner2) const;

  //void GetBBox(mgVu0FBOX& box) const;

  // 00136760
  //void SetBSphere(vec4& origin, f32 radius);

  // 001367B0
  mgCFrame* GetFrame(ssize i);

  // 00136800
  //bool RemakeBBox(const vec4& corner1, const vec4& corner2);

  //bool RemakeBBox(const mgVu0FBOX& box);

  // 00136A80
  // Returns the number of frames contained within a subgraph, with this
  // frame as the root.
  uint GetFrameNum() const;

  // 00136AE0
  void SetParent(std::shared_ptr<mgCFrame> parent);

  // 00136BC0
  void DeleteParent();

  // 00136C30
  void SetReference(std::shared_ptr<mgCFrame> ref);

  // 00136C60
  void DeleteReference();

  // 00136C80
  void ClearChildFlag();

  // 00136E40
  //matrix4 GetBBoardMatrix(sint i1, mgRENDER_INFO& render_info);

  // 00137030
  //matrix4 GetLWMatrix();

  // 001371B0
  //matrix4 GetLWMatrixTopBottom();

  // 00137320
  //matrix4 GetInverseMatrix();

  // 00137590
  //matrix4 SetTransMatrix();

  // 001376D0
  void SearchFrame(char* s);

  // 00137750
  void SearchFrameID(char* s);

  // 001377E0
  //vec4 GetWorldPosition(vec4& v2);

  // 00137830
  //vec4 GetWorldPosition0();

  // 00137870
  //vec4 GetWorldDir(vec4& v1);

  // 00137930
  void SetRotType(sint i1);

  // 00137950
  void SetAttrParam(mgCFrameAttr& attr, sint i1, sint i2);

  // 00137D30
  void SetAttrParamObjAlpha(f32 f1, sint i1);

  // 00137DA0
  void SetAttrParamDraw(sint i1, sint i2);

  // 001381C0
  //mgVu0FBOX GetDrawRect(mgCDrawManager* manager);

private:
  // 00136B20
  void SetBrother(std::shared_ptr<mgCFrame> brother); // sibling?

  // 00136B60
  void SetChild(std::shared_ptr<mgCFrame> child);

  // 00136CE0
  //matrix4 GetLocalMatrix();

public:
  // 50
  std::string m_name{ };

  // About the graph implementation:
  // Users can create an mgCFrame using Create (which results in a graph with a singular frame)
  // and can set/remove a parent for an mgCFrame (there's also SetReference/DeleteReference, 
  // but I'm not quite sure of the use case for that compared to SetParent/DeleteParent).
  // Setting children/siblings is entirely a private implementation detail.
  //
  // Example graph:
  // ( )
  // (1)<.........
  // ( )    .    .
  // | ^    .    .
  // v .    .    .
  // ( )->( )->( )
  // (2)  (3)  (4)
  // ( )<.( )<.( )
  //      | ^
  //      v .
  //      ( )
  //      (5)
  //      ( )
  //
  // If a frame has a child, it has a reference to the first child in a doubly-linked list of siblings.
  // All children also have a weak reference back to the parent frame.
  // 
  // Note that all strong references flow downwards through the graph, and in a way that all nodes (except the root)
  // have exactly one reference.
  // 
  // However, the root frame is also stored in a vector in an mgCFrameManager instance, which prevents an upper
  // second of the graph destructing if only a reference to a non-root frame is kept, such as keeping a reference
  // to 5 while having no references to 1. This vector is currently manually garbage collected by
  // calling mgCFrameManager::Step.
  // 
  // A graph which has a frame with siblings but no parent is malformed.

  // 54
  std::weak_ptr<mgCFrame> m_parent{ };
  // 58
  std::shared_ptr<mgCFrame> m_child{ };
  // 5C
  std::shared_ptr<mgCFrame> m_next_brother{ };
  // 60
  std::weak_ptr<mgCFrame> m_prev_brother{ };

  // 64
  ssize m_unk_field_64{ 0 };

  // 68
  //mgCFrame** m_unk_field_68{ nullptr };

  // 6C
  unk32 m_unk_field_6C{ 0 };

  // 70
  //matrix4 m_lw_matrix{ 1.0f };

  // B0
  //matrix4 m_trans_matrix{ 1.0f };

  // F0
  BoundInfo* m_bound_info{ nullptr };

  // F4
  mgCFrameAttr* m_unk_field_F4{ nullptr };

  // F8
  mgCVisual* m_visual{ nullptr };

  // FC
  unk32 m_unk_field_FC{ 0 };

  // 100
  unk32 m_unk_field_100{ 0 };
};

class mgCFrameManager
{
public:
  // Handles garbage collection
  void Step();
private:
  // Finds the position of a graph
  std::optional<mgCFrameCollection::iterator> FindGraph(std::shared_ptr<mgCFrame> graph);

  // Adds a graph to the collection
  void AddGraph(std::shared_ptr<mgCFrame> graph);

  // Removes a graph from the collection
  void RemoveGraph(std::shared_ptr<mgCFrame> graph);

  // Checks if a graph has other references
  bool IsGraphAlive(std::shared_ptr<mgCFrame>& root); // argument by reference to avoid incrementing ref count
private:
  // All stored graph roots
  mgCFrameCollection m_graphs{};
private:
  friend class mgCFrame;
};

class mgCDrawEnv
{
public:
  // 00138850
  mgCDrawEnv(bool b);

  mgCDrawEnv();

public:
  // 00138970
  void SetAlpha(u8 alpha_macro_id);

  // 001389E0
  u8 GetAlphaMacroID(void);

  // 00138A40
  void SetZBuf(sint i);

  // 0
  u64 m_unk_field_0{ 0 };

  // 8
  u64 m_unk_field_8{ 0 };

  // 10
  u64 m_unk_field_10{ 0 };

  // 18
  u64 m_unk_field_18{ 0 };
  
  // 24
  u8 m_unk_field_24{ 0 };

  // 28
  u64 m_unk_field_28{ 0 };

  // 30
  u64 m_unk_field_30{ 0 };

  // 38
  u64 m_unk_field_38{ 0 };
};

class mgCDrawPrim
{
public:
  // 001343a0
  // Current member initialization should generate correct default constructor
  //mgCDrawPrim();

  // 00134410
  mgCDrawPrim(mgCMemory* memory, sceVif1Packet* vif1_packet);

  mgCDrawPrim() = default;

public:
  // 001344a0
  void Begin(sint i);

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
  void BeginPrim2(sint);

  // 00134890
  void BeginPrim2(sint, uint, uint, uint);

  // 00134940
  void EndPrim2();

  // 00134a20
  void End2();

  // 00134aa0
  //void Data0(vec4);

  // 00134ac0
  //void Data4(vec4);

  // 00134ae0
  //void Data(ivec4);

  // 00134b00
  void DirectData(sint);

  // 00134b20
  // note: x and y are fixed posint (>> 4)
  void Vertex(sint x, sint y, sint z);

  // 00134b30
  void Vertex(f32 x, f32 y, f32 z);

  // 00134B70
  //void Vertex(vec3 v);

  // 00134bb0
  void Vertex4(sint x, sint y, sint z);

  // 00134b70
  //void Vertex4(vec4 v);

  // Custom
  //void Vertex4(vec3 v);

  // 00134c60
  //void Vertex4(ivec3 v);

  // 00134c80
  void Color(sint r, sint g, sint b, sint a);

  // 00134cf0
  //void Color(vec4 v);

  // 00134d30
  // fixed posint (<< 4)
  void TextureCrd4(sint s, sint t);

  // 00134d70
  void TextureCrd(sint s, sint t);

  // 00134d80
  void Direct(ulong, ulong);

  // 00134da0
  void Texture(mgCTexture* texture);

  // 00134ec0
  void AlphaBlendEnable(bool);

  // 00134ee0
  void AlphaBlend(sint);

  // 00134ef0
  void AlphaTestEnable(bool);

  // 00134f10
  void AlphaTest(sint, sint);

  // 00134f50
  // destination alpha
  void DAlphaTest(sint, sint);

  // 00134f90
  void DepthTestEnable(bool);

  // 00134ff0
  void DepthTest(sint);

  // 00135090
  void ZMask(sint);

  // 001350a0
  void TextureMapEnable(bool);

  // 001350c0
  void Bilinear(bool);

  // 001350d0
  void Shading(bool);

  // 001350f0
  void AntiAliasing(bool);

  // 00135110
  void FogEnable(bool);

  // 00135130
  void Coord(sint);

  // 00135140
  void GetOffset(sint*, sint*);

public:
  // 0
  unk32 m_unk_field_0{ 0 };

  // 4
  unk32 m_unk_field_4{ 0 };

  // 8
  unk32 m_unk_field_8{ 0 };

  // 10
  mgCDrawEnv m_unk_field_10{ };

  // 50
  unk32 m_unk_field_50{ 0x100 };

  // 58
  mgCTexture m_unk_field_58{ };

  // C8
  bool m_unk_field_C8{ true };

  // CC
  bool m_unk_field_CC{ true };

  // DO
  bool m_unk_field_D0{ true };

  // ?

  // F8
  f32 m_unk_field_F8{ 1.0f };

  // FC
  unk32 m_unk_field_FC{ 0 };

  // SIZE 0x100
};

struct mgRENDER_INFO
{
  // 00138B00
  void SetRenderInfo(f32 f1, sint i1, sint i2, f32 f2, f32 f3, sint i3);

  // 00138FC0
  //void SetViewMatrix(matrix4& m1, vec4& v1);

  // 001390A0
  //void SetDropShadowMatrix(vec4& v1, vec4& v2, vec4& v3);

  // 00139120
  usize ActiveLighting(usize i1, bool b1);

  // 00139250
  // FIXME: unknown pointer return type (of size 0x150 -- see InitActiveLighting)
  void* GetpLightInfo(void);

  // 00139280
  void InitActiveLighting(void);

  // 001392B0
  void InitLighting(void);

  // 00139320
  //void SetLight(matrix4& m1, matrix4& m2);

  // 001393A0
  //void GetLight(matrix4& m1, matrix4& m2);

  // 00139400
  //void SetLight(sint i1, vec4& v1, vec4& v2);

  // 001394B0
  //void SetAmbient(vec4& v1);

  // 001394E0
  //void GetAmbient(vec4& v1);

  // 00139510
  //void SetPlight(sint i1, vec4& v1, vec4& v2, f32 f1, f32 f2);

  // 00139590
  void SetPlight(sint i1, mgPOINT_LIGHT& pl);

  // 00139700
  void GetPlight(sint i1, mgPOINT_LIGHT& pl);

  // 001397C0
  void FogEnable(bool enabled);

  // 001397D0
  bool GetFogEnabled(void);

  // 001397E0
  void PlightEnable(bool enabled);

  // 001397F0
  bool GetPlightEnable(void);

  // 00139800
  void SetFogParam(f32 f1, f32 f2, u8 i1, u8 i2, u8 i3, f32 f3, f32 f4);

  // 3A0
  vec3 camera_pos{};

  // F20
  std::array<mgCDrawEnv, 2> m_unk_field_F20{};
};

// 00135B90
//void QuatToMat(vec4& v1, matrix4& m1);

// 00135C70
//void test1(matrix4& m1, matrix4& m2, matrix4& m3, vec4& v1, vec4& v2);

// 00135DC0
//void test2(vec4& v1, vec4& v2);

// 00135E90
//bool mgInsideScreen(mgVu0FBOX& box);

// 00135EE0
//bool mgInsideScreen(mgVu0FBOX& box, matrix4& m1);

// 00135FA0
//bool mgInsideScreen(mgVu0FBOX& box, matrix4& m1, vec4& v1, vec4& v2);

// 00135F80
//bool mgInsideScreen(vec4& v1, vec4& v2);

// 00135FA0
//bool mgInsideScreen(matrix4& m1, matrix4& m2, vec4& v1, vec4& v2);

// 001375C0
// sint StrCmp(char* s1, char* s2);

// 001376C0
// sint mgFrameNameComp(char* s1, char* s2);

// 001398B0
void MG_ADDRESS_CHECK(void*, char*);