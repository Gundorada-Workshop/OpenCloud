#pragma once
#include "glm/glm.hpp"
#include "common/types.h"

// TODO
class CVisual;
class mgCDrawManager;


class mgRENDER_INFO;
class mgCFrameAttr;

namespace mg_Frame
{
	void SInit();
}

struct mgPOINT_LIGHT
{
	glm::vec4 field_0;
	glm::vec4 field_10;
	float field_20;
	float field_24;
};

struct mgVu0FBOX
{
	glm::vec4 m_corner1;
	glm::vec4 m_corner2;

	// 00139890
	mgVu0FBOX(mgVu0FBOX& box);
};

class mgCObject
{
public:
	// NOTE: See vtable @ 00374FE0
	virtual void ChangeParam(void);
	virtual void UseParam(void);
	virtual void SetPosition(glm::vec4&);
	virtual void SetPosition(float x, float y, float z);
	virtual void GetPosition(glm::vec4&);
	virtual void SetRotation(glm::vec4&);
	virtual void SetRotation(float x, float y, float z);
	virtual void GetRotation(glm::vec4&);
	virtual void SetScale(glm::vec4&);
	virtual void SetScale(float x, float y, float z);
	virtual void GetScale(glm::vec4&);
	virtual void Draw(void);
	// FIXME: Unknown return type
	virtual int DrawDirect(void);
	virtual void Initialize(void);

	// 00161DF0
	mgCObject();

	// FIXME: NAME: TYPE
	int field_4;
	int field_8;
	int field_C;
	int field_10;
	int field_14;
	int field_18;
	int field_1C;
	int field_20;
	int field_24;
	int field_28;
	int field_2C;
	int field_30;
	int field_34;
	int field_38;
	int field_3C;
	int field_40;
	int field_44;
};

class mgCFrameBase : mgCObject
{
public:

};

class mgCFrameAttr //: mgCVisualAttr
{
public:
	// 00135AD0
	void Initialize(void);

	// 00135B60
	mgCFrameAttr();
};

class mgCFrame : mgCFrameBase
{
public:
	virtual void GetWorldBBox(mgVu0FBOX& box);
	// FIXME: unknown pointer type
	virtual void Draw(void* p);
	virtual void SetVisual(CVisual* visual);

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

	char* name;
	// FIXME: NAME: TYPE
	int field_54;
	int field_58;
	int field_5C;
	int field_60;
	int field_64;
	int field_68;
	int field_6C;
	matrix4 field_70;
	matrix4 field_B0;
	int field_F0;
	int field_F4;
	int field_F8;
	int field_FC;
	int field_100;
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

	// 00138880
	mgCDrawEnv(mgCDrawEnv& other);
};

class mgRENDER_INFO
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

// 00380DA0
static mgCFrameAttr stru_380DA0;