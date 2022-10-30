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
	memcpy(&m_corner1, &box.m_corner1, sizeof(m_corner1));
	memcpy(&m_corner2, &box.m_corner2, sizeof(m_corner2));
}

void mgCObject::ChangeParam(void)
{
	// TODO
	assert(false);
}

void mgCObject::UseParam(void)
{
	// TODO
	assert(false);
}

void mgCObject::SetPosition(vec4&)
{
	// TODO
	assert(false);
}

void mgCObject::SetPosition(float x, float y, float z)
{
	// TODO
	assert(false);
}

void mgCObject::GetPosition(vec4&)
{
	// TODO
	assert(false);
}

void mgCObject::SetRotation(vec4&)
{
	// TODO
	assert(false);
}

void mgCObject::SetRotation(float x, float y, float z)
{
	// TODO
	assert(false);
}

void mgCObject::GetRotation(vec4&)
{
	// TODO
	assert(false);
}

void mgCObject::SetScale(vec4&)
{
	// TODO
	assert(false);
}

void mgCObject::SetScale(float x, float y, float z)
{
	// TODO
	assert(false);
}

void mgCObject::GetScale(vec4&)
{
	// TODO
	assert(false);
}

void mgCObject::Draw(void)
{
	// TODO
	assert(false);
}

int mgCObject::DrawDirect(void)
{
	// TODO
	assert(false);
	return 0;
}

void mgCObject::Initialize(void)
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
