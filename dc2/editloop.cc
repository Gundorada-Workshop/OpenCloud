#include <array>
#include "glm/glm.hpp"
#include "common/debug.h"
#include "common/log.h"
#include "editloop.h"
#include "ls_mes.h"
#include "mg_frame.h"
#include "mg_memory.h"

set_log_channel("editloop");

// 01E9B440
static CWaveTable WaveTable{};
// 01E9C650
static glm::vec4 CharaOldPos{};
// 01E9C660
static ClsMes EventMes1{};
// 01E9E840
static mgCMemory buf0{};
// 01E9E870
static mgCMemory buf1{};
// 01E9E8A0
static std::array<mgCMemory, 2> data_buf{};
// 01E9E900
static std::array<mgCMemory, 2> init_dbuf{};
// 01E9E960
static mgCMemory WorkBuffer{};
// 01E9E990
static mgCMemory MenuBuffer{};
// 01E9E9C0
static mgCMemory ChrEffBuffer{};
// 01E9E990
static mgCMemory Script_Buffer{};
// 01E9EA20
static mgCMemory TotalDataBuff{};
// 01E9EA50
static mgCMemory ControlCharaBuff{};
// 01E9EA80
static mgCMemory MainDataBuff{};
// 01E9EA80
static mgCMemory MainCharaBuff{};
// 01E9EAE0
static mgCMemory SubDataBuff{};
// 01E9EB10
static mgCMemory SubCharaBuff{};
// 01E9EB40
static std::array<mgCMemory, 4> EventBuff{};
// 01E9EC00
static std::array<mgCMemory, 8> CharaBufs{};
// 01E9ED80
static mgCMemory FishingBuff{};
// 01E9EDB0
static mgCMemory SkyBuff{};
// 01E9EDE0
static CEditEvent EditEvent{};
// 01E9EF30
static EditDebugInfo EdDebugInfo{};
// 01E9EF70
static mgCVisualMDT TestVisual{};
// 01E9EFC0
static mgCFrame TestFrame{};
// 01E9F0F0
static std::array<_DWORD, 0x10> beforeAnalyze{};

// 001A2110
CWaveTable::CWaveTable()
{
  log_trace("CWaveTable::CWaveTable()");

  memset(&m_unk_field_0, 0, sizeof(m_unk_field_0));
  memset(&m_unk_field_900, 0, sizeof(m_unk_field_900));
  m_unk_field_1200 = 0;
}

// 002EF9B0
void CEditEvent::Reset()
{
  log_trace("CEditEvent::Reset()");

  m_unk_field_4 = 0;
  m_unk_field_C = 0;
  m_unk_field_0 = 0;
  m_unk_field_10 = -1;
  m_unk_field_148 = -1;
  m_unk_field_128 = 0;

  memset(&m_unk_field_20, 0, sizeof(m_unk_field_20));
}