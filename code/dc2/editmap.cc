#include <ranges>

#include "common/clock.h"
#include "common/helpers.h"
#include "common/log.h"

#include "graph/rectangle.h"

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
static graph::rect* emapRect{};
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
//std::optional<std::pair<usize, usize>> CEditGrid::GetLPos(f32 x, f32 y) const
//{
//  log_trace("CEditGrid::{}({}, {})", __func__, x, y);
//
//  // Localize x and y to our grid
//  x = (x - m_grid_start_pos.x) / m_tile_len_x;
//  y = (y - m_grid_start_pos.y) / m_tile_len_y;
//
//  // Now check that x and y are valid
//  if (x < 0.0f || y < 0.0f)
//  {
//    return std::nullopt;
//  }
//
//  std::pair<usize, usize> result = { static_cast<usize>(x), static_cast<usize>(y) };
//  if (!Check(result.first, result.second))
//  {
//    return std::nullopt;
//  }
//
//  return result;
//}

// 00297A50
// world position (where are we in the scene, actually?)
//vec3 CEditGrid::GetWPos(usize x, usize y) const
//{
//  log_trace("CEditGrid::{}({}, {})", __func__, x, y);
//
//  return vec3
//  {
//    static_cast<f32>(x) * m_tile_len_x + m_grid_start_pos.x,
//    0.0f,
//    static_cast<f32>(y) * m_tile_len_y + m_grid_start_pos.y,
//  };
//}

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
//void CEditGrid::GetRiverPos(usize x, usize y, matrix4& dest) const
//{
//  log_trace("CEditGrid::{}({}, {}, {})", __func__, x, y, fmt::ptr(&dest));
//
//  todo;
//}

// 00298170
//void CEditGrid::GetRiverPos(usize x, usize y, vec3& dest) const
//{
//  log_trace("CEditGrid::{}({}, {}, {})", __func__, x, y, fmt::ptr(&dest));
//
//  todo;
//}

// 00298200
//void CEditGrid::GetRiverPoly(CCPoly* dest, const mgVu0FBOX& box, sint i, f32 f)
//{
//  log_trace("CEditGrid::{}({}, {}, {}, {})", __func__, fmt::ptr(&dest), fmt::ptr(&box), i, f);
//
//  todo;
//}

// 002985C0
//mgVu0FBOX CEditGrid::GetGridBox(const vec3& pos) const
//{
//  log_trace("CEditGrid::{}({})", __func__, fmt::ptr(&pos));
//
//  todo;
//  return mgVu0FBOX{};
//}

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
//void CEditPartsInfo::CreateBox()
//{
//  log_trace("CEditPartsInfo::{}()", __func__);
//
//  m_parts_bound_box = mgVu0FBOX();
//}

// 001B56A0
//f32 CEditPartsInfo::GetPartsHeight() const
//{
//  log_trace("CEditPartsInfo::{}()", __func__);
//
//  return m_parts_bound_box.corners[0].y - m_parts_bound_box.corners[1].y;
//}

// 001B56B0
//f32 CEditPartsInfo::GetPartsMaxWidth() const
//{
//  log_trace("CEditPartsInfo::{}()", __func__);
//
//  vec3 temp = m_parts_bound_box.corners[0] - m_parts_bound_box.corners[1];
//  return std::max({ temp.x, temp.y, temp.z });
//}

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
//std::optional<vec3> CEditPartsInfo::GetDefColor(ssize index) const
//{
//  log_trace("CEditPartsInfo::{}({})", __func__, index);
//
//  if (m_unk_field_44 == nullptr)
//  {
//    return std::nullopt;
//  }
//
//  return m_unk_field_44->GetDefColor(index);
//}

// 001B57F0
static f32 StandardPos(f32 f)
{
  log_trace("{}({})", __func__, f);

  f32 epsilon = (f > 0.0f) ? 0.001 : -0.001;
  return truncf(f + epsilon);
}

