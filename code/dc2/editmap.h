#pragma once
#include "common/debug.h"
#include "common/types.h"

#include "dc2/map.h"
#include "dc2/mg/mg_lib.h"
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
  vec3 GetWPos(usize x, usize y) const;

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
  void GetRiverPos(usize x, usize y, matrix4& dest) const;

  // 00298170
  void GetRiverPos(usize x, usize y, vec3& dest) const;

  // 00298200
  void GetRiverPoly(CCPoly* dest, const mgVu0FBOX& box, sint i, f32 f);

  // 002985C0
  mgVu0FBOX GetGridBox(const vec3& pos) const;

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
  vec3 m_grid_start_pos{ 0.0f };
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
  std::optional<vec3> GetDefColor(ssize index) const;

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
  mgVu0FBOX m_parts_bound_box{};
  // 70
  std::array<EditPartsMaterial, 4> m_material{};

  // A0
  vec3 m_unk_field_A0{};
  // B0
  vec3 m_unk_field_B0{};

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
    matrix4 m_wall_plane{};
  };

  // 001B5860
  virtual void SetPosition(const vec3& position) override;

  // 001B58E0
  virtual void SetPosition(f32 x, f32 y, f32 z) override;

  // 001B5930
  virtual vec3 GetPosition() override;

  // 001B59A0
  virtual void UpdatePosition() override;

  // 001B5990
  vec3 GetLocalPos();

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
  bool GetFenceSide(vec3& v1_dest, vec3& v2_dest);

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
  unk32 m_unk_field_320{};
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