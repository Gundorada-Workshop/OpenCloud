#include <string.h>
#include "common/log.h"
#include "mg_frame.h"

set_log_channel("mg_frame");

// 00380DA0
static mgCFrameAttr dmy_attr;

namespace mg_frame
{
	void SInit()
	{
		log_trace("SInit()");

		new (&dmy_attr) mgCFrameAttr();
	}
}

// 00376C70
s32 mgScreenWidth{};
// 00376C74
s32 mgScreenHeight{};

mgVu0FBOX::mgVu0FBOX(mgVu0FBOX& other)
{
	log_trace("mgVu0FBOX::mgVu0FBOX({})", fmt::ptr(&other));

	m_a = other.m_a;
	m_b = other.m_b;
}

// 0013E7B0
void mgCVisualAttr::Initialize()
{
	log_trace("mgCVisualAttr::Initialize()");

	memset(this, 0, sizeof(this));

	m_unk_field_0 = -1;
	m_unk_field_8 = 1;
	m_unk_field_14 = -1;
}

// 0013E7F0
mgCVisualAttr::mgCVisualAttr()
{
	log_trace("mgCVisualAttr::mgCVisualAttr()");

	Initialize();
}

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
bool mgCVisual::CreateBBox(glm::vec4& v1, glm::vec4& v2, glm::mat4& m1)
{
	log_trace("mgCVisual::{}({}, {}, {})", __func__, fmt::ptr(&v1), fmt::ptr(&v2), fmt::ptr(&m1));

	return false;
}

// 00134340
_UNKNOWNPOINTER mgCVisual::CreateRenderInfoPacket(_UNKNOWNPOINTER p, glm::mat4& m1, mgRENDER_INFO& render_info)
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
_UNKNOWNPOINTER mgCVisual::Draw(glm::mat4& m1, mgCDrawManager& draw_man)
{
	log_trace("mgCVisual::{}({}, {})", __func__, fmt::ptr(&m1), fmt::ptr(&draw_man));

	return Draw(nullptr, m1, draw_man);
}

// 00134350
_UNKNOWNPOINTER mgCVisual::Draw(_UNKNOWNPOINTER p, glm::mat4& m1, mgCDrawManager& draw_man)
{
	log_trace("mgCVisual::{}({}, {}, {})", __func__, fmt::ptr(p), fmt::ptr(&m1), fmt::ptr(&draw_man));

	return nullptr;
}