// 001B5860
//void CEditParts::SetPosition(const vec3& position)
//{
//  log_trace("CEditParts::{}(({}, {}, {}))", __func__, position.x, position.y, position.z);
//
//  if (m_unk_field_314 != nullptr)
//  {
//    vec3 old_pos = GetPosition();
//    mgCObject::SetPosition(vec3{ position.x, StandardPos(old_pos.y), position.z });
//  }
//  else
//  {
//    mgCObject::SetPosition(position);
//  }
//}

// 001B58E0
//void CEditParts::SetPosition(f32 x, f32 y, f32 z)
//{
//  log_trace("CEditParts::{}({}, {}, {})", __func__, x, y, z);
//
//  SetPosition(vec3{ x, y, z });
//}

// 001B5930
//vec3 CEditParts::GetPosition()
//{
//  log_trace("CEditParts::{}()", __func__);
//
//  vec3 local_pos = GetLocalPos();
//
//  if (m_unk_field_314 != nullptr)
//  {
//    vec3 pos = GetPosition();
//    local_pos.y += StandardPos(pos.y);
//  }
//
//  return local_pos;
//}

// 001B59A0
//void CEditParts::UpdatePosition()
//{
//  log_trace("CEditParts::{}()", __func__);
//
//  if (!m_unk_field_40 && m_unk_field_314 == nullptr)
//  {
//    return;
//  }
//
//  vec3 local_pos = GetLocalPos();
//
//  if (m_unk_field_314 != nullptr)
//  {
//    local_pos.y += m_unk_field_314->GetPosition().y;
//  }
//
//  m_unk_field_C0.SetPosition(local_pos);
//  m_unk_field_C0.SetRotation(m_rotation);
//  m_unk_field_C0.SetScale(m_scale);
//
//  m_unk_field_40 = false;
//}

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
//vec3 CEditParts::GetLocalPos()
//{
//  log_trace("CEditParts::{}()", __func__);
//
//  return mgCObject::GetPosition();
//}

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
//bool CEditParts::GetFenceSide(vec3& v1_dest, vec3& v2_dest)
//{
//  log_trace("CEditParts::{}()", __func__);
//
//  if (!m_bounding_box_valid || m_info == nullptr)
//  {
//    return false;
//  }
//
//  matrix4 lw_mat = GetLWMatrix();
//  vec4 var_20 = vec4{ m_info->m_unk_field_A0, 1.0f };
//  vec4 var_10 = vec4{ m_info->m_unk_field_B0, 1.0f };
//
//  v1_dest = lw_mat * var_20;
//  v2_dest = lw_mat * var_10;
//  return true;
//}

