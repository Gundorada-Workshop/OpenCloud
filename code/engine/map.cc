#include "common/log.h"
#include "common/macros.h"

#include "engine/map.h"
#include "engine/scene.h"
#include "engine/script_interpreter.h"

set_log_channel("map");

// 00376E0C
static std::list<CMapPiece> mapNowMapPiece{};

// 00376E34
static usize mapMatIdx{};

// 00164520
static bool cfgDRAW_OFF_RECT(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

MAYBE_UNUSED static bool cfgOCCLUSION_PLANE(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool cfgFUNC_DATA(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool cfgFUNC_NAME(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool cfgFUNC_EVENT_DATA(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool cfgFUNC_DATA_END(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool cfgWATER_SURFACE_NUM(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool cfgWATER_SURFACE_START(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool cfgWATER_VERTEX(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool cfgWATER_POS(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool cfgWATER_PARAM(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool cfgWATER_SHAKE(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool cfgWATER_SURFACE_END(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool cfgWATER_DRAW_NUM(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool cfgWATER_DRAW(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapDummy(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapPARTS(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapFAR_CLIP(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapLIGHT_FLAG(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapMOVE_FLAG(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapLOD_START(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapLOD_BLEND(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapLOD_PIECE(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapLOD_END(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapPIECE(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapPIECE_POS(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapPIECE_NAME(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapPIECE_ROT(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapPIECE_SCALE(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapPIECE_MATERIAL_START(SPI_STACK* stack, MAYBE_UNUSED sint stack_count)
{
  trace_script_call(stack, stack_count);

  if (mapNowMapPiece.empty())
  {
    return false;
  }

  usize capacity = spiGetStackInt(stack++);
  if (capacity > 0)
  {
    mapNowMapPiece.front().SetMaterial(capacity);
  }

  return true;
}

static bool mapPIECE_MATERIAL(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapPIECE_MATERIAL_END(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapPIECE_COL_TYPE(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapPIECE_TIME(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapPIECE_END(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapPARTS_END(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

MAYBE_UNUSED static bool mapMAP_PARTS(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapMAP_FAR_CLIP(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapPARTS_NAME(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapPARTS_GROUP(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapPARTS_POS(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapPARTS_ROT(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapPARTS_SCALE(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

MAYBE_UNUSED static bool mapMAP_PARTS_END(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapMAP_INFO_TOP(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapCAMERA_INFO(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapFIX_CAMERA(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapFIX_CAMERA_POS(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapFIX_CAMERA_POS2(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapFIX_CAMERA_OFF_GROUP(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapFIX_CAMERA_RECT(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapFIX_CAMERA_END(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapCAMERA_INFO_END(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_POINT(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_DATA(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_NAME(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_FLAG(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_FIRE_DATA(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_EFFECT_NAME(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_PLIGHT_DATA(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_ANIME_DATA(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_INVENT_DATA(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_EVENT_DATA(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_POS(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_DATA_END(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_POINT_END(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool mapFUNC_SOUND_DATA(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

// 00334730
static const std::array<SPI_TAG_PARAM, 88> map_tag =
{
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "d",                      mapDummy,
  "PARTS",                  mapPARTS,
  "FAR_CLIP",               mapFAR_CLIP,
  "LIGHT_FLAG",             mapLIGHT_FLAG,
  "MOVE_FLAG",              mapMOVE_FLAG,
  "LOD_START",              mapLOD_START,
  "LOD_BLEND",              mapLOD_BLEND,
  "LOD_PIECE",              mapLOD_PIECE,
  "LOD_END",                mapLOD_END,
  "PIECE",                  mapPIECE,
  "PIECE_POS",              mapPIECE_POS,
  "PIECE_NAME",             mapPIECE_NAME,
  "PIECE_ROT",              mapPIECE_ROT,
  "PIECE_SCALE",            mapPIECE_SCALE,
  "PIECE_MATERIAL_START",   mapPIECE_MATERIAL_START,
  "MAP_PIECE_MATERIAL",     mapPIECE_MATERIAL,
  "MAP_PIECE_MATERIAL_END", mapPIECE_MATERIAL_END,
  "PIECE_COL_TYPE",         mapPIECE_COL_TYPE,
  "PIECE_TIME",             mapPIECE_TIME,
  "PIECE_END",              mapPIECE_END,
  "PARTS_END",              mapPARTS_END,
  "MAP_PARTS",              mapPARTS,
  "MAP_FAR_CLIP",           mapMAP_FAR_CLIP,
  "PARTS_NAME",             mapPARTS_NAME,
  "PARTS_GROUP",            mapPARTS_GROUP,
  "PARTS_POS",              mapPARTS_POS,
  "PARTS_ROT",              mapPARTS_ROT,
  "PARTS_SCALE",            mapPARTS_SCALE,
  "MAP_PARTS_END",          mapPARTS_END,
  "_MAP_INFO_TOP",          mapMAP_INFO_TOP,
  "CAMERA_INFO",            mapCAMERA_INFO,
  "FIX_CAMERA",             mapFIX_CAMERA,
  "FIX_CAMERA_POS",         mapFIX_CAMERA_POS,
  "FIX_CAMERA_POS2",        mapFIX_CAMERA_POS2,
  "FIX_CAMERA_OFF_GROUP",   mapFIX_CAMERA_OFF_GROUP,
  "FIX_CAMERA_RECT",        mapFIX_CAMERA_RECT,
  "FIX_CAMERA_END",         mapFIX_CAMERA_END,
  "CAMERA_INFO_END",        mapCAMERA_INFO_END,
  "FUNC_POINT",             mapFUNC_POINT,
  "FUNC_DATA",              mapFUNC_DATA,
  "FUNC_NAME",              mapFUNC_NAME,
  "FUNC_FLAG",              mapFUNC_FLAG,
  "FUNC_FIRE_DATA",         mapFUNC_FIRE_DATA,
  "FUNC_EFFECT_NAME",       mapFUNC_EFFECT_NAME,
  "FUNC_FIRE_DATA",         mapFUNC_EFFECT_NAME,
  "FUNC_PLIGHT_DATA",       mapFUNC_PLIGHT_DATA,
  "FUNC_ANIME_DATA",        mapFUNC_ANIME_DATA,
  "FUNC_INVENT_DATA",       mapFUNC_INVENT_DATA,
  "FUNC_EVENT_DATA",        mapFUNC_EVENT_DATA,
  "FUNC_POS",               mapFUNC_POS,
  "FUNC_DATA_END",          mapFUNC_DATA_END,
  "FUNC_POINT_END",         mapFUNC_POINT_END,
  "FUNC_SOUND_DATA",        mapFUNC_SOUND_DATA,
  NULL, nullptr
};

// 003349f0
static const std::array<SPI_TAG_PARAM, 16> cfg_tag =
{
  "DRAW_OFF_RECT",       cfgDRAW_OFF_RECT,
  "FUNC_DATA",           cfgFUNC_DATA,
  "FUNC_NAME",           cfgFUNC_NAME,
  "FUNC_EVENT_DATA",     cfgFUNC_EVENT_DATA,
  "FUNC_POS",            mapFUNC_POS,
  "FUNC_DATA",           cfgFUNC_DATA_END,
  "WATER_SURFACE_NUM",   cfgWATER_SURFACE_NUM,
  "WATER_SURFACE_START", cfgWATER_SURFACE_START,
  "WATER_VERTEX",        cfgWATER_VERTEX,
  "WATER_POS",           cfgWATER_POS,
  "WATER_PARAM",         cfgWATER_PARAM,
  "WATER_SHAKE",         cfgWATER_SHAKE,
  "WATER_SURFACE_END",   cfgWATER_SURFACE_END,
  "WATER_DRAW_NUM",      cfgWATER_DRAW_NUM,
  "WATER_DRAW",          cfgWATER_DRAW,
  NULL, nullptr,
};

// 00376e04
static CMap* _mapMap{ nullptr };
// 00376e10
static mgCMemory* _mapStack{ nullptr };

// 00376E40
void CMap::LoadCfgFile(char* file, int size, mgCMemory* map_stack)
{
  CScriptInterpreter interpreter{ };

  // _ReserveFuncFlag = 0;
  // _WaterIndex = 0;
  // _cfgWater = 0;
  _mapMap = this;
  _mapStack = map_stack;

  interpreter.SetTag(cfg_tag.data());
  interpreter.SetScript(file, size);
  interpreter.Run();
}

static bool amapIMG(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

static bool amapPCP(MAYBE_UNUSED SPI_STACK* stack, int)
{
  return true;
}

// 00334a80
static const std::array<SPI_TAG_PARAM, 3> add_mapinfo_tag =
{
  "IMG", amapIMG,
  "PCP", amapPCP,
  NULL, nullptr
};

// 00168AC0
CMapPiece::CMapPiece()
{
  log_trace("CMap::{}()", __func__);

  todo;
}

// 00168850
CMapPiece::CMapPiece(MAYBE_UNUSED const CMapPiece& other)
{
  log_trace("CMapPiece::{}({})", __func__, fmt::ptr(&other));

  todo;
}

// 00166E40
unkptr CMapPiece::Draw()
{
  log_trace("CMapPiece::{}()", __func__);

  return DrawSub(false);
}

// 0015E3E0
unkptr CMapPiece::DrawDirect()
{
  log_trace("CMapPiece::{}()", __func__);

  return DrawSub(true);
}

// 00162750
void CMapPiece::SetMaterial(usize capacity)
{
  log_trace("CMapPiece::{}({})", __func__, capacity);

  m_material.clear();
  m_material.reserve(capacity);

  for (usize i = 0; i < capacity; ++i)
  {
    m_material.emplace_back();
  }
}

// 00168520
void CMapPiece::AssignMds(MAYBE_UNUSED CMdsInfo* mds_info)
{
  log_trace("CMapPiece::{}({})", __func__, fmt::ptr(mds_info));

  todo;
}

// 00168570
//sint CMapPiece::GetPoly(sint i1, CCPoly* dest, mgVu0FBOX& box, sint i2)
//{
//  log_trace("CMapPiece::{}({}, {}, {}, {})", __func__, i1, fmt::ptr(dest), fmt::ptr(&box), i2);
//
//  todo;
//  return 0;
//}

// 00168620
void CMapPiece::SetTimeBand(f32 f1, f32 f2)
{
  log_trace("CMapPiece::{}({}, {})", __func__, f1, f2);

  m_unk_field_94 = f1;
  m_unk_field_98 = f2;
}

// 00168630
PieceMaterial* CMapPiece::GetMaterial(ssize index)
{
  log_trace("CMapPiece::{}({})", __func__, index);

  if (index < 0 || index > static_cast<ssize>(m_material.size()))
  {
    return nullptr;
  }

  return &m_material[index];
}

// 00168680
void CMapPiece::Step()
{
  log_trace("CMapPiece::{}()", __func__);

  if (m_unk_field_9C == nullptr)
  {
    return;
  }

  UpdatePosition();
  m_unk_field_9C->Step();
}

// 001686D0
// std::optional<mgVu0FBOX> CMapPiece::GetBoundBox()
//{
//  log_trace("CMapPiece::{}()", __func__);
//
//  if (m_frame == nullptr)
//  {
//    return std::nullopt;
//  }
//
//  UpdatePosition();
//  return m_frame->GetWorldBBox();
//}

// 00168730
unkptr CMapPiece::DrawSub(MAYBE_UNUSED bool b)
{
  log_trace("CMapPiece::{}({})", __func__, b);

  todo;
  return nullptr;
}

// 0015CB30 / 00166250
CMapParts::CMapParts()
{
  log_trace("CMapParts::{}()", __func__);

  todo;
}

// 00167AA0
CMapParts::CMapParts(MAYBE_UNUSED const CMapParts& other)
{
  log_trace("CMapParts::{}({})", __func__, fmt::ptr(&other));

  todo;
}

// 0015E3D0
unkptr CMapParts::Draw()
{
  log_trace("CMapParts::{}()", __func__);

  return DrawSub(false);
}

// 0015E3E0
unkptr CMapParts::DrawDirect()
{
  log_trace("CMapParts::{}()", __func__);

  return DrawSub(true);
}

// 00166A00
bool CMapParts::PreDraw()
{
  log_trace("CMapParts::{}()", __func__);

  if (!CObject::PreDraw())
  {
    return false;
  }

  UpdatePosition();

  MAYBE_UNUSED f32 alpha_result;
  return 0.0f;
  //return FarClip(mgGetDistFromCamera(m_position), &alpha_result);
}

// 00166E50
void CMapParts::DrawStep()
{
  log_trace("CMapParts::{}()", __func__);

  UpdatePosition();
  CObject::DrawStep();

  for (auto& map_piece : m_map_pieces)
  {
    map_piece.UpdatePosition();
    map_piece.DrawStep();
  }
}

// 001678E0
void CMapParts::Step()
{
  log_trace("CMapParts::{}()", __func__);

  if (!m_active)
  {
    return;
  }

  for (auto& map_piece : m_map_pieces)
  {
    map_piece.m_frame->SetReference(m_unk_field_C0);
    map_piece.Step();
    map_piece.m_frame->DeleteReference();
  }
}

// 00167970
void CMapParts::AnimeStep(MAYBE_UNUSED CFuncPointCheck* point_check, MAYBE_UNUSED CObjAnimeEnv* anime_env)
{
  log_trace("CMapParts::{}()", __func__);

  todo;
}

// 001666F0
void CMapParts::UpdatePosition()
{
  log_trace("CMapParts::{}()", __func__);

  if (!m_unk_field_40)
  {
    return;
  }

  //m_unk_field_C0.SetPosition(m_position);
  //m_unk_field_C0.SetRotation(m_rotation);
  //m_unk_field_C0.SetScale(m_scale);
  m_unk_field_40 = false;
}

// 00162080
void CMapParts::SetLODDist(const std::vector<f32>& lods)
{
  log_trace("CMapParts::{}({})", __func__, fmt::ptr(&lods));

  m_lod_dist.clear();
  m_lod_dist.reserve(lods.size());
  std::copy(lods.begin(), lods.end(), std::back_inserter(m_lod_dist));
}

// 001620F0
void CMapParts::SetLODBlend(bool flag)
{
  log_trace("CMapParts::{}({})", __func__, flag);

  m_lod_blend = flag;
}

// 001621B0
bool CMapParts::GetLODBlend() const
{
  log_trace("CMapParts::{}()", __func__);

  return m_lod_blend;
}

// 00166360
void CMapParts::SetName(const std::string& name)
{
  log_trace("CMapParts::{}({})", __func__, name);

  m_name = name;
};

// 001663C0
void CMapParts::SetPartsName(const std::string& name)
{
  log_trace("CMapParts::{}({})", __func__, name);

  m_parts_name = name;
}

// 00166420
void CMapParts::AddPiece(std::list<CMapPiece>& pieces)
{
  // Used by script interpreter functions - adds one existing CMapPiece object to this CMapParts

  log_trace("CMapParts::{}({})", __func__, fmt::ptr(&pieces));

  CMapPiece* piece = &pieces.front();
  if ((piece->m_unk_field_84 & 4) != 0)
  {
    m_active = true;
  }

  // Only grab one piece (script stores list of one piece in mapNowMapPiece?)
  // Unlike the original code, this invalidates the element at mapNowMapPiece,
  // however this function is only called in mapPIECE_END, so it should be at end of life anyways
  auto end = pieces.begin();
  std::advance(end, 1);

  m_map_pieces.splice(m_map_pieces.end(), pieces, pieces.begin(), end);
}

// 00166490
CMapPiece* CMapParts::SearchPiece(const std::string& name)
{
  log_trace("CMapParts::{}({})", __func__, name);

  for (auto& map_pieces : m_map_pieces)
  {
    if (map_pieces.m_name == name)
    {
      return &map_pieces;
    }
  }

  return nullptr;
}

// 00166520
CMapPiece* CMapParts::SearchPieceColType(sint col_type)
{
  log_trace("CMapParts::{}({})", __func__, col_type);

  for (auto& map_pieces : m_map_pieces)
  {
    if (map_pieces.m_col_type == col_type)
    {
      return &map_pieces;
    }
  }

  return nullptr;
}

// 00166580
//sint CMapParts::GetPoly(sint i1, CCPoly* dest, mgVu0FBOX& box, sint i2)
//{
//  log_trace("CMapParts::{}({}, {}, {}, {})", __func__, i1, fmt::ptr(dest), fmt::ptr(&box), i2);
//
//  todo;
//  return 0;
//}

// 001666B0
//sint CMapParts::GetColPoly(CCPoly* dest, mgVu0FBOX& box, sint i2)
//{
//  log_trace("CMapParts::{}({}, {}, {})", __func__, fmt::ptr(dest), fmt::ptr(&box), i2);
//
//  return GetPoly(1, dest, box, i2);
//}

// 001666D0
//sint CMapParts::GetCameraPoly(CCPoly* dest, mgVu0FBOX& box, sint i2)
//{
//  log_trace("CMapParts::{}({}, {}, {})", __func__, fmt::ptr(dest), fmt::ptr(&box), i2);
//
//  return GetPoly(3, dest, box, i2);
//}

// 00166760
//bool CMapParts::SetColor(ssize index, const vec4& rgba)
//{
//  log_trace("CMapParts::{}({}, {})", __func__, index, fmt::ptr(&rgba));
//
//  if (index < 0 || index >= m_color.size())
//  {
//    return false;
//  }
//
//  m_color[index] = rgba;
//  return true;
//}

// 001667B0
//std::optional<vec4> CMapParts::GetColor(ssize index) const
//{
//  log_trace("CMapParts::{}({})", __func__, index);
//
//  if (index < 0 || index >= m_color.size())
//  {
//    return std::nullopt;
//  }
//
//  return m_color[index];
//}

// 001667F0
//std::optional<vec4> CMapParts::GetDefColor(ssize index)
//{
//  log_trace("CMapParts::{}({})", __func__, index);
//
//  if (index < 0 || index >= m_color.size())
//  {
//    return std::nullopt;
//  }
//
//  for (auto& map_piece : m_map_pieces)
//  {
//    for (usize i = 0; i < map_piece.m_material.size(); ++i)
//    {
//      PieceMaterial* piece_material = map_piece.GetMaterial(i);
//
//      if (piece_material->m_unk_field_8 && piece_material->m_color_idx == index)
//      {
//        return piece_material->m_color;
//      }
//    }
//  }
//
//  return std::nullopt;
//}

// 001668E0
//void CMapParts::UpdateColor()
//{
//  log_trace("CMapParts::{}()", __func__);
//
//  for (usize i = 0; i < m_color.size(); ++i)
//  {
//    auto& rgba = m_color[i];
//    if (rgba.a <= 0.0f)
//    {
//      continue;
//    }
//
//    for (auto& map_piece : m_map_pieces)
//    {
//      for (usize j = 0; j < map_piece.m_material.size(); ++j)
//      {
//        auto piece_material = map_piece.GetMaterial(j);
//        if (piece_material->m_unk_field_8 && piece_material->m_color_idx == i)
//        {
//          rgba = vec4{ piece_material->m_color.rgb, rgba.a };
//        }
//      }
//    }
//  }
//}

// 00166A70
unkptr CMapParts::DrawSub(MAYBE_UNUSED bool b)
{
  log_trace("CMapParts::{}({})", __func__, b);

  todo;
  return nullptr;
}

// 00166ED0
void CMapParts::CreateBoundBox()
{
  log_trace("CMapParts::{}()", __func__);

  todo;
}

// 00167090
//bool CMapParts::CheckColBox(mgVu0FBOX* box) const
//{
//  log_trace("CMapParts::{}({})", __func__, fmt::ptr(box));
//
//  todo;
//  return false;
//}

// 001671D0
//std::optional<mgVu0FBOX> CMapParts::GetBBox() const
//{
//  log_trace("CMapParts::{}()", __func__);
//
//  if (m_bounding_box_valid)
//  {
//    return m_bounding_box;
//  }
//  else
//  {
//    return std::nullopt;
//  }
//}

// 00167220
//std::optional<mgVu0FBOX> CMapParts::GetBoundBox()
//{
//  log_trace("CMapParts::{}()", __func__);
//
//  if (m_bounding_box_valid)
//  {
//    mgVu0FBOX result;
//    matrix4 lw_mat = GetLWMatrix();
//
//    mgApplyMatrix(result.corners[0], result.corners[1], lw_mat, m_bounding_box.corners[0], m_bounding_box.corners[1]);
//    return result;
//  }
//  else
//  {
//    return std::nullopt;
//  }
//}

// 00167280
//std::optional<vec4> CMapParts::GetBoundSphere()
//{
//  log_trace("CMapParts::{}()", __func__);
//
//  if (m_bounding_box_valid)
//  {
//    matrix4 lw_mat = GetLWMatrix();
//
//    vec4 result = lw_mat * m_bounding_sphere;
//    result.w = m_bounding_sphere.w;
//    return result;
//  }
//  else
//  {
//    return std::nullopt;
//  }
//}

// 00167300
//matrix4 CMapParts::GetLWMatrix()
//{
//  log_trace("CMapParts::{}()", __func__);
//
//  UpdatePosition();
//  return m_unk_field_C0.GetLWMatrix();
//}

// 00167350
bool CMapParts::InsideScreen() const
{
  log_trace("CMapParts::{}()", __func__);

  todo;
  return false;
}

// 001673A0
bool CMapParts::InsideScreen(MAYBE_UNUSED const std::vector<COcclusion>& occlusion, MAYBE_UNUSED sint i) const
{
  log_trace("CMapParts::{}({}, {})", __func__, fmt::ptr(&occlusion), i);

  todo;
  return false;
}

// 001674B0
void CMapParts::InScreenFunc(MAYBE_UNUSED InScreenFuncInfo* func_info)
{
  log_trace("CMapParts::{}({})", __func__, fmt::ptr(func_info));

  todo;
}

// 00167730
void CMapParts::DrawScreenFunc(MAYBE_UNUSED mgCFrame* frame)
{
  log_trace("CMapParts::{}({})", __func__, fmt::ptr(frame));

  todo;
}

// 001679F0
void CMapParts::StepFuncPoint(MAYBE_UNUSED CFuncPointCheck& point_check)
{
  log_trace("CMapParts::{}({})", __func__, fmt::ptr(&point_check));

  todo;
}

// 00167A60
void CMapParts::CopyFuncPointCheck(MAYBE_UNUSED CFuncPointCheck& other)
{
  log_trace("CMapParts::{}({})", __func__, fmt::ptr(&other));

  todo;
}

// 00168150
bool CMapParts::AssignFuncAnime()
{
  log_trace("CMapParts::{}()", __func__);

  todo;
  return false;
}

// 0015E250
unkptr CMap::DrawSub(MAYBE_UNUSED bool b)
{
  log_trace("CMap::{}({})", __func__, b);

  todo;
  return nullptr;
}

// 00160B10
unkptr CMap::Draw()
{
  log_trace("CMap::{}()", __func__);

  return DrawSub(false);
}

// 00160B30
unkptr CMap::DrawDirect()
{
  log_trace("CMap::{}()", __func__);

  return DrawSub(true);
}

// 0015D7A0
//bool CMap::PreDraw(const vec3& v)
//{
//  log_trace("CMap::{}({})", __func__, fmt::ptr(&v));
//
//  todo;
//  return false;
//}

// 0015E3F0
void CMap::DrawEffect()
{
  log_trace("CMap::{}()", __func__);

  todo;
}

// 0015E5D0
void CMap::DrawFireEffect(MAYBE_UNUSED sint texture_id)
{
  log_trace("CMap::{}({})", __func__, texture_id);

  todo;
}

// 0015E720
void CMap::DrawFireRaster()
{
  log_trace("CMap::{}()", __func__);

  todo;
}

// 0015E800
void CMap::DrawWater(MAYBE_UNUSED mgCCamera* camera, MAYBE_UNUSED mgCTexture* tex1, MAYBE_UNUSED mgCTexture* tex2)
{
  log_trace("CMap::{}({}, {}, {})", __func__, fmt::ptr(camera), fmt::ptr(tex1), fmt::ptr(tex2));

  todo;
}

// 0015F120
//sint CMap::GetPoly(sint i1, CCPoly* dest, mgVu0FBOX& box, sint i2)
//{
//  log_trace("CMap::{}({}, {}, {}, {})", __func__, i1, fmt::ptr(dest), fmt::ptr(&box), i2);
//
//  todo;
//  return 0;
//}

// 0015F260
//sint CMap::GetColPoly(CCPoly* dest, mgVu0FBOX& box, sint i2)
//{
//  log_trace("CMap::{}({}, {}, {})", __func__, fmt::ptr(dest), fmt::ptr(&box), i2);
//
//  return GetPoly(1, dest, box, i2);
//}

// 0015F290
//sint CMap::GetCameraPoly(CCPoly* dest, mgVu0FBOX& box, sint i2)
//{
//  log_trace("CMap::{}({}, {}, {})", __func__, fmt::ptr(dest), fmt::ptr(&box), i2);
//
//  return GetPoly(3, dest, box, i2);
//}

// 0015F880
//void CMap::GetEvent(const vec3* v, sint i, MapEventInfo* dest)
//{
//  log_trace("CMap::{}({}, {}, {})", __func__, fmt::ptr(v), i, fmt::ptr(dest));
//
//  todo;
//}

// 0015FC00
void CMap::InScreenFunc(MAYBE_UNUSED InScreenFuncInfo* func_info)
{
  log_trace("CMap::{}({})", __func__, fmt::ptr(func_info));

  todo;
}

// 0015FD00
void CMap::DrawScreenFunc(MAYBE_UNUSED mgCFrame* frame)
{
  log_trace("CMap::{}({})", __func__, fmt::ptr(frame));

  todo;
}

// 0015FF60
void CMap::GetSeSrcVolPan(MAYBE_UNUSED sint* ip, MAYBE_UNUSED f32* fp1_dest, MAYBE_UNUSED f32* fp2_dest, MAYBE_UNUSED sint i)
{
  log_trace("CMap::{}({}, {}, {}, {})", __func__, fmt::ptr(ip), fmt::ptr(fp1_dest), fmt::ptr(fp2_dest), i);

  todo;
}

// 0015FDF0
void CMap::AnimeStep(MAYBE_UNUSED CObjAnimeEnv* env)
{
  log_trace("CMap::{}({})", __func__, fmt::ptr(env));

  todo;
}

// 0015FEF0
void CMap::Step()
{
  log_trace("CMap::{}()", __func__);

  todo;
}

// 0015C510
std::string CMap::Iam() const
{
  log_trace("CMap::{}()", __func__);

  return CMapName;
}

// 0015C600
CPartsGroup* CMap::GetPartsGroup(ssize index)
{
  log_trace("CMap::{}({})", __func__, index);

  if (index < 0 || index >= static_cast<ssize>(m_parts_group_buf.size()))
  {
    return nullptr;
  }

  return &m_parts_group_buf[index];
}

// 0015C640
ssize CMap::AddPartsGroup(MAYBE_UNUSED const std::string& group_name, MAYBE_UNUSED CMapParts* parts)
{
  log_trace("CMap::{}({}, {})", __func__, group_name, fmt::ptr(parts));

  todo;
  return 0;
}

// 0015C750
CPartsGroup* CMap::SearchPartsGroup(MAYBE_UNUSED const std::string& group_name)
{
  log_trace("CMap::{}({})", __func__, group_name);

  todo;
  return nullptr;
}

// 0015C780
ssize CMap::SearchPartsGroupNo(MAYBE_UNUSED const std::string& group_name)
{
  log_trace("CMap::{}({})", __func__, group_name);

  todo;
  return 0;
}

// 0015C820
ssize CMap::SearchEmptyPartsGroupNo()
{
  log_trace("CMap::{}()", __func__);

  todo;
  return 0;
}

// 0015CA30
void CMap::SetPlacePartsBuff(MAYBE_UNUSED usize capacity)
{
  log_trace("CMap::{}({})", __func__, capacity);

  todo;
}

// 0015CBD0
std::vector<CMapParts>& CMap::GetPlacePartsTable()
{
  log_trace("CMap::{}()", __func__);

  return m_map_place_parts;
}

// 0015CBE0
void CMap::SetCameraInfoTable(MAYBE_UNUSED usize capacity)
{
  log_trace("CMap::{}({})", __func__, capacity);

  todo;
}

// 0015CBF0
CCameraInfo* CMap::GetCameraInfo(MAYBE_UNUSED ssize index)
{
  log_trace("CMap::{}({})", __func__, index);

  todo;
  return nullptr;
}

// 0015CC40
CMapParts* CMap::NewPlaceParts()
{
  log_trace("CMap::{}()", __func__);

  todo;
  return nullptr;
}

// 0015CCB0
CMdsInfo* CMap::SearchMDS(MAYBE_UNUSED const std::string& mds_name)
{
  log_trace("CMap::{}({})", __func__, mds_name);

  todo;
  return nullptr;
}

// 0015CCE0
void CMap::CreateEffect(MAYBE_UNUSED uint* p, MAYBE_UNUSED sint i)
{
  log_trace("CMap::{}({}, {})", __func__, fmt::ptr(p), i);

  todo;
}

// 0015CD00
ssize CMap::SearchEffectIndex(MAYBE_UNUSED const std::string& effect_name)
{
  log_trace("CMap::{}({})", __func__, effect_name);

  todo;
  return 0;
}

// 0015CD10
void CMap::AddParts(MAYBE_UNUSED std::list<CMapParts>& parts)
{
  log_trace("CMap::{}({})", __func__, fmt::ptr(&parts));

  todo;
}

// 0015CD60
CMapParts* CMap::GetParts(MAYBE_UNUSED const std::string& parts_name)
{
  log_trace("CMap::{}({})", __func__, parts_name);

  todo;
  return nullptr;
}

// 0015CE00
//void CMap::CreateDrawRect(mgVu0FBOX* box1, mgVu0FBOX* box2, sint i)
//{
//  log_trace("CMap::{}({}, {}, {})", __func__, fmt::ptr(box1), fmt::ptr(box2), i);
//
//  todo;
//}

// 0015CFD0
//void CMap::CreateOcclusion(const matrix4* m)
//{
//  log_trace("CMap::{}({})", __func__, fmt::ptr(m));
//
//  todo;
//}

// 0015D080
//void CMap::PlaceParts(const std::string& parts_name, const vec3& position, const vec3& rotation, const vec3& scale)
//{
//  log_trace("CMap::{}({}, {}, {}, {})", __func__, parts_name, fmt::ptr(&position), fmt::ptr(&rotation), fmt::ptr(&scale));
//
//  todo;
//}

// 0015D170
void CMap::PlacePartsEnd()
{
  log_trace("CMap::{}()", __func__);

  todo;
}

// 0015D350
void CMap::ClearPlaceParts()
{
  log_trace("CMap::{}()", __func__);

  todo;
}

// 0015D420
CMapParts* CMap::GetPlaceParts(MAYBE_UNUSED const std::string& parts_name)
{
  log_trace("CMap::{}({})", __func__, parts_name);

  todo;
  return nullptr;
}

// 0015D4C0
CMapParts* CMap::GetPlaceParts(MAYBE_UNUSED ssize parts_index)
{
  log_trace("CMap::{}({})", __func__, parts_index);

  todo;
  return nullptr;
}

// 0015D510
ssize CMap::ConvertParts(MAYBE_UNUSED CMapParts* parts)
{
  log_trace("CMap::{}({})", __func__, fmt::ptr(parts));

  todo;
  return 0;
}

// 0015D550
//void CMap::GetPlaceParts(mgVu0FBOX* region, std::vector<CMapParts>& parts_dest, usize max_capacity)
//{
//  log_trace("CMap::{}({}, {}, {})", __func__, fmt::ptr(region), fmt::ptr(&parts_dest), max_capacity);
//
//  todo;
//}

// 0015D550
//void CMap::GetPlaceColParts(mgVu0FBOX* region, std::vector<CMapParts>& parts_dest, usize max_capacity)
//{
//  log_trace("CMap::{}({}, {}, {})", __func__, fmt::ptr(region), fmt::ptr(&parts_dest), max_capacity);
//
//  todo;
//}

// 0015D730
void CMap::CreateFuncCheck(MAYBE_UNUSED CFuncPointCheck* point_check)
{
  log_trace("CMap::{}({})", __func__, fmt::ptr(point_check));

  todo;
}

// 0015D770
//std::optional<mgVu0FBOX> CMap::GetBBox() const
//{
//  log_trace("CMap::{}()", __func__);
//
//  if (m_bounding_box_valid)
//  {
//    return m_bounding_box;
//  }
//  return std::nullopt;
//}

// 0015DBE0
usize CMap::GetCharaLight(MAYBE_UNUSED mgCObject* object, MAYBE_UNUSED CFuncPoint* func_point, MAYBE_UNUSED sint i1, MAYBE_UNUSED sint i2)
{
  log_trace("CMap::{}()", __func__);

  todo;
  return 0;
}

// 0015E0B0
//void CMap::SetFuncPLight(const vec4& v, CFuncPointCheck* point_check)
//{
//  log_trace("CMap::{}({}, {})", __func__, fmt::ptr(&v), fmt::ptr(point_check));
//
//  todo;
//}

// 0015E1F0
void CMap::ResetFuncPLight(MAYBE_UNUSED ssize light_index)
{
  log_trace("CMap::{}({})", __func__, light_index);

  todo;
}

// 0015EF70
void CMap::DrawTrBox()
{
  log_trace("CMap::{}()", __func__);

  todo;
}

// 0015F110
bool CMap::GetShow() const
{
  log_trace("CMap::{}()", __func__);

  todo;
  return false;
}

// 0015F2C0
//sint CMap::GetTrBoxColPoly(CCPoly* dest, mgVu0FBOX& box, sint i2)
//{
//  log_trace("CMap::{}({}, {}, {})", __func__, fmt::ptr(dest), fmt::ptr(&box), i2);
//
//  todo;
//  return 0;
//}

// 0015F3D0
//sint CMap::GetFixCameraPos(const vec3& v1, vec3& v2)
//{
//  log_trace("CMap::{}({}, {})", __func__, fmt::ptr(&v1), fmt::ptr(&v2));
//
//  todo;
//  return 0;
//}

// 0015F730
//void CMap::FixCameraPartsOnOff(const vec3& v)
//{
//  log_trace("CMap::{}({})", __func__, fmt::ptr(&v));
//
//  todo;
//}

// 0015F880
//CMapParts* CMap::GetEvent(const vec3& v, sint i, MapEventInfo* event_info)
//{
//  log_trace("CMap::{}({}, {}, {})", __func__, fmt::ptr(&v), i, fmt::ptr(event_info));
//
//  todo;
//  return nullptr;
//}

// 0015FDA0
void CMap::EffectStep()
{
  log_trace("CMap::{}()", __func__);

  todo;
}

// 001600D0
void CMap::CreateMap(MAYBE_UNUSED CMdsListSet* mds_list)
{
  log_trace("CMap::{}({})", __func__, fmt::ptr(mds_list));

  todo;
}

// 00160150
void CMap::AssignFuncPoint()
{
  log_trace("CMap::{}()", __func__);

  todo;
}

// 001602C0
void CMap::CreateTrBox(MAYBE_UNUSED CMapTreasureBox* treasure_box, MAYBE_UNUSED sint i)
{
  log_trace("CMap::{}({}, {})", __func__, fmt::ptr(treasure_box), i);

  todo;
}

// 00160620
CMapTreasureBox* CMap::GetTrBox(MAYBE_UNUSED ssize index)
{
  log_trace("CMap::{}({})", __func__, index);

  todo;
  return nullptr;
}

// 00160670
void CMap::DeleteTrBox(MAYBE_UNUSED ssize index, MAYBE_UNUSED CMapFlagData* flag_data)
{
  log_trace("CMap::{}({}, {})", __func__, index, fmt::ptr(flag_data));

  todo;
}

// 001606E0
void CMap::UpdateTrBoxFlag(MAYBE_UNUSED CMapFlagData* flag_data) const
{
  log_trace("CMap::{}({})", __func__, fmt::ptr(flag_data));

  todo;
}

// 00160780
void CMap::LoadData(MAYBE_UNUSED uint* p1, MAYBE_UNUSED uint* p2, MAYBE_UNUSED sint* p3)
{
  log_trace("CMap::{}({}, {}, {})", __func__, fmt::ptr(p1), fmt::ptr(p2), fmt::ptr(p3));

  todo;
}

// 00160D30
f32 CMap::GetNowTime() const
{
  log_trace("CMap::{}()", __func__);

  todo;
  return 0.0f;
}

// 00160D70
ETimeBand CMap::GetNowTimeBand() const
{
  log_trace("CMap::{}()", __func__);

  todo;
  return ETimeBand::Night;
}

// 00160DA0
ETimeBand CMap::GetNowTimeLightBand() const
{
  log_trace("CMap::{}()", __func__);

  todo;
  return ETimeBand::Night;
}

// 00160E70
//void CMap::GetLightingRatio(vec4& ratio_dest) const
//{
//  log_trace("CMap::{}({})", __func__, fmt::ptr(&ratio_dest));
//
//  todo;
//}

// 00160FE0
//void CMap::GetLightingFlareRatio(vec4& ratio_dest) const
//{
//  log_trace("CMap::{}({})", __func__, fmt::ptr(&ratio_dest));
//
//  todo;
//}

// 00161010
//void CMap::GetLightingSunRatio(vec4& ratio_dest) const
//{
//  log_trace("CMap::{}({})", __func__, fmt::ptr(&ratio_dest));
//
//  todo;
//}

// 001610F0
//ETimeBand CMap::GetTimeLightingRatio(vec4& ratio_dest) const
//{
//  log_trace("CMap::{}({})", __func__, fmt::ptr(&ratio_dest));
//
//  todo;
//  return ETimeBand::Night;
//}

// 001612B0
//void CMap::GetSunPoint(vec3& point_dest) const
//{
//  log_trace("CMap::{}({})", __func__, fmt::ptr(&point_dest));
//
//  todo;
//}

// 00161360
sint CMap::GetLightNoTime(MAYBE_UNUSED ETimeBand time)
{
  log_trace("CMap::{}({})", __func__, static_cast<sint>(time));

  todo;
  return 0;
}

// 00161480
bool CMap::GetTimeEnable() const
{
  log_trace("CMap::{}()", __func__);

  todo;
  return false;
}

// 00161490
CMapLightingInfo CMap::GetLightingInfo() const
{
  log_trace("CMap::{}()", __func__);

  todo;
  return CMapLightingInfo();
}

// 00161770
sint CMap::GetActiveLightNo() const
{
  log_trace("CMap::{}()", __func__);

  todo;
  return 0;
}

// 00161790
CMapLightingInfo CMap::GetLightInfo(MAYBE_UNUSED f32* f_buf, MAYBE_UNUSED usize buf_size) const
{
  log_trace("CMap::{}({}, {})", __func__, fmt::ptr(f_buf), buf_size);

  todo;
  return CMapLightingInfo();
}

// 00164480
void CMap::LoadMapFile(MAYBE_UNUSED char* file, MAYBE_UNUSED uint size, MAYBE_UNUSED sint add_mode)
{
  log_trace("CMap::{}({}, {}, {})", __func__, fmt::ptr(file), size, add_mode);

  todo;
}

// 00164510
void CMap::SetPieceLoadSkip(MAYBE_UNUSED bool skip)
{
  log_trace("CMap::{}({})", __func__, skip);

  todo;
}

// 00160C70
ETimeBand GetTimeBand(f32 time)
{
  log_trace("{}({})", __func__, time);

  using enum ETimeBand;

  if (time < 6.0f || time >= 21.0f)
  {
    // 9 PM until 6 AM
    return Night;
  }

  if (time < 9.0f)
  {
    // 6 AM to 9 AM
    return Morning;
  }

  if (time < 17.0f)
  {
    // 9 AM to 5 PM
    return Midday;
  }

  if (time < 21.0f)
  {
    // 5 PM to 9 PM
    return Evening;
  }

  unreachable_code;
}
