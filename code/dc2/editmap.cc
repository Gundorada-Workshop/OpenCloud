#include "common/log.h"

#include "dc2/editmap.h"
#include "dc2/script_interpreter.h"

set_log_channel("editmap");

// 00377F44
static CEditInfoMngr* emapInfo{};
// 00377F4C
static sint emapIdx{};
// 00377F50
static sint emapMatID{};
// 00377F54
static CEditInfoMngr* emapNowInfo{};
// 00377F58
static sint emapRectType{};
// 00377F5C
static rect* emapRect{};
// 00377F60
static sint emapRectNum{};
// 00377F64
static sint emapRectIdx{};
// 00377F68
static sint emapFixNum{};
// 00377F6C
static sint emapFixIdx{};

// 003543C0
const static SPI_TAG_PARAM emap_tag[] = {
  // TODO
  nullptr, nullptr
};

// 001B5790
bool CEditHouse::LiveChara() const
{
  log_trace("CEditHouse::{}()", __func__);

  for (auto chara_id : m_occupant_ids)
  {
    if (chara_id != ECharacterID::Invalid)
    {
      return true;
    }
  }

  return false;
}

// 001B5630
EEPartsType CEditPartsInfo::GetPartsType() const
{
  log_trace("CEditPartsInfo::{}()", __func__);

  todo;
  return EEPartsType(0);
}

// 002A4DE0
void CEditInfoMngr::SetePartsInfoTable(usize capacity)
{
  log_trace("CEditInfoMngr::{}({})", __func__, capacity);

  m_eparts_info.clear();
  m_eparts_info.reserve(capacity);

  for (usize i = 0; i < capacity; ++i)
  {
    m_eparts_info.emplace_back();
  }
}

// 002A4DF0
void CEditInfoMngr::SeteFixPartsTable(usize capacity)
{
  log_trace("CEditInfoMngr::{}({})", __func__, capacity);

  m_efix_parts.clear();
  m_efix_parts.reserve(capacity);

  for (usize i = 0; i < capacity; ++i)
  {
    m_efix_parts.emplace_back();
  }
}

// 002A4E00
CEditPartsInfo* CEditInfoMngr::GetePartsInfo(ssize index)
{
  log_trace("CEditInfoMngr::{}({})", __func__, index);

  if (index < 0 || index >= m_eparts_info.size())
  {
    return nullptr;
  }

  return &m_eparts_info[index];
}

// 002A4E40
CEditPartsInfo* CEditInfoMngr::GetePartsInfo(const std::string& parts_name)
{
  log_trace("CEditInfoMngr::{}({})", __func__, parts_name);

  for (auto& parts_info : m_eparts_info)
  {
    if (parts_name == parts_info.m_name)
    {
      return &parts_info;
    }
  }

  return nullptr;
}

// 002A4ED0
CEditPartsInfo* CEditInfoMngr::GetePartsInfoAtID(ssize id)
{
  log_trace("CEditInfoMngr::{}({})", __func__, id);

  for (auto& parts_info : m_eparts_info)
  {
    if (id == parts_info.m_id)
    {
      return &parts_info;
    }
  }

  return nullptr;
}

// 002A4F40
CEditPartsInfo* CEditInfoMngr::GetPartsInfoAtType(EEPartsType parts_type)
{
  log_trace("CEditInfoMngr::{}({})", __func__, std::to_underlying(parts_type));

  for (auto& parts_info : m_eparts_info)
  {
    if (parts_type == parts_info.GetPartsType())
    {
      return &parts_info;
    }
  }

  return nullptr;
}

// 002A58E0
void CEditInfoMngr::LoadEditInfo(char* file, usize file_len)
{
  log_trace("CEditInfoMngr::{}({})", __func__, capacity);

  emapInfo = this;
  emapIdx = 0;
  emapNowInfo = 0;
  emapRect = nullptr;
  emapRectNum = 0;
  emapRectIdx = 0;
  emapFixNum = 0;
  emapFixIdx = 0;

  CScriptInterpreter interpreter{};

  interpreter.SetTag(emap_tag);
  interpreter.SetScript(file, file_len);
  interpreter.Run();
}
