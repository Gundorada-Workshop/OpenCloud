#pragma once
#include <cmath>
#include <memory>

#include "common/debug.h"
#include "common/types.h"
#include "common/math.h"

#include "dc2/map.h"
#include "dc2/mg/mg_lib.h"
#include "dc2/userdata.h"


class CEditData;


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
  Invalid = -1,
  Uninitialized = 0,
  _1 = 1,
  _11 = 11,
};

class CGridData
{
public:
  // 0
  bool m_river{};
  // 4
  unk32 m_unk_field_4{};
  // 8
  unk32 m_unk_field_8{};
  // C
  unk32 m_unk_field_C{};
  // 10
  unk32 m_unk_field_10{};
};

class CEditGrid
{
public:
  // 00297770
  void Create(usize x, usize y);

  // 00297860
  void Clear();

  // 002978B0
  bool Check(usize x, usize y) const;

  // 00297900
  CGridData* Get(usize x, usize y);

  // 00297960
  // Unchecked Get!
  inline CGridData* GetFast(usize x, usize y)
  {
    return &m_tiles[m_x * x + y];
  }

  // 00297990
  // local position (discrete x, y position)
  std::optional<std::pair<usize, usize>> GetLPos(f32 x, f32 y) const;

  // 00297A50
  // world position (where are we in the scene, actually?)
  //vec3 GetWPos(usize x, usize y) const;

  // 00297AA0
  bool SetRiver(f32 x, f32 y);

  // 00297AA0
  bool ResetRiver(f32 x, f32 y);

  // 00297B20
  bool SetRiver(usize x, usize y);

  // 00297C10
  bool ResetRiver(usize x, usize y);

  // 00298040
  bool River(usize x, usize y);

  // 00298070
  //void GetRiverPos(usize x, usize y, matrix4& dest) const;

  // 00298170
  //void GetRiverPos(usize x, usize y, vec3& dest) const;

  // 00298200
  //void GetRiverPoly(CCPoly* dest, const mgVu0FBOX& box, sint i, f32 f);

  // 002985C0
  //mgVu0FBOX GetGridBox(const vec3& pos) const;

private:
  // 00297D10
  bool UpdateRiver(usize x, usize y);

public:

  // 0
  usize m_x{};
  // 4
  usize m_y{};
  // 8
  std::vector<CGridData> m_tiles{};
  // C
  f32 m_tile_len_x{};
  // 10
  f32 m_tile_len_y{};
  // 20
  vec3 m_grid_start_pos{ };
};

class CEditHouse
{
public:
  // 001B5790
  bool LiveChara() const;

  bool m_active{};
  std::array<ssize, 3> m_occupant_ids{ 0 };
};

struct EditPartsMaterial
{
  // 0
  ECommonItemData m_item_id{};
  // 4
  ssize m_count{};
};

enum class EEPartsInfoID
{
  Uninitialized = -999,
  Invalid = -1,
  _53 = 53,
  _78 = 78,
};

class CEditPartsInfo
{
public:
  // 001B5630
  EEPartsType GetPartsType() const;

  // 001B5670
  void CreateBox();

  // 001B56A0
  f32 GetPartsHeight() const;

  // 001B56B0
  f32 GetPartsMaxWidth() const;

  // 001B5730
  EditPartsMaterial* GetMaterial(ssize index);

  // 001B5760
  //std::optional<vec3> GetDefColor(ssize index) const;

  // 0
  EEPartsInfoID m_id{ EEPartsInfoID::Uninitialized };
  // 4 FIXME: flags enum
  uint m_unk_field_4{};

  // 18
  sint m_unk_field_18{ -1 };

  // 24
  EEPartsType m_type{ EEPartsType::Uninitialized };

  // 2C
  sint m_unk_field_2C{ -1 };

  // 3C
  std::string m_name{};

  // 44
  CMapParts* m_unk_field_44{};

  // 50
  //mgVu0FBOX m_parts_bound_box{};
  // 70
  std::array<EditPartsMaterial, 4> m_material{};

