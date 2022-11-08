#pragma once
#include <array>
#include "glm/glm.hpp"
#include "common/debug.h"
#include "common/types.h"
#include "mg_memory.h"
#include "mg_texture.h"

// ~ 00131B60 - 00139900

// THIS FILE TODO
class mgCMDTBuilder {};
class mgCVisualFixMDT {};
class mgMaterial {};
class mgCShadowMDT {};
class mgC3DSprite {};
class mgCSprite {};
class mgCVisualPrim {};

struct mgRENDER_INFO;
class mgCDrawManager;
class mgCTextureManager;

namespace mg_frame
{
	void SInit();
}

// 00376C70
extern s32 mgScreenWidth;
// 00376C74
extern s32 mgScreenHeight;

template<typename T>
struct mgRect
{
public:
	// 0
	T m_ax;
	// 4
	T m_ay;
	// 8
	T m_bx;
	// C
	T m_by;

	// 0013E390 (s32)
	// 001F24F0 (float)
	// 002BFC30 (s16)
	inline void Set(T ax, T ay, T bx, T by)
	{
		//log_trace("mgRect::Set({}, {}, {}, {})", ax, ay, bx, by);

		m_ax = ax;
		m_ay = ay;
		m_bx = bx;
		m_by = by;
	}
};

class mgCVisualAttr
{
public:
	// 0013E7B0
	void Initialize();
	// 0013E7F0
	mgCVisualAttr();

	// 0
	s32 m_unk_field_0;

	// ?

	// 8
	s32 m_unk_field_8;

	// ?

	// 14
	s32 m_unk_field_14;

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
public:

};

class mgCVisual
{
public:
	// VTABLE 00374F10
	// 0  0
	// 4  0
	// 8  00133740
	virtual int Iam();
	// C  00134300
	virtual int GetMaterialNum();
	// 10 00134310
	virtual _UNKNOWNPOINTER GetpMaterial();
	// 14 00134320
	virtual _UNKNOWNPOINTER GetMaterial(ssize index);
	// 18 00133750 (NOTE: this class actually just returns its own reference :( )
	virtual mgCVisual* Copy(mgCMemory& stack);
	// 1C 00134330
	virtual bool CreateBBox(glm::vec4& v1, glm::vec4& v2, glm::mat4& m1);
	// 20 00134340
	virtual _UNKNOWNPOINTER CreateRenderInfoPacket(_UNKNOWNPOINTER p, glm::mat4& m1, mgRENDER_INFO& render_info);
	// 24 001342F0
	virtual _UNKNOWNPOINTER CreatePacket(mgCMemory& mem1, mgCMemory& mem2);
	// 28 00134360
	virtual _UNKNOWNPOINTER Draw(glm::mat4& m1, mgCDrawManager& draw_man);
	// 2C 00134350
	virtual _UNKNOWNPOINTER Draw(_UNKNOWNPOINTER p, glm::mat4& m1, mgCDrawManager& draw_man);
	// 30 00132DC0
	virtual void Initialize();

	// 0
	_DWORD m_unk_field_0;
	// 4
	_DWORD m_unk_field_4;
	// 8
	_DWORD m_unk_field_8;
	// C
	_DWORD m_unk_field_C;
	// 10
	s32 m_unk_field_10;
	// 14
	s32 m_unk_field_14;
	// 18
	_DWORD m_unk_field_18;
	
	// SIZE 0x20 (vtable @ 0x1C)
};