// 00132DC0
void mgCVisual::Initialize()
{
	log_trace("mgCVisual::Initialize()");

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
bool mgCVisualMDT::CreateBBox(glm::vec4& v1, glm::vec4& v2, glm::mat4& m1)
{
	log_trace("mgCVisualMDT::{}({}, {}, {})", __func__, fmt::ptr(&v1), fmt::ptr(&v2), fmt::ptr(&m1));

	if (m_unk_field_20 <= 0)
	{
		return false;
	}

	glm::mat4* mat = m_unk_field_30;
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
_UNKNOWNPOINTER mgCVisualMDT::CreateRenderInfoPacket(_UNKNOWNPOINTER p, glm::mat4& m1, mgRENDER_INFO& render_info)
{
	log_trace("mgCVisualMDT::{}({}, {}, {})", __func__, fmt::ptr(p), fmt::ptr(&m1), fmt::ptr(&render_info));

	todo;
	return nullptr;
}

// 001342B0
_UNKNOWNPOINTER mgCVisualMDT::Draw(glm::mat4& m1, mgCDrawManager& draw_man)
{
	log_trace("mgCVisualMDT::{}({}, {})", __func__, fmt::ptr(&m1), fmt::ptr(&draw_man));

	return Draw(nullptr, m1, draw_man);
}

// 0013F4E0
_UNKNOWNPOINTER mgCVisualMDT::Draw(_UNKNOWNPOINTER p, glm::mat4& m1, mgCDrawManager& draw_man)
{
	log_trace("mgCVisualMDT::{}({}, {}, {})", __func__, fmt::ptr(p), fmt::ptr(&m1), fmt::ptr(&draw_man));

	return nullptr;
}


// 0013EAC0
void mgCVisualMDT::Initialize()
{
	log_trace("mgCVisualMDT::Initialize()");

	m_unk_field_20 = 0;
	m_unk_field_30 = nullptr;
	m_unk_field_24 = 0;
	m_unk_field_34 = 0;
	m_unk_field_38 = 0;
	m_unk_field_3C = 0;
	m_material_num = 0;
	m_p_material = nullptr;
	m_unk_field_48 = 0;

	m_unk_field_0 = 0;
	m_unk_field_4 = 0;
	m_unk_field_8 = 0;
	m_unk_field_14 = 0;
	m_unk_field_10 = 0;
	
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
_UNKNOWNPOINTER mgCVisualMDT::CreateExtRenderInfoPacket(_UNKNOWNPOINTER p, glm::mat4& m1, mgRENDER_INFO& render_info)
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

// 00134410
void mgCDrawPrim::Initialize(mgCMemory* memory, sceVif1Packet* vif1_packet)
{
	log_trace("mgCDrawPrim::Initialize({}, {})", fmt::ptr(memory), fmt::ptr(vif1_packet));

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
void mgCDrawPrim::Data0(glm::vec4 v)
{
	log_trace("mgCDrawPrim::{}(({}, {}, {}, {}))", __func__, v.x, v.y, v.z, v.w);

	todo;
}

// 00134AC0
void mgCDrawPrim::Data4(glm::vec4 v)
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
void mgCDrawPrim::Color(glm::vec4 rgba)
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
void mgCObject::SetPosition(const glm::vec4& v)
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

	glm::vec4 pos = glm::vec4(x, y, z, 1.0f);
	SetPosition(pos);
}

// 00136260
void mgCObject::GetPosition(glm::vec4& v)
{
	log_trace("mgCObject::GetPosition({})", fmt::ptr(&v));

	v = m_position;
}

// 00136270
void mgCObject::SetRotation(const glm::vec4& v)
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

	glm::vec4 rot = glm::vec4(x, y, z, 0.0f);
	SetPosition(rot);
}

// 00136330
void mgCObject::GetRotation(glm::vec4& v)
{
	log_trace("mgCObject::GetRotation({})", fmt::ptr(&v));

	v = m_rotation;
}

// 00136340
void mgCObject::SetScale(const glm::vec4& v)
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

	glm::vec4 scale = glm::vec4(x, y, z, 0.0f);
	SetScale(scale);
}

// 00136400
void mgCObject::GetScale(glm::vec4& v)
{
	log_trace("mgCObject::GetScale({})", fmt::ptr(&v));

	v = m_scale;
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
void mgCObject::Initialize()
{
	log_trace("mgCObject::Initialize()");

	SetPosition(0.0f, 0.0f, 0.0f);
	SetRotation(0.0f, 0.0f, 0.0f);
	SetScale(1.0f, 1.0f, 1.0f);
	m_unk_field_40 = true;
	m_unk_field_44 = false;
}

// 00161DF0
mgCObject::mgCObject()
{
	log_trace("mgCObject::mgCObject()");

	Initialize();
}

// 00136510
void mgCFrameBase::Initialize()
{
	log_trace("mgCFrameBase::Initialize()");

	mgCObject::Initialize();
}

// 00135AD0
void mgCFrameAttr::Initialize()
{
	log_trace("mgCFrameAttr::Initialize()");

	memset(this, 0, sizeof(mgCFrameAttr));

	mgCVisualAttr::Initialize();
	
	m_unk_field_7C = 128.0f;
	m_unk_field_78 = 128.0f;
	m_unk_field_74 = 128.0f;
	m_unk_field_70 = 128.0f;

	m_unk_field_0 = -1;
	m_unk_field_18 = 1;
	m_unk_field_8 = 1;
	m_unk_field_3C = 0;
	
	m_unk_field_20 = 100.0f;
	m_unk_field_30 = 1;
	m_unk_field_44 = 1.0f;
	m_unk_field_80 = 1;

	m_unk_field_5C = 0;
	m_unk_field_58 = 0;
	m_unk_field_50 = 0;
	m_unk_field_54 = 1.0f;

	m_unk_field_8C = 0;
	m_unk_field_84 = 0;
}

// 00135B60
mgCFrameAttr::mgCFrameAttr()
{
	log_trace("mgCFrameAttr::mgCFrameAttr()");

	Initialize();
}

// 001387F0
_UNKNOWNPOINTER mgCFrame::Draw()
{
	log_trace("mgCFrame::Draw()");

	todo;
	return nullptr;
}

// 00136520
void mgCFrame::Initialize()
{
	log_trace("mgCFrame::Initialize()");

	m_unk_field_60 = 0;
	m_unk_field_5C = 0;
	m_unk_field_58 = 0;
	m_unk_field_54 = 0;
	m_unk_field_70 = glm::mat4(1.0f);
	m_unk_field_B0 = glm::mat4(1.0f);
	m_name = nullptr;
	m_unk_field_100 = 0;
	m_unk_field_FC = 0;
	m_unk_field_F8 = 0;
	m_unk_field_F4 = 0;
	m_unk_field_64 = 0;
	m_unk_field_68 = 0;
	m_unk_field_6C = 0;
	m_unk_field_F0 = 0;

	mgCObject::Initialize();
}

// 00136890
void mgCFrame::GetWorldBBox(mgVu0FBOX& box)
{
	log_trace("mgCFrame::GetWorldBBox({})", fmt::ptr(&box));

	todo;
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

// 00136490
mgCFrame::mgCFrame()
{
	log_trace("mgCFrame::mgCFrame()");

	Initialize();
}

// 001388B0
void mgCDrawEnv::Initialize(bool b)
{
	log_trace("mgCDrawEnv::Initialize({})", b);

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

// 00138850
mgCDrawEnv::mgCDrawEnv()
{
	log_trace("mgCDrawEnv::mgCDrawEnv()");

	Initialize(false);
}

// 00138880
mgCDrawEnv::mgCDrawEnv(mgCDrawEnv& other)
{
	log_trace("mgCDrawEnv::mgCDrawEnv({})", fmt::ptr(&other));

	memcpy(this, &other, sizeof(this));
}
