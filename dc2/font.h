#pragma once

// ~ 002D4130 - 002D87F0

class CFont
{
public:
	// 002D4570
	void SetFuchi(s32 fuchi);
	// 002D5D40
	void Initialize();

	// 0
	char m_str[0x80];
	// 80
	s32 m_fuchi;
	
	// ?

	// 88
	u8 m_unk_field_88;
	// 89
	u8 m_unk_field_89;
	// 8A
	u8 m_unk_field_8A;
	// 8B
	u8 m_unk_field_8B;
	// 90
	u32 m_unk_field_90;
	// 94
	_UNKNOWN m_unk_field_94;
	// 98
	_UNKNOWN m_unk_field_98;
	// 9C
	u32 m_unk_field_9C;
	// A0
	u32 m_unk_field_A0;
	// A4
	u32 m_unk_field_A4;
	// A8
	u32 m_unk_field_A8;
	// AC
	_UNKNOWN m_unk_field_AC;
};
