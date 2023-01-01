#pragma once
#include "common/debug.h"
#include "common/types.h"

#include "dc2/map.h"
#include "dc2/userdata.h"

struct ePlaceData
{
public:
};

struct EP_PLACE_INFO
{
public:
};

enum class EEPartsType
{

};

class CEditPartsInfo
{
public:
  // 001B5630
  EEPartsType GetPartsType() const;

  // 0
  ssize m_id{};

  // 3C
  std::string m_name{};

  // SIZE 0x280
};

class CEditHouse
{
public:
  // 001B5790
  bool LiveChara() const;

  bool m_active{};
  std::array<ECharacterID, 3> m_occupant_ids{ ECharacterID::Invalid };
};

class CEditParts
{
public:
  struct WallInfo
  {
  public:
  };
};

class CEditInfoMngr
{
public:
  // 002A4DE0
  void SetePartsInfoTable(usize capacity);
  
  // 002A4DF0
  void SeteFixPartsTable(usize capacity);

  // 002A4E00
  CEditPartsInfo* GetePartsInfo(ssize index);

  // 002A4E40
  CEditPartsInfo* GetePartsInfo(const std::string& parts_name);

  // 002A4ED0
  CEditPartsInfo* GetePartsInfoAtID(ssize id);

  // 002A4F40
  CEditPartsInfo* GetPartsInfoAtType(EEPartsType parts_type);

  // 002A58E0
  void LoadEditInfo(char* file, usize file_len);

  // 0 (length), 4 (buf)
  std::vector<CEditPartsInfo> m_eparts_info{};
  // 8 (length), C (buf)
  std::vector<ePlaceData> m_efix_parts{};
  // 10
  unk32 m_unk_field_10{};
  // 14
  unk32 m_unk_field_14{};
};

class CEditMap
{
public:
  struct RemoveInfo
  {
  public:
  };

  // F94
  CEditInfoMngr m_edit_info{};
};