// 001B5BD0
bool CEditParts::GetWallPlane(MAYBE_UNUSED sint i, MAYBE_UNUSED WallInfo* wall_info) const
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
bool CEditParts::CheckTerritory(MAYBE_UNUSED const CEditParts* other) const
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
  log_trace("CEditInfoMngr::{}({})", __func__, common::to_underlying(id));

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
CEditPartsInfo* CEditInfoMngr::GetePartsInfoAtType(EEPartsType parts_type)
{
  log_trace("CEditInfoMngr::{}({})", __func__, common::to_underlying(parts_type));

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

// 001B4130
unkptr CEditMap::DrawSub(bool b)
{
  log_trace("CEditMap::{}({})", __func__, b);

  todo;
  return nullptr;
}

// 001B40A0
//bool CEditMap::PreDraw(const vec3& v)
//{
//  log_trace("CEditMap::{}({})", __func__, fmt::ptr(&v));
//
//  todo;
//  return false;
//}

// 0029C1C0
void CEditMap::DrawEffect()
{
  log_trace("CEditMap::{}()", __func__);

  todo;
}

// 0029BFD0
void CEditMap::DrawFireEffect(sint i)
{
  log_trace("CEditMap::{}({})", __func__, i);

  todo;
}

// 0029C110
void CEditMap::DrawFireRaster()
{
  log_trace("CEditMap::{}()", __func__);

  todo;
}

// 001B0780
//sint CEditMap::GetPoly(sint i1, CCPoly* dest, mgVu0FBOX& box, sint i2)
//{
//  log_trace("CEditMap::{}({}, {}, {}, {})", __func__, i1, fmt::ptr(dest), fmt::ptr(&box), i2);
//
//  todo;
//  return 0;
//}

// 002A5960
//void CEditMap::GetEvent(const vec3* v, sint i, MapEventInfo* dest)
//{
//  log_trace("CEditMap::{}({}, {}, {})", __func__, fmt::ptr(v), i, fmt::ptr(dest));
//
//  todo;
//}

// 002EF530
void CEditMap::InScreenFunc(InScreenFuncInfo* func_info)
{
  log_trace("CEditMap::{}({})", __func__, fmt::ptr(func_info));

  todo;
}

// 002EF630
void CEditMap::DrawScreenFunc(mgCFrame* frame)
{
  log_trace("CEditMap::{}({})", __func__, fmt::ptr(frame));

  todo;
}

// 002EF6D0
void CEditMap::GetSeSrcVolPan(sint* ip, f32* fp1_dest, f32* fp2_dest, sint i)
{
  log_trace("CEditMap::{}({}, {}, {}, {})", __func__, fmt::ptr(ip), fmt::ptr(fp1_dest), fmt::ptr(fp2_dest), i);

  todo;
}

// 0029C330
void CEditMap::AnimeStep(CObjAnimeEnv* env)
{
  log_trace("CEditMap::{}({})", __func__, fmt::ptr(env));

  todo;
}

// 001B4090
void CEditMap::Step()
{
  log_trace("CEditMap::{}()", __func__);

  m_unk_field_F68 += GAME_FPS * GAME_DT;
  CMap::Step();
}

// 001B02A0
std::string CEditMap::Iam() const
{
  log_trace("CEditMap::{}()", __func__);

  return CEditMapName;
}

// 001B0390
void CEditMap::ClearGrid()
{
  log_trace("CEditMap::{}()", __func__);

  for (auto& grid : m_edit_grid)
  {
    if (grid != nullptr)
    {
      grid->Clear();
    }
  }
}

// 001B0400
void CEditMap::ClearHouse()
{
  log_trace("CEditMap::{}()", __func__);

  for (auto& house : m_house)
  {
    house = CEditHouse();
  }
}

// 001B0460
void CEditMap::ClearAllParts()
{
  log_trace("CEditMap::{}()", __func__);

  todo;
}

// 001B0660
void CEditMap::InitialPlaceParts(CEditData* edit_data)
{
  log_trace("CEditMap::{}({})", __func__, fmt::ptr(edit_data));

  todo;
}

// 001B0960
void CEditMap::CreateTable(sint i1, sint i2)
{
  log_trace("CEditMap::{}({}, {})", __func__, i1, i2);

  todo;
}

// 001B0B30
CEditPartsInfo* CEditMap::GetePartsInfo(ssize index)
{
  log_trace("CEditMap::{}()", __func__);

  return m_edit_info_mngr.GetePartsInfo(index);
}

// 001B0B40
CEditPartsInfo* CEditMap::GetePartsInfo(const std::string& name)
{
  log_trace("CEditMap::{}({})", __func__, name);

  return m_edit_info_mngr.GetePartsInfo(name);
};

// 001B0B50
CEditPartsInfo* CEditMap::GetePartsInfoAtID(EEPartsInfoID id)
{
  log_trace("CEditMap::{}({})", __func__, common::to_underlying(id));

  return m_edit_info_mngr.GetePartsInfoAtID(id);
}

// 001B0B60
CEditPartsInfo* CEditMap::GetePartsInfoAtType(EEPartsType type)
{
  log_trace("CEditMap::{}({})", __func__, common::to_underlying(type));

  return m_edit_info_mngr.GetePartsInfoAtType(type);
}

// 001B0B70
CEditPartsInfo* CEditMap::GetePartsInfoAtPlaceID(ssize place_id)
{
  log_trace("CEditMap::{}({})", __func__, place_id);

  auto parts = GetePlaceParts(place_id);
  if (parts == nullptr)
  {
    return nullptr;
  }

  return parts->m_info;
}

// 001B0BA0
CEditParts* CEditMap::eNewPlaceParts()
{
  log_trace("CEditMap::{}()", __func__);

  todo;
  return nullptr;
}

// 001B0C00
CEditHouse* CEditMap::eNewHouseInfo()
{
  log_trace("CEditMap::{}()", __func__);

  for (auto& house : m_house)
  {
    if (!house.m_active)
    {
      return &house;
    }
  }

  return nullptr;
}

// 001B0C40
CEditParts* CEditMap::GetePlaceParts(ssize index)
{
  log_trace("CEditMap::{}({})", __func__, index);

  todo;
  return nullptr;
}

// 001B0CA0
CEditParts* CEditMap::GetePlaceParts(const std::string& name)
{
  log_trace("CEditMap::{}({})", __func__, name);

  todo;
  return nullptr;
}

// 001B0D60
void CEditMap::GetePlaceIDList(sint* ids_dest, usize max_size)
{
  log_trace("CEditMap::{}({}, {})", __func__, fmt::ptr(ids_dest), max_size);

  todo;
}

// 001B0DD0
//matrix4 CEditMap::GetRotMatrix(sint angle) const
//{
//  log_trace("CEditMap::{}({})", __func__, angle);
//
//  todo;
//  return matrix4{ 1.0f };
//}

// 001B0EB0
sint CEditMap::GetEditAngle90(sint angle) const
{
  log_trace("CEditMap::{}({})", __func__, angle);

  angle = AngleLimit(angle);
  return (angle / (MAX_EDIT_ANGLE / 4)) * (MAX_EDIT_ANGLE * 4);
}

// 001B0F00
f32 CEditMap::GetEditAngle(sint angle) const
{
  log_trace("CEditMap::{}({})", __func__, angle);

  return mgAngleLimit(static_cast<f32>(angle % MAX_EDIT_ANGLE) * common::math::pi2() / static_cast<f32>(MAX_EDIT_ANGLE));
}

// 001B0F50
sint CEditMap::ConvEditAngle(f32 angle) const
{
  log_trace("CEditMap::{}({})", __func__, angle);

  if (angle < 0.0f)
  {
    angle += common::math::pi2();
  }

  sint edit_angle = static_cast<sint>(angle / (common::math::pi2() / MAX_EDIT_ANGLE));

  if (angle / (common::math::pi2() / MAX_EDIT_ANGLE) - static_cast<f32>(edit_angle) >= 0.5f)
  {
    edit_angle += 1;
  }

  return AngleLimit(edit_angle);
}

// 001B0FF0
sint CEditMap::AngleLimit(sint angle) const
{
  log_trace("CEditMap::{}({})", __func__, angle);

  angle &= MAX_EDIT_ANGLE;
  if (angle < 0)
  {
    angle += MAX_EDIT_ANGLE;
  }

  return angle;
}

// 001B1020
//vec3 CEditMap::GetEditPos(const vec3& pos) const
//{
//  log_trace("CEditMap::{}({})", __func__, fmt::ptr(&pos));
//
//  vec3 edit_pos{};
//
//  for (usize i = 0; i < 3; ++i)
//  {
//    f32 epsilon = (pos[i] >= 0.0f) ? 0.01f : -0.01f;
//    edit_pos[i] = truncf(pos[i] + epsilon);
//  }
//
//  return edit_pos;
//}

// 001B11D0
sint CEditMap::CmpEditAlt(f32 f1, f32 f2) const
{
  log_trace("CEditMap::{}({}, {})", __func__, f1, f2);

  f32 diff = f1 - f2;
  
  if (diff > 0.5f)
  {
    return -1;
  }

  if (diff < -0.5f)
  {
    return 1;
  }

  return 0;
}

// 001B1220
f32 CEditMap::GetEditAlt(f32 f) const
{
  log_trace("CEditMap::{}({})", __func__, f);

  f32 epsilon = (f > 0.0f) ? 0.5f : -0.5f;
  return truncf(f + epsilon);
}

// 001B1280
//bool CEditMap::GetGridPos(const vec3& v1, vec3& v2, vec3& v3) const
//{
//  log_trace("CEditMap::{}({}, {}, {})", __func__, fmt::ptr(&v1), fmt::ptr(&v2), fmt::ptr(&v3));
//
//  todo;
//  return false;
//}

// 001B1360
//matrix4 CEditMap::GetMatrix(const vec3& position, sint angle)
//{
//  log_trace("CEditMap::{}({}, {})", __func__, fmt::ptr(&position), angle);
//
//  todo;
//  return matrix4{ 1.0f };
//}

// 001B13B0
//matrix4 CEditMap::GetInverseMatrix(const matrix4& mat)
//{
//  log_trace("CEditMap::{}({})", __func__, fmt::ptr(&mat));
//
//  todo;
//  return matrix4{ 1.0f };
//}

// 001B13C0
usize CEditMap::ConvertParts(CEditParts* parts)
{
  log_trace("CEditMap::{}({})", __func__, fmt::ptr(parts));

  todo;
  return 0;
}

// 001B13F0
std::optional<usize> CEditMap::GetSameParts(ssize index)
{
  log_trace("CEditMap::{}({})", __func__, index);

  todo;
  return std::nullopt;
}

// 001B14A0
std::optional<usize> CEditMap::BuildEditParts(EEPartsInfoID id)
{
  log_trace("CEditMap::{}({})", __func__, common::to_underlying(id));

  auto parts_info = GetePartsInfoAtID(id);
  
  if (parts_info == nullptr)
  {
    return std::nullopt;
  }

  return BuildEditParts(parts_info->m_name);
}

// 001B14F0
usize CEditMap::GetTotalPolyn(sint* ip1, sint* ip2)
{
  log_trace("CEditMap::{}({}, {})", __func__, fmt::ptr(ip1), fmt::ptr(ip2));

  todo;
  return 0;
}

// 001B1630
std::optional<usize> CEditMap::BuildEditParts(const std::string& name)
{
  log_trace("CEditMap::{}({})", __func__, name);

  todo;
  return std::nullopt;
}

// 001B1820
bool CEditMap::DeleteEditParts(ssize index)
{
  log_trace("CEditMap::{}({})", __func__, index);

  auto edit_parts = GetePlaceParts(index);
  if (edit_parts == nullptr)
  {
    return false;
  }

  // Reconstruct the edit parts in place
  *edit_parts = {};

  return true;
}

// 001B18A0
//bool CEditMap::RemoveEditParts(sint i, const vec3& v, const RemoveInfo* remove_info)
//{
//  log_trace("CEditMap::{}({}, {}, {})", __func__, i, fmt::ptr(&v), fmt::ptr(remove_info));
//
//  todo;
//  return false;
//}

// 001B1C50
bool CEditMap::PlaceBurnParts()
{
  log_trace("CEditMap::{}()", __func__);

  todo;
  return false;
}

// 001B1CE0
bool CEditMap::BurnEditParts(const RemoveInfo* remove_info)
{
  log_trace("CEditMap::{}({})", __func__, fmt::ptr(remove_info));

  todo;
  return false;
}

// 001B1F50
//CEditParts* CEditMap::PlaceEditParts(const std::string& name, const vec3& position, const vec3& rotation)
//{
//  log_trace("CEditMap::{}({}, {}, {})", __func__, name, position, rotation);
//
//  auto index = BuildEditParts(name);
//  if (!index.has_value())
//  {
//    return nullptr;
//  }
//
//  auto parts = GetePlaceParts(index.value());
//  if (parts == nullptr)
//  {
//    return nullptr;
//  }
//
//  parts->SetPosition(position);
//  parts->SetRotation(rotation);
//  parts->SetScale(1.0f, 1.0f, 1.0f);
//}

// 001B2000
//CEditParts* CEditMap::PlaceEditParts(sint i, const EP_PLACE_INFO* place_info, const vec3& position, const vec3& rotation, sint* ip)
//{
//  log_trace("CEditMap::{}({}, {}, {}, {}, {})", __func__, i, fmt::ptr(place_info), fmt::ptr(&position), fmt::ptr(&rotation), fmt::ptr(ip));
//
//  todo;
//  return nullptr;
//}

// 001B21D0
//bool CEditMap::PlaceRiverParts(const vec3& position)
//{
//  log_trace("CEditMap::{}({})", __func__, fmt::ptr(&position));
//
//  todo;
//  return false;
//}

// 001B2220
bool CEditMap::CreatePlaceLog(sint i, const EP_PLACE_INFO* place_info)
{
  log_trace("CEditMap::{}({}, {})", __func__, i, fmt::ptr(place_info));

  todo;
  return false;
}

// 001B2320
//std::vector<std::shared_ptr<CEditParts>> CEditMap::GetNearParts(CEditPartsInfo* info, const vec3& position, f32 radius)
//{
//  log_trace("CEditMap::{}({}, {}, {})", __func__, fmt::ptr(info), fmt::ptr(&position), radius);
//
//  todo;
//  return std::vector<std::shared_ptr<CEditParts>>{};
//}

// 001B24D0
//std::vector<std::shared_ptr<CEditParts>> CEditMap::GetNearParts(const mgVu0FBOX& bounding_box)
//{
//  log_trace("CEditMap::{}({})", __func__, fmt::ptr(&bounding_box));
//
//  todo;
//  return std::vector<std::shared_ptr<CEditParts>>{};
//}

// 001B2670
//std::optional<usize> CEditMap::GetePlaceParts(const vec4& bounding_sphere)
//{
//  log_trace("CEditMap::{}({})", __func__, fmt::ptr(&bounding_sphere));
//
//  todo;
//  return std::nullopt;
//}

// 001B2740
//std::optional<usize> CEditMap::GetePlaceParts(const vec3& origin, const std::vector<std::shared_ptr<CEditParts>>& collection)
//{
//  log_trace("CEditMap::{}({}, {})", __func__, fmt::ptr(&origin), fmt::ptr(&collection));
//
//  todo;
//  return std::nullopt;
//}

// 001B2A50
//bool CEditMap::CheckEditParts(CEditPartsInfo* info, const vec3& position, f32 f, const EP_PLACE_INFO* place_info)
//{
//  log_trace("CEditMap::{}({}, {}, {}, {})", __func__, fmt::ptr(info), fmt::ptr(&position), f, fmt::ptr(place_info));
//
//  todo;
//  return false;
//}

// 001B2A50
//f32 CEditMap::GetEditPartsAlt(CEditPartsInfo* info, const vec3& position, f32 f, const EP_PLACE_INFO* place_info)
//{
//  log_trace("CEditMap::{}({}, {}, {}, {})", __func__, fmt::ptr(info), fmt::ptr(&position), f, fmt::ptr(place_info));
//
//  todo;
//  return 0.0f;
//}

// 001B2B50
//bool CEditMap::MagnetParts(CEditPartsInfo* info, const vec3& v1, const vec3& v2, const std::vector<std::shared_ptr<CEditParts>>& collection)
//{
//  log_trace("CEditMap::{}({}, {}, {}, {})", __func__, fmt::ptr(info), fmt::ptr(&v1), fmt::ptr(&v2), fmt::ptr(&collection));
//
//  todo;
//  return false;
//}

// 001B3A90
//bool CEditMap::MagnetParts(CEditPartsInfo* info, const vec3& v1, const vec3& v2)
//{
//  log_trace("CEditMap::{}({}, {}, {})", __func__, fmt::ptr(info), fmt::ptr(&v1), fmt::ptr(&v2));
//
//  todo;
//  return false;
//}

// 001B3B00
//bool CEditMap::CheckWallEditParts(CEditPartsInfo* info, const vec3& v1, sint i1, sint i2, const EP_PLACE_INFO* place_info)
//{
//  log_trace("CEditMap::{}({}, {}, {}, {}, {})", __func__, fmt::ptr(info), fmt::ptr(&v1), i1, i2, fmt::ptr(place_info));
//
//  todo;
//  return false;
//}

// 001B4AC0
void CEditMap::LoadEditInfo(char* script_buf, usize script_size)
{
  log_trace("CEditMap::{}({}, {})", __func__, fmt::ptr(script_buf), script_size);

  todo;
}

// 002967B0
//void CEditMap::PlaceRiver(const vec3& position)
//{
//  log_trace("CEditMap::{}({})", __func__, fmt::ptr(&position));
//
//  todo;
//}

// 00296840
//void CEditMap::RemoveRiver(const vec3& position)
//{
//  log_trace("CEditMap::{}({})", __func__, fmt::ptr(&position));
//
//  todo;
//}

// 002968D0
//void CEditMap::CreateGrid(const vec3& v1, const vec3& v2, const vec3& v3)
//{
//  log_trace("CEditMap::{}({}, {}, {})", __func__, fmt::ptr(&v1), fmt::ptr(&v2), fmt::ptr(&v3));
//
//  todo;
//}

// 00296B80
usize CEditMap::GetRiverNum(f32* fp)
{
  log_trace("CEditMap::{}({})", __func__, fmt::ptr(&fp));

  todo;
  return 0;
}

// 00296CE0
//bool CEditMap::IsRiverGrid(const vec3& position)
//{
//  log_trace("CEditMap::{}({})", __func__, fmt::ptr(&position));
//
//  todo;
//  return false;
//};

// 00296DA0
usize CEditMap::GetRiverNum(ssize index, f32 f)
{
  log_trace("CEditMap::{}({}, {})", __func__, index, f);

  todo;
  return 0;
}

// 00296E30
void CEditMap::DrawRiverMask()
{
  log_trace("CEditMap::{}()", __func__);

  todo;
}

// 00297350
void CEditMap::DrawRiver()
{
  log_trace("CEditMap::{}()", __func__);

  todo;
}

// 002A8B40
void CEditMap::SaveData(CEditData* data)
{
  log_trace("CEditMap::{}({})", __func__, fmt::ptr(data));

  todo;
}

// 002A9110
void CEditMap::LoadData(CEditData* data)
{
  log_trace("CEditMap::{}({})", __func__, fmt::ptr(data));

  todo;
}

// 002A9820
sint CEditMap::CultureAnalyzeParts(sint i1, sint i2)
{
  log_trace("CEditMap::{}({}, {})", __func__, i1, i2);

  todo;
  return 0;
}

// 002A9A20
sint CEditMap::CultureAnalyze(sint i)
{
  log_trace("CEditMap::{}({})", __func__, i);

  todo;
  return 0;
}

// 002A9AB0
std::pair<
  std::vector<std::shared_ptr<CMapParts>>,
  std::vector<std::shared_ptr<CMapPiece>>
> CEditMap::GetOnOffParts(const std::string& name)
{
  log_trace("CEditMap::{}({})", __func__, name);

  todo;
  return std::pair<
    std::vector<std::shared_ptr<CMapParts>>,
    std::vector<std::shared_ptr<CMapPiece>>
  >{};
}

// 002A9C60
void CEditMap::PartsOnOff(sint i, CEditData* data)
{
  log_trace("CEditMap::{}({}, {})", __func__, i, fmt::ptr(data));

  todo;
}

// 002ED720
//f32 CEditMap::GetEditPartsAlt(CEditPartsInfo* info, const vec3& position, f32 f, const std::vector<std::shared_ptr<CEditParts>>& collection)
//{
//  log_trace("CEditMap::{}({}, {}, {}, {})", __func__, fmt::ptr(info), fmt::ptr(&position), f, fmt::ptr(&collection));
//
//  todo;
//  return 0.0f;
//}

// 002ED990
//bool CEditMap::CheckEditParts(CEditPartsInfo* info, const vec3& position, f32 f, const EP_PLACE_INFO* place_info, const std::vector<std::shared_ptr<CEditParts>>& collection)
//{
//  log_trace("CEditMap::{}({}, {}, {}, {})", __func__, fmt::ptr(info), fmt::ptr(&position), f, fmt::ptr(place_info), fmt::ptr(&collection));
//
//  todo;
//  return false;
//}

// 002EDF60
//bool CEditMap::CheckEditPartsOnRiver(CEditPartsInfo* info, const vec3& position, f32 f)
//{
//  log_trace("CEditMap::{}({}, {}, {})", __func__, fmt::ptr(info), fmt::ptr(&position), f);
//
//  todo;
//  return false;
//}

// 002EE280
//bool CEditMap::CheckRiverParts(const vec3& position)
//{
//  log_trace("CEditMap::{}({})", __func__, fmt::ptr(&position));
//
//  todo;
//  return false;
//}

// 002EE5F0
bool CEditMap::CheckNormalPlaceParts(ssize index)
{
  log_trace("CEditMap::{}({})", __func__, index);

  todo;
  return false;
}

// 002EE620
bool CEditMap::CheckNormalPlaceParts(CEditParts* parts)
{
  log_trace("CEditMap::{}({})", __func__, fmt::ptr(parts));

  todo;
  return false;
}

// 002EE660
bool CEditMap::CheckLiveNPC(sint i1, sint i2)
{
  log_trace("CEditMap::{}({}, {})", __func__, i1, i2);

  todo;
  return false;
}

// 002EE770
usize CEditMap::GetePlacePartsAtInfoID(EEPartsInfoID id, sint* ip, sint i)
{
  log_trace("CEditMap::{}({}, {}, {})", __func__, common::to_underlying(id), fmt::ptr(ip), i);

  todo;
  return 0;
}

// 002EE920
usize CEditMap::GetTerritoryParts(sint i1, sint* ip, sint i2)
{
  log_trace("CEditMap::{}({}, {}, {})", __func__, i1, fmt::ptr(ip), i2);

  todo;
  return 0;
}

// 002EEA30
usize CEditMap::GetChildParts(sint i1, sint* ip, sint i2)
{
  log_trace("CEditMap::{}({}, {}, {})", __func__, i1, fmt::ptr(ip), i2);

  todo;
  return 0;
}

// 002EEAF0
sint CEditMap::RepaintNum(sint i)
{
  log_trace("CEditMap::{}({})", __func__, i);

  return i / 2;
}

// 002EEB10
//usize CEditMap::PaintFence(sint i1, const vec3& v, sint i2)
//{
//  log_trace("CEditMap::{}({}, {}, {})", __func__, i1, fmt::ptr(&v), i2);
//
//  todo;
//  return 0;
//}

// 002EEDE0
usize CEditMap::PaintFence(CEditParts* parts)
{
  log_trace("CEditMap::{}({})", __func__, fmt::ptr(parts));

  todo;
  return 0;
}

// 002EEEC0
void CEditMap::UpdateHouse()
{
  log_trace("CEditMap::{}()", __func__);

  todo;
}

// 002EF0B0
void CEditMap::GroundBalance(sint i)
{
  log_trace("CEditMap::{}({})", __func__, i);

  todo;
}

// 002EF480
bool CEditMap::BalanceCheck() const
{
  log_trace("CEditMap::{}()", __func__);

  todo;
  return false;
}