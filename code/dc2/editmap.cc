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

// 00297770
void CEditGrid::Create(usize x, usize y)
{
  log_trace("CEditGrid::{}({}, {})", __func__, x, y);

  usize capacity = x * y;
  m_tiles.reserve(capacity);

  for (usize i = 0; i < capacity; ++i)
  {
    m_tiles.emplace_back();
  }
}

// 00297860
void CEditGrid::Clear()
{
  log_trace("CEditGrid::{}()", __func__);

  m_tiles.clear();
}

// 002978B0
bool CEditGrid::Check(usize x, usize y) const
{
  log_trace("CEditGrid::{}({}, {})", __func__, x, y);

  return x < m_x && y < m_y;
}

// 00297900
CGridData* CEditGrid::Get(usize x, usize y)
{
  log_trace("CEditGrid::{}({}, {})", __func__, x, y);

  if (!Check(x, y))
  {
    return nullptr;
  }

  return GetFast(x, y);
}

// 00297990
// local position (discrete x, y position)
std::optional<std::pair<usize, usize>> CEditGrid::GetLPos(f32 x, f32 y) const
{
  log_trace("CEditGrid::{}({}, {})", __func__, x, y);

  // Localize x and y to our grid
  x = (x - m_grid_start_pos.x) / m_tile_len_x;
  y = (y - m_grid_start_pos.y) / m_tile_len_y;

  // Now check that x and y are valid
  if (x < 0.0f || y < 0.0f)
  {
    return std::nullopt;
  }

  std::pair<usize, usize> result = { static_cast<usize>(x), static_cast<usize>(y) };
  if (!Check(result.first, result.second))
  {
    return std::nullopt;
  }

  return result;
}

// 00297A50
// world position (where are we in the scene, actually?)
vec3 CEditGrid::GetWPos(usize x, usize y) const
{
  log_trace("CEditGrid::{}({}, {})", __func__, x, y);

  return vec3
  {
    static_cast<f32>(x) * m_tile_len_x + m_grid_start_pos.x,
    0.0f,
    static_cast<f32>(y) * m_tile_len_y + m_grid_start_pos.y,
  };
}

// 00297AA0
bool CEditGrid::SetRiver(f32 x, f32 y)
{
  log_trace("CEditGrid::{}({}, {})", __func__, x, y);

  auto local_pos = GetLPos(x, y);
  if (!local_pos.has_value())
  {
    return false;
  }

  return SetRiver(local_pos.value().first, local_pos.value().second);
}

// 00297AA0
bool CEditGrid::ResetRiver(f32 x, f32 y)
{
  log_trace("CEditGrid::{}({}, {})", __func__, x, y);

  auto local_pos = GetLPos(x, y);
  if (!local_pos.has_value())
  {
    return false;
  }

  return ResetRiver(local_pos.value().first, local_pos.value().second);
}

// 00297B20
bool CEditGrid::SetRiver(usize x, usize y)
{
  log_trace("CEditGrid::{}({}, {})", __func__, x, y);

  auto grid_data = Get(x, y);
  if (grid_data == nullptr)
  {
    return false;
  }

  grid_data->m_river = true;

  // Update this and all adjacent rivers
  // this is the call order I dunno if it matters, it's kind of funky
  UpdateRiver(x + 0, y + 0);
  UpdateRiver(x - 1, y + 0);
  UpdateRiver(x + 1, y + 0);
  UpdateRiver(x + 0, y + 1);
  UpdateRiver(x + 0, y - 1);
  UpdateRiver(x - 1, y - 1);
  UpdateRiver(x + 1, y - 1);
  UpdateRiver(x + 1, y + 1);
  UpdateRiver(x - 1, y + 1);

  return true;
}

