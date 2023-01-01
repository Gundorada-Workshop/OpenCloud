#include <ranges>

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
    if (chara_id > 0)
    {
      return true;
    }
  }

  return false;
}

// 001B57F0
static f32 StandardPos(f32 f)
{
  log_trace("{}({})", __func__, f);

  f32 epsilon = (f > 0.0f) ? 0.001 : -0.001;
  return truncf(f + epsilon);
}

// 001B5860
void CEditParts::SetPosition(const vec3& position)
{
  log_trace("CEditParts::{}(({}, {}, {}))", __func__, position.x, position.y, position.z);

  if (m_unk_field_314 != nullptr)
  {
    vec3 old_pos = GetPosition();
    mgCObject::SetPosition(vec3{ position.x, StandardPos(old_pos.y), position.z });
  }
  else
  {
    mgCObject::SetPosition(position);
  }
}

// 001B58E0
void CEditParts::SetPosition(f32 x, f32 y, f32 z)
{
  log_trace("CEditParts::{}({}, {}, {})", __func__, x, y, z);

  SetPosition(vec3{ x, y, z });
}

// 001B5930
vec3 CEditParts::GetPosition()
{
  log_trace("CEditParts::{}()", __func__);

  vec3 local_pos = GetLocalPos();

  if (m_unk_field_314 != nullptr)
  {
    vec3 pos = GetPosition();
    local_pos.y += StandardPos(pos.y);
  }

  return local_pos;
}

// 001B59A0
void CEditParts::UpdatePosition()
{
  log_trace("CEditParts::{}()", __func__);

  if (!m_unk_field_40 && m_unk_field_314 == nullptr)
  {
    return;
  }

  vec3 local_pos = GetLocalPos();

  if (m_unk_field_314 != nullptr)
  {
    local_pos.y += m_unk_field_314->GetPosition().y;
  }

  m_unk_field_C0.SetPosition(local_pos);
  m_unk_field_C0.SetRotation(m_rotation);
  m_unk_field_C0.SetScale(m_scale);

  m_unk_field_40 = false;
}

// 001B5A50
sint CEditParts::GetInfoID() const
{
  log_trace("CEditParts::{}()", __func__);

  if (m_info == nullptr)
  {
    return -1;
  }

  return m_info->m_id;
}

// 001B5990
vec3 CEditParts::GetLocalPos()
{
  log_trace("CEditParts::{}()", __func__);

  return mgCObject::GetPosition();
}

// 001B5A70
sint CEditParts::GetLiveNPC() const
{
  log_trace("CEditParts::{}()", __func__);

  if (m_house == nullptr)
  {
    return -1;
  }

  return m_house->m_occupant_ids.front();
}

// 001B5A90
bool CEditParts::IsWallParts() const
{
  log_trace("CEditParts::{}()", __func__);

  if (m_info == nullptr)
  {
    return false;
  }

  todo;
  return false;
}

// 001B5AC0
bool CEditParts::IsFence() const
{
  log_trace("CEditParts::{}()", __func__);

  if (m_info == nullptr)
  {
    return false;
  }

  // FIXME: MAGIC
  return ((m_info->m_unk_field_4 & 0x130) == 0x130);
}

// 001B5AF0
bool CEditParts::IsBurn() const
{
  log_trace("CEditParts::{}()", __func__);

  if (m_info == nullptr)
  {
    return false;
  }

  // FIXME: MAGIC
  return ((m_info->m_unk_field_4 & 0x1000) != 0x0);
};

// 001B5B20
bool CEditParts::GetFenceSide(vec3& v1_dest, vec3& v2_dest)
{
  log_trace("CEditParts::{}()", __func__);

  if (!m_bounding_box_valid || m_info == nullptr)
  {
    return false;
  }

  matrix4 lw_mat = GetLWMatrix();
  vec4 var_20 = vec4{ m_info->m_unk_field_A0, 1.0f };
  vec4 var_10 = vec4{ m_info->m_unk_field_B0, 1.0f };

  v1_dest = lw_mat * var_20;
  v2_dest = lw_mat * var_10;
  return true;
}

// 001B5BD0
bool CEditParts::GetWallPlane(sint i, WallInfo* wall_info) const
{
  log_trace("CEditParts::{}()", __func__);

  todo;
  return false;
}

// 001B5DC0
sint CEditParts::GetWallGroupNum() const
{
  log_trace("CEditParts::{}()", __func__);

  if (m_info == nullptr)
  {
    return 0;
  }

  return m_info->m_wall_group_num;
}

// 001B5DE0
EEPartsType CEditParts::GetPartsType() const
{
  log_trace("CEditParts::{}()", __func__);

  if (m_info == nullptr)
  {
    return EEPartsType::Invalid;
  }

  return m_info->GetPartsType();
}

// 001B5E20
bool CEditParts::CheckTerritory(const CEditParts* other) const
{
  log_trace("CEditParts::{}()", __func__);

  todo;
  return false;
}

// 001B5F50
void CEditParts::CheckColorUpdate()
{
  log_trace("CEditParts::{}()", __func__);

  for (const auto& map_piece : m_map_pieces)
  {
    if (map_piece.m_material.size() > 0)
    {
      m_n_material = std::max<sint>(map_piece.m_material.size(), m_n_material);
    }
  }
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
  log_trace("CEditInfoMngr::{}({}, {})", __func__, file, file_len);

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