class mgCVisualMDT : public mgCVisual
{
public:
	// VTABLE 00375190
	// 0  0
	// 4  0
	// 8  00134280
	virtual int Iam();
	// C  00134290
	virtual int GetMaterialNum();
	// 10 001342A0
	virtual _UNKNOWNPOINTER GetpMaterial();
	// 14 0013EF60
	virtual _UNKNOWNPOINTER GetMaterial(ssize index);
	// 18 00133750 (mgCVisual::Copy)
	// 1C 0013EFC0
	virtual bool CreateBBox(glm::vec4& v1, glm::vec4& v2, glm::mat4& m1);
	// 20 001404D0
	virtual _UNKNOWNPOINTER CreateRenderInfoPacket(_UNKNOWNPOINTER p, glm::mat4& m1, mgRENDER_INFO& render_info);
	// 24 001342F0 (mgCVisual::CreatePacket)
	// 28 001342B0
	virtual _UNKNOWNPOINTER Draw(glm::mat4& m1, mgCDrawManager& draw_man);
	// 2C 0013F4E0
	virtual _UNKNOWNPOINTER Draw(_UNKNOWNPOINTER p, glm::mat4& m1, mgCDrawManager& draw_man);
	// 30 0013EAC0
	virtual void Initialize();
	// 34 0013F6A0
	virtual _DWORD CreatePacket(mgCDrawManager& draw_man);
	// 38 0013FF60
	virtual _DWORD CreateFacePacket(_UNKNOWNPOINTER p, mgCFace& face);
	// 3C 0013F010
	virtual mgCFace* CreateFace(FACES_ID& faces_id, mgCMemory& mem1, mgCMemory& mem2, mgCFace&& faces);
	// 40 00140BE0
	virtual _UNKNOWNPOINTER CreateExtRenderInfoPacket(_UNKNOWNPOINTER p, glm::mat4& m1, mgRENDER_INFO& render_info);
	// 44 0013F290
	virtual bool DataAssignMT(MDT_HEADER* mdt_header, mgCMemory& stack, mgCTextureManager* texture_man);

	// 20
	s32 m_unk_field_20;
	// 24
	_DWORD m_unk_field_24;
	// 28
	_DWORD m_unk_field_28;
	// 2C
	_DWORD m_unk_field_2C;
	// 30
	glm::mat4* m_unk_field_30;
	// 34
	_DWORD m_unk_field_34;
	// 38
	_DWORD m_unk_field_38;
	// 3C
	_DWORD m_unk_field_3C;
	// 40
	s32 m_material_num;
	// 44
	_UNKNOWNPOINTER m_p_material;
	// 48
	_DWORD m_unk_field_48;

	// SIZE 0x4C
};

struct mgPOINT_LIGHT
{
	glm::vec4 field_0;
	glm::vec4 field_10;
	float field_20;
	float field_24;
};

struct mgVu0FBOX
{
	// 0
	// Corner 1
	glm::vec4 m_a;
	// 10
	// Corner 2
	glm::vec4 m_b;

	// 00139890
	mgVu0FBOX(mgVu0FBOX& box);
};

class mgCDrawManager 
{
public:
	// 00135180
	mgCDrawManager();

	// 64
	_UNKNOWNPOINTER m_unk_field_64;
	// 68
	u32 m_unk_field_68;
	// 6C
	_UNKNOWN m_unk_field_6C;
	// 70
	_UNKNOWN m_unk_field_70;
};

class mgCObject
{
public:
	// VTABLE 00374FE0
	// 0  0
	// 4  0
	// 8  00138810
	virtual void ChangeParam();
	// C  00138820
	virtual void UseParam();
	// 10 00136190
	virtual void SetPosition(const glm::vec4&);
	// 14 00136220
	virtual void SetPosition(float x, float y, float z);
	// 18 00136260
	virtual void GetPosition(glm::vec4&);
	// 1C 00136270
	virtual void SetRotation(const glm::vec4&);
	// 20 001362F0
	virtual void SetRotation(float x, float y, float z);
	// 24 00136330
	virtual void GetRotation(glm::vec4&);
	// 28 00136340
	virtual void SetScale(const glm::vec4&);
	// 2C 001363C0
	virtual void SetScale(float x, float y, float z);
	// 30 00136400
	virtual void GetScale(glm::vec4&);
	// 34 00138840
	virtual _UNKNOWNPOINTER Draw();
	// 38 00138830
	virtual _UNKNOWNPOINTER DrawDirect();
	// 3C 00136410
	virtual void Initialize();

	// 00161DF0
	mgCObject();