  // A0
  vec3 m_unk_field_A0{ };
  // B0
  vec3 m_unk_field_B0{ };

  // 254
  sint m_wall_group_num{};

  // SIZE 0x280
};

class CEditParts : public CMapParts
{
public:
  struct WallInfo
  {
  public:
    //matrix4 m_wall_plane{};
  };

  // 001B5860
  //virtual void SetPosition(const vec3& position) override;

  // 001B58E0
  //virtual void SetPosition(f32 x, f32 y, f32 z) override;

  // 001B5930
  //virtual vec3 GetPosition() override;

  // 001B59A0
  virtual void UpdatePosition() override;

  // 001B5990
  //vec3 GetLocalPos();

  // 001B5A50
  EEPartsInfoID GetInfoID() const;

  // 001B5A70
  sint GetLiveNPC() const;

  // 001B5A90
  bool IsWallParts() const;

  // 001B5AC0
  bool IsFence() const;

  // 001B5AF0
  bool IsBurn() const;

  // 001B5B20
  //bool GetFenceSide(vec3& v1_dest, vec3& v2_dest);

  // 001B5BD0
  bool GetWallPlane(sint i, WallInfo* wall_info) const;

  // 001B5DC0
  sint GetWallGroupNum() const;

  // 001B5DE0
  EEPartsType GetPartsType() const;

  // 001B5E20
  bool CheckTerritory(const CEditParts* other) const;

  // 001B5F50
  void CheckColorUpdate();

  // 310
  unk32 m_unk_field_310{};
  // 314
  CMapParts* m_unk_field_314{};
  // 318
  sint m_n_material{};
  // 31C
  unk32 m_unk_field_31C{};
  // 320
  std::unique_ptr<unk> m_unk_field_320{};
  // 324
  CEditPartsInfo* m_info{};
  // 328
  CEditHouse* m_house{};

  // ALIGNED SIZE 0x330
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
  CEditPartsInfo* GetePartsInfoAtID(EEPartsInfoID id);

  // 002A4F40
  CEditPartsInfo* GetePartsInfoAtType(EEPartsType parts_type);

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

class CEditMap : public CMap
{
public:
  static constexpr char CEditMapName[] = "CEditMap";

  // For placing items
  static constexpr f32 EDIT_ANGLE_INCREMENT = 15.0f;
  static constexpr sint MAX_EDIT_ANGLE = static_cast<sint>(360.0f / EDIT_ANGLE_INCREMENT);

  // 90.0f has to be evenly divisible by ANGLE_INCREMENT
  // (for GetEditAngle90)
  static_assert(90.0f / EDIT_ANGLE_INCREMENT == static_cast<f32>(MAX_EDIT_ANGLE) / 4);

  struct RemoveInfo
  {
  public:
  };

  // 001B4130
  virtual unkptr DrawSub(bool b) override;

  // 001B40A0
  //virtual bool PreDraw(const vec3& v) override;

  // 0029C1C0
  virtual void DrawEffect() override;

  // 0029BFD0
  virtual void DrawFireEffect(sint i) override;

  // 0029C110
  virtual void DrawFireRaster() override;

  // 001B0780
  //virtual sint GetPoly(sint i1, CCPoly* dest, mgVu0FBOX& box, sint i2) override;

  // 002A5960
  //virtual void GetEvent(const vec3* v, sint i, MapEventInfo* dest) override;

  // 002EF530
  virtual void InScreenFunc(InScreenFuncInfo* func_info) override;

  // 002EF630
  virtual void DrawScreenFunc(mgCFrame* frame) override;

  // 002EF6D0
  virtual void GetSeSrcVolPan(sint* ip, f32* fp1_dest, f32* fp2_dest, sint i) override;

  // 0029C330
  virtual void AnimeStep(CObjAnimeEnv* env) override;

  // 001B4090
  virtual void Step() override;

  // 001B02A0
  virtual std::string Iam() const override;

