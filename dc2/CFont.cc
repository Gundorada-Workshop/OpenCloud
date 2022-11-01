#include "common/debug.h"
#include "common/log.h"

#include "CFont.h"

set_log_channel("CFont");

void CFont::SetFuchi(s32 fuchi)
{
	log_trace("SetFuchi({})", fuchi);

	m_fuchi = fuchi;
}

void CFont::Initialize()
{
	log_trace("Initialize()");

	memset(&m_str, 0, sizeof(m_str));
	SetFuchi(3);

	m_unk_field_88 = 0x80;
	m_unk_field_89 = 0x80;
	m_unk_field_8A = 0x80;
	m_unk_field_8B = 0x80;

	m_unk_field_90 = 0x80;

	m_unk_field_98 = 0;
	m_unk_field_94 = 0;

	m_unk_field_9C = 15;

	m_unk_field_A0 = 24;

	m_unk_field_A4 = 16;

	m_unk_field_A8 = 20;

	m_unk_field_AC = 0;
}