	// (vtable @ 0x0)
	// 4
	_DWORD m_unk_field_4;
	// 8
	_DWORD m_unk_field_8;
	// C
	_DWORD m_unk_field_C;
	// 10
	glm::vec4 m_position;
	// 20
	glm::vec4 m_rotation;
	// 30
	glm::vec4 m_scale;
	// 40
	bool m_unk_field_40;
	// 44
	bool m_unk_field_44;

	// SIZE 0x48
};

class mgCFrameAttr : public mgCVisualAttr
{
public:
	// 00135AD0
	void Initialize(void);

	// 00135B60
	mgCFrameAttr();

	// 18
	s32 m_unk_field_18;

	// ?

	float m_unk_field_20;

	// ?

	// 30
	s32 m_unk_field_30;

	// ?

	// 3C
	_DWORD m_unk_field_3C;

	// ?

	// 44
	float m_unk_field_44;

	// ?

	// 50
	// probably a vec4 to be honest
	_DWORD m_unk_field_50;
	// 54
	float m_unk_field_54;
	// 58
	_DWORD m_unk_field_58;
	// 5C
	_DWORD m_unk_field_5C;

	// ?

	// 70
	// also probably a vec4
	float m_unk_field_70;
	// 74
	float m_unk_field_74;
	// 78
	float m_unk_field_78;
	// 7C
	float m_unk_field_7C;
	// 80
	s32 m_unk_field_80;
	// 84
	_DWORD m_unk_field_84;
	
	// ?

	// 8C
	_DWORD m_unk_field_8C;

	// SIZE 0x90
};

class mgCFrameBase : public mgCObject
{
public:
	// VTABLE 00374FA0
	// 0  0
	// 4  0
	// 8  00138810 (mgCObject::ChangeParam)
	// C  00138820 (mgCObject::UseParam)
	// 10 00136190 (mgCObject::SetPosition)
	// 14 00136220 (mgCObject::SetPosition)
	// 18 00136260 (mgCObject::GetPosition)
	// 1C 00136270 (mgCObject::SetRotation)
	// 20 001362F0 (mgCObject::SetRotation)
	// 24 00136330 (mgCObject::GetRotation)
	// 28 00136340 (mgCObject::SetScale)
	// 2C 001363C0 (mgCObject::SetScale)
	// 30 00136400 (mgCObject::GetScale)
	// 34 00138840 (mgCObject::Draw)
	// 38 00138830 (mgCObject::DrawDirect)
	// 3C 00136510
	virtual void Initialize();

	// SIZE 0x48 (?) (no new members ?)
};

class mgCFrame : public mgCFrameBase
{
public:
	// VTABLE 00374FA0
	// 0  0
	// 4  0
	// 8  00138810 (mgCObject::ChangeParam)
	// C  00138820 (mgCObject::UseParam)
	// 10 00136190 (mgCObject::SetPosition)
	// 14 00136220 (mgCObject::SetPosition)
	// 18 00136260 (mgCObject::GetPosition)
	// 1C 00136270 (mgCObject::SetRotation)
	// 20 001362F0 (mgCObject::SetRotation)
	// 24 00136330 (mgCObject::GetRotation)
	// 28 00136340 (mgCObject::SetScale)
	// 2C 001363C0 (mgCObject::SetScale)
	// 30 00136400 (mgCObject::GetScale)
	// 34 001387F0
	virtual _UNKNOWNPOINTER Draw();
	// 38 00138830 (mgCObject::DrawDirect)
	// 3C 00136520
	virtual void Initialize();
	// 40 00136890
	virtual void GetWorldBBox(mgVu0FBOX& box);
	// 44 00137E10
	virtual void Draw(_UNKNOWNPOINTER p);
	// 48 00132D90
	virtual void SetVisual(mgCVisual* visual);

	// 00136590
	void SetName(char* name);

	// 001365A0
	void SetTransMatrix(glm::vec4& v);

	// 001365F0
	void SetBBox(glm::vec4& corner1, glm::vec4& corner2);

	// 001366F0
	void GetBBox(glm::vec4& corner1, glm::vec4& corner2);

