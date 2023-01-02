#pragma once
#include <vector>

#include "common/types.h"

#include "dc2/collision.h"
#include "dc2/mg/mg_lib.h"
#include "dc2/object.h"
#include "dc2/object_anime.h"

// ~ 0015C420 - 00168400

class CMdsInfo;
class CMapParts;
struct InScreenFuncInfo;
class CMdsListSet;
class CCharacter2;

// FIXME: Find out where this should go
// 12/29/22 nah just use an std::list instead (or vector if you're confident with changing that spec)
template <typename T> class CList
{
  void Initialize();
  T* pGetData();
};

enum class ETimeBand : uint
{
  Midday = 0,
  Evening = 1,
  Night = 2,
  Morning = 3
};

// TODO THIS FILE
struct MapEventInfo {};
class CMapFlagData {};
class CPartsGroup {};
class CFuncPoint {};
class CFuncPointCheck {};
class CCameraInfo {};
class CCameraDrawInfo {};
class CMapWater {};
class CMapInfo {};
class CMapLightingInfo {};
class CMapTreasureBox {};
class CMapSky {};
class CMapEffect_Sprite {};
class CMapEffect {};
class CMapEffectsManager {};
class COcclusion {};

struct PieceMaterial
{
  // 8
  bool m_unk_field_8{};
  // C
  usize m_color_idx{};
  // 10
  //vec4 m_color{};
};

class CMapPiece : public CObjectFrame
{
public:
  // 00168AC0
  CMapPiece();

  // 00168850
  CMapPiece(const CMapPiece& other);
public:
  // 00166E40
  virtual unkptr Draw() override;
  
  // 0015E3E0
  virtual unkptr DrawDirect() override;

  // 00162750
  void SetMaterial(usize capacity);

  // 00168520
  void AssignMds(CMdsInfo* mds_info);

  // 00168570
  //sint GetPoly(sint i1, CCPoly* dest, mgVu0FBOX& box, sint i2);

  // 00168620
  void SetTimeBand(f32 f1, f32 f2);

  // 00168630
  PieceMaterial* GetMaterial(ssize index);

  // 00168680
  void Step();

  // 001686D0
  //std::optional<mgVu0FBOX> GetBoundBox();

  // 00168730
  unkptr DrawSub(bool b);

  // 80
  std::string m_name{};
  // 84 FIXME: flags enum
  uint m_unk_field_84{};

  // 8C (capacity), 90 (buf)
  std::vector<PieceMaterial> m_material{};
  // 94
  f32 m_unk_field_94{};
  // 98
  f32 m_unk_field_98{};
  // 9C
  CCharacter2* m_unk_field_9C{};
  // A0 FIXME: enum
  s16 m_col_type{};
};

class CMapParts : public CObject
{
public:
  // 0015CB30 / 00166250
  CMapParts();

  // 00167AA0
  CMapParts(const CMapParts& other);

  // make a destructor please :)
public:
  // 0015E3D0
  virtual unkptr Draw() override;

  // 0015E3E0
  virtual unkptr DrawDirect() override;

  // 00166A00
  virtual bool PreDraw() override;

  // 00166E50
  virtual void DrawStep() override;

  // 001678E0
  virtual void Step();

  // 00167970
  virtual void AnimeStep(CFuncPointCheck* point_check, CObjAnimeEnv* anime_env);

  // 001666F0
  virtual void UpdatePosition();

  // 00162080
  void SetLODDist(const std::vector<f32>& lods);

  // 001620F0
  void SetLODBlend(bool flag);

  // 001621B0
  bool GetLODBlend() const;

  // 00166360
  void SetName(const std::string& name);

  // 001663C0
  void SetPartsName(const std::string& name);

  // 00166420
  void AddPiece(std::list<CMapPiece>& pieces);

  // 00166490
  CMapPiece* SearchPiece(const std::string& name);

  // 00166520
  CMapPiece* SearchPieceColType(sint col_type);

  // 00166580
  //sint GetPoly(sint i1, CCPoly* dest, mgVu0FBOX& box, sint i2);

  // 001666B0
  //sint GetColPoly(CCPoly* dest, mgVu0FBOX& box, sint i2);

  // 001666D0
  //sint GetCameraPoly(CCPoly* dest, mgVu0FBOX& box, sint i2);

  // 00166760
  //bool SetColor(ssize index, const vec4& rgba);

  // 001667B0
  //std::optional<vec4> GetColor(ssize index) const;

  // 001667F0
  //std::optional<vec4> GetDefColor(ssize index);

  // 001668E0
  void UpdateColor();

  // 00166A70
  unkptr DrawSub(bool b);

  // 00166ED0
  void CreateBoundBox();