// 00297C10
bool CEditGrid::ResetRiver(usize x, usize y)
{
  log_trace("CEditGrid::{}({}, {})", __func__, x, y);

  auto grid_data = Get(x, y);
  if (grid_data == nullptr || !grid_data->m_river)
  {
    return false;
  }

  grid_data->m_river = false;

  // Update this and all adjacent rivers
  // this is the call order I dunno if it matters, it's kind of funky
  UpdateRiver(x + 0, y + 0);
  UpdateRiver(x - 1, y + 0);
  UpdateRiver(x + 1, y + 0);
  UpdateRiver(x + 0, y + 1);
  UpdateRiver(x + 0, y - 1);
  UpdateRiver(x - 1, y - 1);
  UpdateRiver(x + 1, y - 1);
  UpdateRiver(x + 1, y + 1);
  UpdateRiver(x - 1, y + 1);

  return true;
}

// 00297D10
bool CEditGrid::UpdateRiver(usize x, usize y)
{
  log_trace("CEditGrid::{}({}, {})", __func__, x, y);

  todo;
  return false;
}

// 00298040
bool CEditGrid::River(usize x, usize y)
{
  log_trace("CEditGrid::{}({}, {})", __func__, x, y);

  auto grid_data = Get(x, y);
  return grid_data != nullptr && grid_data->m_river;
}

// 00298070
void CEditGrid::GetRiverPos(usize x, usize y, matrix4& dest) const
{
  log_trace("CEditGrid::{}({}, {}, {})", __func__, x, y, fmt::ptr(&dest));

  todo;
}

// 00298170
void CEditGrid::GetRiverPos(usize x, usize y, vec3& dest) const
{
  log_trace("CEditGrid::{}({}, {}, {})", __func__, x, y, fmt::ptr(&dest));

  todo;
}

// 00298200
void CEditGrid::GetRiverPoly(CCPoly* dest, const mgVu0FBOX& box, sint i, f32 f)
{
  log_trace("CEditGrid::{}({}, {}, {}, {})", __func__, fmt::ptr(&dest), fmt::ptr(&box), i, f);

  todo;
}

// 002985C0
mgVu0FBOX CEditGrid::GetGridBox(const vec3& pos) const
{
  log_trace("CEditGrid::{}({})", __func__, fmt::ptr(&pos));

  todo;
  return mgVu0FBOX{};
}

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

// 001B5630
EEPartsType CEditPartsInfo::GetPartsType() const
{
  log_trace("CEditPartsInfo::{}()", __func__);

  // FIXME: MAGIC
  if ((m_unk_field_4 & 0x40) != 0)
  {
    return EEPartsType::_1;
  }
  if ((m_unk_field_4 & 0x80) != 0)
  {
    return EEPartsType::_11;
  }

  return m_type;
}

// 001B5670
void CEditPartsInfo::CreateBox()
{
  log_trace("CEditPartsInfo::{}()", __func__);

  new (&m_parts_bound_box) mgVu0FBOX();
}

// 001B56A0
f32 CEditPartsInfo::GetPartsHeight() const
{
  log_trace("CEditPartsInfo::{}()", __func__);

  return m_parts_bound_box.corners[0].y - m_parts_bound_box.corners[1].y;
}

// 001B56B0
f32 CEditPartsInfo::GetPartsMaxWidth() const
{
  log_trace("CEditPartsInfo::{}()", __func__);

  vec3 temp = m_parts_bound_box.corners[0] - m_parts_bound_box.corners[1];
  return std::max({ temp.x, temp.y, temp.z });
}

// 001B5730
EditPartsMaterial* CEditPartsInfo::GetMaterial(ssize index)
{
  log_trace("CEditPartsInfo::{}({})", __func__, index);

  if (index < 0 || index >= m_material.size())
  {
    return nullptr;
  }

  return &m_material[index];
}

// 001B5760
std::optional<vec3> CEditPartsInfo::GetDefColor(ssize index) const
{
  log_trace("CEditPartsInfo::{}({})", __func__, index);

  if (m_unk_field_44 == nullptr)
  {
    return std::nullopt;
  }

  return m_unk_field_44->GetDefColor(index);
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
EEPartsInfoID CEditParts::GetInfoID() const
{
  log_trace("CEditParts::{}()", __func__);

  if (m_info == nullptr)
  {
    return EEPartsInfoID::Invalid;
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
CEditPartsInfo* CEditInfoMngr::GetePartsInfoAtID(EEPartsInfoID id)
{
  log_trace("CEditInfoMngr::{}({})", __func__, std::to_underlying(id));

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