	// 00136760
	void SetBSphere(glm::vec4& origin, float radius);

	// 001367B0
	mgCFrame* GetFrame(usize i);

	// 0013688C
	void RemakeBBox(glm::vec4& corner1, glm::vec4& corner2);

	// 00136A80
	int GetFrameNum(void);

	// 00136AE0
	void SetParent(mgCFrame& parent);

	// 00136B20
	void SetBrother(mgCFrame& brother); // sibling?

	// 00136B60
	void SetChild(mgCFrame& child);

	// 00136BC0
	void DeleteParent(void);

	// 00136C30
	void SetReference(mgCFrame& ref);

	// 00136C60
	void DeleteReference(void);

	// 00136C80
	void ClearChildFlag(void);

	// 00136CE0
	void GetLocalMatrix(glm::mat4& m1);

	// 00136E40
	void GetBBoardMatrix(int i1, glm::mat4& m1, mgRENDER_INFO& render_info);

	// 00137030
	void GetLWMatrix(glm::mat4& m1);

	// 001371B0
	void GetLWMatrixTopBottom(glm::mat4& m1);

	// 00137320
	void GetInverseMatrix(glm::mat4& m1);

	// 00137590
	void SetTransMatrix(glm::mat4& m1);

	// 001376D0
	void SearchFrame(char* s);

	// 00137750
	void SearchFrameID(char* s);

	// 001377E0
	void GetWorldPosition(glm::vec4& v1, glm::vec4& v2);

	// 00137830
	void GetWorldPosition0(glm::vec4& v1);

	// 00137870
	void GetWorldDir(glm::vec4& v1, glm::vec4& v2);

	// 00137930
	void SetRotType(int i1);

	// 00137950
	void SetAttrParam(mgCFrameAttr& attr, int i1, int i2);

	// 00137D30
	void SetAttrParamObjAlpha(float f1, int i1);

	// 00137DA0
	void SetAttrParamDraw(int i1, int i2);

	// 001381C0
	void GetDrawRect(mgVu0FBOX& box, mgCDrawManager* manager);

	// 00136490
	mgCFrame();

	// 001386C0
	mgCFrame(mgCFrame& other);

	// 50
	char* m_name;
	// 54
	_DWORD m_unk_field_54;
	// 58
	_DWORD m_unk_field_58;
	// 5C
	_DWORD m_unk_field_5C;
	// 60
	_DWORD m_unk_field_60;
	// 64
	_DWORD m_unk_field_64;
	// 68
	_DWORD m_unk_field_68;
	// 6C
	_DWORD m_unk_field_6C;
	// 70
	glm::mat4 m_unk_field_70;
	// B0
	glm::mat4 m_unk_field_B0;
	// F0
	_DWORD m_unk_field_F0;
	// F4
	_DWORD m_unk_field_F4;
	// F8
	_DWORD m_unk_field_F8;
	// FC
	_DWORD m_unk_field_FC;
	// 100
	_DWORD m_unk_field_100;

	// SIZE 0x104 (?)
};

class mgCDrawEnv {
public:
	// 001388B0
	void Initialize(bool b);

	// 00138970
	void SetAlpha(u8 alpha_macro_id);

	// 001389E0
	u8 GetAlphaMacroID(void);

	// 00138A40
	void SetZBuf(int i);

	// 00138850
	mgCDrawEnv();

	// 0
	u64 m_unk_field_0;
	// 8
	u64 m_unk_field_8;
	// 10
	u64 m_unk_field_10;
	// 18
	u64 m_unk_field_18;
	
	// ?

	// 28
	u64 m_unk_field_28;
	// 30
	u64 m_unk_field_30;
	// 38
	u64 m_unk_field_38;
};

class mgCDrawPrim
{
public:
	// 001343a0
	// Current member initialization should generate correct default constructor
	//mgCDrawPrim();

	// 00134410
	void Initialize(mgCMemory* memory, sceVif1Packet* vif1_packet);

	// 001344a0
	void Begin(int i);

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
	void Data0(glm::vec4);

	// 00134ac0
	void Data4(glm::vec4);

