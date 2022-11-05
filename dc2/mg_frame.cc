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

mgVu0FBOX::mgVu0FBOX(mgVu0FBOX& box)
{
	m_a = box.m_a;
	m_b = box.m_b;
}

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

void mgCDrawPrim::Vertex4(glm::vec3 v)
{
	Vertex4(static_cast<sint>(v.x), static_cast<sint>(v.y), static_cast<sint>(v.z));
}

void mgCDrawPrim::Vertex4(glm::ivec3 v)
{
	Vertex4(v[0], v[1], v[2]);
}

void mgCDrawPrim::Color(glm::vec4 rgba)
{
	Color(static_cast<sint>(rgba[0]), static_cast<sint>(rgba[1]),
		static_cast<sint>(rgba[2]), static_cast<sint>(rgba[3]));
}

void mgCDrawPrim::TextureCrd(sint s, sint t)
{
	TextureCrd4(s << 4, t << 4);
}

// 00135180
mgCDrawManager::mgCDrawManager()
{
	log_trace("mgCDrawManager::mgCDrawManager()");

	m_unk_field_68 = 0x40;
	m_unk_field_6C = 0;
	m_unk_field_70 = 0;
}

void mgCObject::ChangeParam()
{
	todo;
}

void mgCObject::UseParam()
{
	todo;
}

void mgCObject::SetPosition(glm::vec4& v)
{
	todo;
}

void mgCObject::SetPosition(float x, float y, float z)
{
	todo;
}

void mgCObject::GetPosition(glm::vec4& v)
{
	todo;
}

void mgCObject::SetRotation(glm::vec4& v)
{
	todo;
}

void mgCObject::SetRotation(float x, float y, float z)
{
	todo;
}

void mgCObject::GetRotation(glm::vec4& v)
{
	todo;
}

void mgCObject::SetScale(glm::vec4& v)
{
	todo;
}

void mgCObject::SetScale(float x, float y, float z)
{
	todo;
}

void mgCObject::GetScale(glm::vec4& v)
{
	todo;
}

void mgCObject::Draw()
{
	todo;
}

int mgCObject::DrawDirect()
{
	todo;
	return 0;
}

void mgCObject::Initialize()
{
	todo;
}

mgCObject::mgCObject()
{
	Initialize();
}

void mgCFrameAttr::Initialize()
{
	memset(this, 0, sizeof(mgCFrameAttr));

	// TODO: More member variable setting down here
}

mgCFrameAttr::mgCFrameAttr()
{
	Initialize();
}

void mgCFrame::GetWorldBBox(mgVu0FBOX& box)
{
	todo;
}

void mgCFrame::Draw(void* p)
{
	todo;
}

void mgCFrame::SetVisual(mgCVisual* visual)
{
	todo;
}

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