  // 001B0390
  void ClearGrid();

  // 001B0400
  void ClearHouse();

  // 001B0460
  void ClearAllParts();

  // 001B0660
  void InitialPlaceParts(CEditData* edit_data);

  // 001B0960
  void CreateTable(sint i1, sint i2);

  // 001B0B30
  CEditPartsInfo* GetePartsInfo(ssize index);

  // 001B0B40
  CEditPartsInfo* GetePartsInfo(const std::string& name);

  // 001B0B50
  CEditPartsInfo* GetePartsInfoAtID(EEPartsInfoID id);

  // 001B0B60
  CEditPartsInfo* GetePartsInfoAtType(EEPartsType type);

  // 001B0B70
  CEditPartsInfo* GetePartsInfoAtPlaceID(ssize place_id);

  // 001B0BA0
  CEditParts* eNewPlaceParts();
  
  // 001B0C00
  CEditHouse* eNewHouseInfo();

  // 001B0C40
  CEditParts* GetePlaceParts(ssize index);

  // 001B0CA0
  CEditParts* GetePlaceParts(const std::string& name);

  // 001B0D60
  void GetePlaceIDList(sint* ids_dest, usize max_size);

  // 001B0DD0
  //matrix4 GetRotMatrix(sint angle) const;

  // 001B0EB0
  sint GetEditAngle90(sint angle) const;

  // 001B0F00
  f32 GetEditAngle(sint angle) const;

  // 001B0F50
  sint ConvEditAngle(f32 angle) const;

  // 001B0FF0
  sint AngleLimit(sint angle) const;

  // 001B1020
  //vec3 GetEditPos(const vec3& pos) const;

  // 001B11D0
  sint CmpEditAlt(f32 f1, f32 f2) const;

  // 001B1220
  f32 GetEditAlt(f32 f) const;

  // 001B1280
  //bool GetGridPos(const vec3& v1, vec3& v2, vec3& v3) const;

  // 001B1360
  //matrix4 GetMatrix(const vec3& position, sint angle);

  // 001B13B0
  //matrix4 GetInverseMatrix(const matrix4& mat);

  // 001B13C0
  usize ConvertParts(CEditParts* parts);

  // 001B13F0
  std::optional<usize> GetSameParts(ssize index);

  // 001B14A0
  std::optional<usize> BuildEditParts(EEPartsInfoID id);

  // 001B14F0
  usize GetTotalPolyn(sint* ip1 = nullptr, sint* ip2 = nullptr);

  // 001B1630
  std::optional<usize> BuildEditParts(const std::string& name);

  // 001B1820
  bool DeleteEditParts(ssize index);

  // 001B18A0
  //bool RemoveEditParts(sint i, const vec3& v, const RemoveInfo* remove_info);

  // 001B1C50
  bool PlaceBurnParts();

  // 001B1CE0
  bool BurnEditParts(const RemoveInfo* remove_info);

  // 001B1F50
  //CEditParts* PlaceEditParts(const std::string& name, const vec3& position, const vec3& rotation);

  // 001B2000
  //CEditParts* PlaceEditParts(sint i, const EP_PLACE_INFO* place_info, const vec3& position, const vec3& rotation, sint* ip = nullptr);

  // 001B21D0
  //bool PlaceRiverParts(const vec3& position);

  // 001B2220
  bool CreatePlaceLog(sint i, const EP_PLACE_INFO* place_info);

  // 001B2320
  //std::vector<std::shared_ptr<CEditParts>> GetNearParts(CEditPartsInfo* info, const vec3& position, f32 radius);

  // 001B24D0
  //std::vector<std::shared_ptr<CEditParts>> GetNearParts(const mgVu0FBOX& bounding_box);

  // 001B2670
  //std::optional<usize> GetePlaceParts(const vec4& bounding_sphere);

  // 001B2740
  //std::optional<usize> GetePlaceParts(const vec3& origin, const std::vector<std::shared_ptr<CEditParts>>& collection);