  // 00167090
  //bool CheckColBox(mgVu0FBOX* box) const;

  // 001671D0
  //std::optional<mgVu0FBOX> GetBBox() const;

  // 00167220
  //std::optional<mgVu0FBOX> GetBoundBox();

  // 00167280
  //std::optional<vec4> GetBoundSphere();

  // 00167300
  //matrix4 GetLWMatrix();

  // 00167350
  bool InsideScreen() const;

  // 001673A0
  bool InsideScreen(const std::vector<COcclusion>& occlusion, sint i) const;

  // 001674B0
  void InScreenFunc(InScreenFuncInfo* func_info);

  // 00167730
  void DrawScreenFunc(mgCFrame* frame);

  // 001679F0
  void StepFuncPoint(CFuncPointCheck& point_check);

  // 00167A60
  void CopyFuncPointCheck(CFuncPointCheck& other);

  // 00168150
  bool AssignFuncAnime();

  // 70 (fixed buf size 0x20)
  std::string m_name{};
  // 90 (fixed buf size 0x20)
  std::string m_parts_name{};
  // B0
  std::list<CMapPiece> m_map_pieces{};
  // C0
  mgCFrame m_unk_field_C0{};

  // 1D8 (length), 1D0 (buf)
  std::vector<f32> m_lod_dist{};
  // 1D4
  bool m_lod_blend{};

  // 1E4
  bool m_active{};
  // 1E8
  // usize m_n_color{}; // m_color.size()
  // 1F0
  //std::array<vec4, 4> m_color{};

  // 230
  bool m_bounding_box_valid{};
  // 240
  //mgVu0FBOX m_bounding_box{};
  // 260
  //vec4 m_bounding_sphere{};
};

class CMap
{
public:

  static constexpr const char CMapName[] = "CMap";

  // 0015E250
  virtual unkptr DrawSub(bool b);

  // 00160B10
  virtual unkptr Draw();

  // 00160B30
  virtual unkptr DrawDirect();

  // 0015D7A0
  //virtual bool PreDraw(const vec3& v);

  // 0015E3F0
  virtual void DrawEffect();

  // 0015E5D0
  virtual void DrawFireEffect(sint texture_id);

  // 0015E720
  virtual void DrawFireRaster();

  // 0015E800
  virtual void DrawWater(mgCCamera* camera, mgCTexture* tex1, mgCTexture* tex2);

  // 0015F120
  //virtual sint GetPoly(sint i1, CCPoly* dest, mgVu0FBOX& box, sint i2);

  // 0015F260
  //virtual sint GetColPoly(CCPoly* dest, mgVu0FBOX& box, sint i2);

  // 0015F290
  //virtual sint GetCameraPoly(CCPoly* dest, mgVu0FBOX& box, sint i2);

  // 0015F880
  //virtual void GetEvent(const vec3* v, sint i, MapEventInfo* dest);

  // 0015FC00
  virtual void InScreenFunc(InScreenFuncInfo* func_info);

  // 0015FD00
  virtual void DrawScreenFunc(mgCFrame* frame);

  // 0015FF60
  virtual void GetSeSrcVolPan(sint* ip, f32* fp1_dest, f32* fp2_dest, sint i);

  // 0015FDF0
  virtual void AnimeStep(CObjAnimeEnv* env);

  // 0015FEF0
  virtual void Step();

  // 0015C510
  virtual std::string Iam() const;

  // 0015C600
  CPartsGroup* GetPartsGroup(ssize index);

  // 0015C640
  ssize AddPartsGroup(const std::string& group_name, CMapParts* parts);

  // 0015C750
  CPartsGroup* SearchPartsGroup(const std::string& group_name);

  // 0015C780
  ssize SearchPartsGroupNo(const std::string& group_name);

  // 0015C820
  ssize SearchEmptyPartsGroupNo();

  // 0015CA30
  void SetPlacePartsBuff(usize capacity);

  // 0015CBD0
  std::vector<CMapParts>& GetPlacePartsTable();

  // 0015CBE0
  void SetCameraInfoTable(usize capacity);

  // 0015CBF0
  CCameraInfo* GetCameraInfo(ssize index);

  // 0015CC40
  CMapParts* NewPlaceParts();

  // 0015CCB0
  CMdsInfo* SearchMDS(const std::string& mds_name);

  // 0015CCE0
  void CreateEffect(uint* p, sint i);

  // 0015CD00
  ssize SearchEffectIndex(const std::string& effect_name);

  // 0015CD10
  // seems the script interpreter passes in a list of multiple parts here, so
  // we'll just splice them into another list unless the spec changes
  void AddParts(std::list<CMapParts>& parts);