	// 00134ae0
	void Data(glm::ivec4);

	// 00134b00
	void DirectData(sint);

	// 00134b20
	// note: x and y are fixed point (>> 4)
	void Vertex(sint x, sint y, sint z);

	// 00134b30
	void Vertex(f32 x, f32 y, f32 z);

	// 00134B70
	void Vertex(glm::vec3 v);

	// 00134bb0
	void Vertex4(sint x, sint y, sint z);

	// 00134b70
	void Vertex4(glm::vec4 v);

	// Custom
	void Vertex4(glm::vec3 v);

	// 00134c60
	void Vertex4(glm::ivec3 v);

	// 00134c80
	void Color(sint r, sint g, sint b, sint a);

	// 00134cf0
	void Color(glm::vec4 v);

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

	// 0
	_DWORD m_unk_field_0{};
	// 4
	_DWORD m_unk_field_4{};
	// 8
	_DWORD m_unk_field_8{};
	// 10
	mgCDrawEnv m_unk_field_10{};
	// 50
	_DWORD m_unk_field_50{ 0x100 };
	// 58
	mgCTexture m_unk_field_58{};
	// C8
	bool m_unk_field_C8{ true };
	// CC
	bool m_unk_field_CC{ true };
	// DO
	bool m_unk_field_D0{ true };

	// ?

	// F8
	float m_unk_field_F8{ 1.0f };
	// FC
	_DWORD m_unk_field_FC{};

	// SIZE 0x100
};

struct mgRENDER_INFO
{
public:
	// 00138AA0
	void Initialize(void);

	// 00138B00
	void SetRenderInfo(float f1, int i1, int i2, float f2, float f3, int i3);

	// 00138FC0
	void SetViewMatrix(matrix4& m1, vec4& v1);

	// 001390A0
	void SetDropShadowMatrix(vec4& v1, vec4& v2, vec4& v3);

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
	void SetLight(matrix4& m1, matrix4& m2);

	// 001393A0
	void GetLight(matrix4& m1, matrix4& m2);

	// 00139400
	void SetLight(int i1, vec4& v1, vec4& v2);

	// 001394B0
	void SetAmbient(vec4& v1);

	// 001394E0
	void GetAmbient(vec4& v1);

	// 00139510
	void SetPlight(int i1, vec4& v1, vec4& v2, float f1, float f2);

	// 00139590
	void SetPlight(int i1, mgPOINT_LIGHT& pl);

	// 00139700
	void GetPlight(int i1, mgPOINT_LIGHT& pl);

	// 001397C0
	void FogEnable(bool enabled);

	// 001397D0
	bool GetFogEnabled(void);

	// 001397E0
	void PlightEnable(bool enabled);

	// 001397F0
	bool GetPlightEnable(void);

	// 00139800
	void SetFogParam(float f1, float f2, u8 i1, u8 i2, u8 i3, float f3, float f4);

	// 3A0
	glm::vec4 camera_pos;

	// F20
	std::array<mgCDrawEnv, 2> m_unk_field_F20;
};

// 00135B90
void QuatToMat(vec4& v1, matrix4& m1);

// 00135C70
void test1(matrix4& m1, matrix4& m2, matrix4& m3, vec4& v1, vec4& v2);

// 00135DC0
void test2(vec4& v1, vec4& v2);

// 00135E90
bool mgInsideScreen(mgVu0FBOX& box);

// 00135EE0
bool mgInsideScreen(mgVu0FBOX& box, matrix4& m1);

// 00135FA0
bool mgInsideScreen(mgVu0FBOX& box, matrix4& m1, vec4& v1, vec4& v2);

// 00135F80
bool mgInsideScreen(vec4& v1, vec4& v2);

// 00135FA0
bool mgInsideScreen(matrix4& m1, matrix4& m2, vec4& v1, vec4& v2);

// 001375C0
int StrCmp(char* s1, char* s2);

// 001376C0
int mgFrameNameComp(char* s1, char* s2);

// 001398B0
void MG_ADDRESS_CHECK(void*, char*);