  // 001B2A50
  //bool CheckEditParts(CEditPartsInfo* info, const vec3& position, f32 f, const EP_PLACE_INFO* place_info);

  // 001B2A50
  //f32 GetEditPartsAlt(CEditPartsInfo* info, const vec3& position, f32 f, const EP_PLACE_INFO* place_info);

  // 001B2B50
  //bool MagnetParts(CEditPartsInfo* info, const vec3& v1, const vec3& v2, const std::vector<std::shared_ptr<CEditParts>>& collection);

  // 001B3A90
  //bool MagnetParts(CEditPartsInfo* info, const vec3& v1, const vec3& v2);

  // 001B3B00
  //bool CheckWallEditParts(CEditPartsInfo* info, const vec3& v1, sint i1, sint i2, const EP_PLACE_INFO* place_info);

  // 001B4AC0
  void LoadEditInfo(char* script_buf, usize script_size);

  // 002967B0
  //void PlaceRiver(const vec3& position);

  // 00296840
  //void RemoveRiver(const vec3& position);

  // 002968D0
  //void CreateGrid(const vec3& v1, const vec3& v2, const vec3& v3);

  // 00296B80
  usize GetRiverNum(f32* fp);

  // 00296CE0
  //bool IsRiverGrid(const vec3& position);

  // 00296DA0
  usize GetRiverNum(ssize index, f32 f);

  // 00296E30
  void DrawRiverMask();

  // 00297350
  void DrawRiver();

  // 002A8B40
  void SaveData(CEditData* data);

  // 002A9110
  void LoadData(CEditData* data);

  // 002A9820
  sint CultureAnalyzeParts(sint i1, sint i2);

  // 002A9A20
  sint CultureAnalyze(sint i);

  // 002A9AB0
  std::pair<
    std::vector<std::shared_ptr<CMapParts>>,
    std::vector<std::shared_ptr<CMapPiece>>
  > GetOnOffParts(const std::string& name);

  // 002A9C60
  void PartsOnOff(sint i, CEditData* data);

  // 002ED720
  //f32 GetEditPartsAlt(CEditPartsInfo* info, const vec3& position, f32 f, const std::vector<std::shared_ptr<CEditParts>>& collection);

  // 002ED990
  //bool CheckEditParts(CEditPartsInfo* info, const vec3& position, f32 f, const EP_PLACE_INFO* place_info, const std::vector<std::shared_ptr<CEditParts>>& collection);

  // 002EDF60
  //bool CheckEditPartsOnRiver(CEditPartsInfo* info, const vec3& position, f32 f);

  // 002EE280
  //bool CheckRiverParts(const vec3& position);

  // 002EE5F0
  bool CheckNormalPlaceParts(ssize index);

  // 002EE620
  bool CheckNormalPlaceParts(CEditParts* parts);

  // 002EE660
  bool CheckLiveNPC(sint i1, sint i2);

  // 002EE770
  usize GetePlacePartsAtInfoID(EEPartsInfoID id, sint* ip, sint i);

  // 002EE920
  usize GetTerritoryParts(sint i1, sint* ip, sint i2);

  // 002EEA30
  usize GetChildParts(sint i1, sint* ip, sint i2);

  // 002EEAF0
  sint RepaintNum(sint i);

  // 002EEB10
  //usize PaintFence(sint i1, const vec3& v, sint i2);

  // 002EEDE0
  usize PaintFence(CEditParts* parts);

  // 002EEEC0
  void UpdateHouse();

  // 002EF0B0
  void GroundBalance(sint i);

  // 002EF480
  bool BalanceCheck() const;

  // D48
  std::array<CEditHouse, 32> m_house{};

  // F50 (size), F54 (buf)
  std::array<std::unique_ptr<CEditGrid>, 4> m_edit_grid{};

  // F68
  f32 m_unk_field_F68{};

  // F94
  CEditInfoMngr m_edit_info_mngr{};
};
