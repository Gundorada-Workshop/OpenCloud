#include <assert.h>
#include <string.h>
#include "mg_Frame.h"


namespace mg_Frame
{
	void SInit()
	{
		new (&stru_380DA0) mgCFrameAttr();
	}
}

mgVu0FBOX::mgVu0FBOX(mgVu0FBOX& box)
{
	m_corner1 = box.m_corner1;
	m_corner2 = box.m_corner2;
}

void mgCObject::ChangeParam()
{
	// TODO
	assert(false);
}

void mgCObject::UseParam()
{
	// TODO
	assert(false);
}

void mgCObject::SetPosition(glm::vec4& v)
{
	// TODO
	assert(false);
}

void mgCObject::SetPosition(float x, float y, float z)
{
	// TODO
	assert(false);
}

void mgCObject::GetPosition(glm::vec4& v)
{
	// TODO
	assert(false);
}

void mgCObject::SetRotation(glm::vec4& v)
{
	// TODO
	assert(false);
}

void mgCObject::SetRotation(float x, float y, float z)
{
	// TODO
	assert(false);
}

void mgCObject::GetRotation(glm::vec4& v)
{
	// TODO
	assert(false);
}

void mgCObject::SetScale(glm::vec4& v)
{
	// TODO
	assert(false);
}

void mgCObject::SetScale(float x, float y, float z)
{
	// TODO
	assert(false);
}

void mgCObject::GetScale(glm::vec4& v)
{
	// TODO
	assert(false);
}

void mgCObject::Draw()
{
	// TODO
	assert(false);
}

int mgCObject::DrawDirect()
{
	// TODO
	assert(false);
	return 0;
}

void mgCObject::Initialize()
{
	// TODO
	assert(false);
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
	// TODO
	assert(false);
}

void mgCFrame::Draw(void* p)
{
	// TODO
	assert(false);
}

void mgCFrame::SetVisual(CVisual* visual)
{
	// TODO
	assert(false);
}

void mgCDrawEnv::Initialize(bool b)
{
	// TODO
	assert(false);
}

mgCDrawEnv::mgCDrawEnv()
{
	Initialize(false);
}

mgCDrawEnv::mgCDrawEnv(mgCDrawEnv& other)
{
	memcpy(this, &other, sizeof(this));
}