  // 0015CD60
  CMapParts* GetParts(const std::string& parts_name);

  // 0015CE00
  //void CreateDrawRect(mgVu0FBOX* box1, mgVu0FBOX* box2, sint i);

  // 0015CFD0
  //void CreateOcclusion(const matrix4* m);

  // 0015D080
  //void PlaceParts(const std::string& parts_name, const vec3& position, const vec3& rotation, const vec3& scale);

  // 0015D170
  void PlacePartsEnd();

  // 0015D350
  void ClearPlaceParts();

  // 0015D420
  CMapParts* GetPlaceParts(const std::string& parts_name);

  // 0015D4C0
  CMapParts* GetPlaceParts(ssize parts_index);

  // 0015D510
  ssize ConvertParts(CMapParts* parts);

  // 0015D550
  //void GetPlaceParts(mgVu0FBOX* region, std::vector<CMapParts>& parts_dest, usize max_capacity);

  // 0015D550
  //void GetPlaceColParts(mgVu0FBOX* region, std::vector<CMapParts>& parts_dest, usize max_capacity);

  // 0015D730
  void CreateFuncCheck(CFuncPointCheck* point_check);

  // 0015D770
  //std::optional<mgVu0FBOX> GetBBox() const;

  // 0015DBE0
  usize GetCharaLight(mgCObject* object, CFuncPoint* func_point, sint i1, sint i2);

  // 0015E0B0
  //void SetFuncPLight(const vec4& v, CFuncPointCheck* point_check);

  // 0015E1F0
  void ResetFuncPLight(ssize light_index);

  // 0015EF70
  void DrawTrBox();

  // 0015F110
  bool GetShow() const;

  // 0015F2C0
  //sint GetTrBoxColPoly(CCPoly* dest, mgVu0FBOX& box, sint i2);

  // 0015F3D0
  //sint GetFixCameraPos(const vec3& v1, vec3& v2);

  // 0015F730
  //void FixCameraPartsOnOff(const vec3& v);

  // 0015F880
  //CMapParts* GetEvent(const vec3& v, sint i, MapEventInfo* event_info);

  // 0015FDA0
  void EffectStep();

  // 001600D0
  void CreateMap(CMdsListSet* mds_list);

  // 00160150
  void AssignFuncPoint();

  // 001602C0
  void CreateTrBox(CMapTreasureBox* treasure_box, sint i);

  // 00160620
  CMapTreasureBox* GetTrBox(ssize index);

  // 00160670
  void DeleteTrBox(ssize index, CMapFlagData* flag_data);

  // 001606E0
  void UpdateTrBoxFlag(CMapFlagData* flag_data) const;

  // 00160780
  void LoadData(uint* p1, uint* p2, sint* p3);

  // 00160D30
  f32 GetNowTime() const;

  // 00160D70
  ETimeBand GetNowTimeBand() const;

  // 00160DA0
  ETimeBand GetNowTimeLightBand() const;

  // 00160E70
  //void GetLightingRatio(vec4& ratio_dest) const;

  // 00160FE0
  //void GetLightingFlareRatio(vec4& ratio_dest) const;

  // 00161010
  //void GetLightingSunRatio(vec4& ratio_dest) const;

  // 001610F0
  //ETimeBand GetTimeLightingRatio(vec4& ratio_dest) const;

  // 001612B0
  //void GetSunPoint(vec3& point_dest) const;

  // 00161360
  sint GetLightNoTime(ETimeBand time);

  // 00161480
  bool GetTimeEnable() const;

  // 00161490
  CMapLightingInfo GetLightingInfo() const;

  // 00161770
  sint GetActiveLightNo() const;

  // 00161790
  CMapLightingInfo GetLightInfo(f32* f_buf, usize buf_size) const;

  // 00164480
  void LoadMapFile(char* file, uint size, sint add_mode);

  // 00164510
  void SetPieceLoadSkip(bool skip);

  void LoadCfgFile(char* file, int size, mgCMemory* map_stack);
  
  // 0
  CMapInfo m_map_info{};

  // 104
  std::list<CMapParts> m_map_parts{}; // See AddParts usage for why this is a list for now
  // 108
  usize m_n_parts_group_buf{};
  // 10C
  std::array<CPartsGroup, 0x20> m_parts_group_buf{};

  // 328 (capacity), 32C (buf pointer), 330 (length)
  std::vector<CMapParts> m_map_place_parts{};
  // 334
  bool m_bounding_box_valid{ false };
  // 340
  //mgVu0FBOX m_bounding_box{};

  // C80 (capacity), C84 (buf)
  std::vector<CCameraInfo> m_camera_info{};
};

// 00160C70
ETimeBand GetTimeBand(f32 time_of_day);
