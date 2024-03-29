#include "common/helpers.h"
#include "common/log.h"

#include "engine/inventmn.h"
#include "engine/mg/mg_lib.h"

set_log_channel("inventmn");

// 01EC96E0
mgCMemory MenuInventStack{};
// 01EC9710
mgCMemory MenuInventCharaStack{};
// 01EC9740
mgCMemory MenuInventMCStack{};
// 01ECB7A0
mgCMemory InventTeigiStack{};

// 001FE170
void Initialize_USER_PICTURE_INFO(USER_PICTURE_INFO* user_picture_info)
{
  log_trace("Initialize_USER_PICTURE_INFO({})", fmt::ptr(user_picture_info));

  if (user_picture_info == nullptr)
  {
    return;
  }

  user_picture_info->m_used = false;
  user_picture_info->m_unk_field_1 = 0;
  user_picture_info->m_unk_field_2 = -1;
  user_picture_info->m_unk_field_4 = -1;
  user_picture_info->m_unk_field_8 = -1;
  user_picture_info->m_unk_field_6 = -1;
  user_picture_info->m_unk_field_A = 0;
}

// 001fe880
void CInventUserData::Initialize()
{
  log_trace("CInventUserData::Initialize()");

  m_unk_field_0 = 0;
  m_unk_field_4 = 0;
  memset(&m_unk_field_8, 0, sizeof(m_unk_field_8));
  memset(&m_unk_field_D60, 0, sizeof(m_unk_field_D60));

  for (auto& picture : m_pictures)
  {
    Initialize_USER_PICTURE_INFO(&picture.m_picture_info);
  }

  memset(&m_unk_field_6D8, 0, sizeof(m_unk_field_6D8));

  ResetAddress();
}

// 001fe970
void CInventUserData::ResetAddress()
{
  log_trace("CInventUserData::ResetAddress()");

  for (int i = 0; i < m_pictures.size(); ++i)
  {
    m_pictures[i].m_unk_field_14 = &m_unk_field_D60[i];
  }
}

// 001FEE40
usize CInventUserData::GetNowHavePictureNum()
{
  log_trace("CInventUserData::{}()", __func__);

  usize count = 0;
  for (auto& picture : m_pictures)
  {
    if (picture.m_picture_info.m_used)
    {
      ++count;
    }
  }

  return count;
}

// 001FF070
void CInventUserData::SetCreateItemFlag(usize index, ECommonItemData item_id)
{
  log_trace("CInventUserData::{}({}, {})", __func__, index, s32(item_id));

  if (index > 0 && m_unk_field_6D8[index] == ECommonItemData::Invalid)
  {
    m_unk_field_6D8[index] = item_id;
    return;
  }

  for (usize i = 1; i < m_unk_field_6D8.size(); ++i)
  {
    if (m_unk_field_6D8[i] == ECommonItemData::Invalid)
    {
      m_unk_field_6D8[i] = item_id;
      return;
    }
  }
}

// 001FF0E0
ECommonItemData CInventUserData::GetCreateItemId(usize index)
{
  log_trace("CInventUserData::{}({})", __func__, index);

  if (index >= m_unk_field_6D8.size())
  {
    return ECommonItemData::Invalid;
  }

  return m_unk_field_6D8[index];
}

// 001FF120
ssize CInventUserData::IsAlreadyCreatedItem(ECommonItemData item_id)
{
  log_trace("CInventUserData::{}({})", __func__, s32(item_id));

  for (usize i = 0; i < m_unk_field_6D8.size(); ++i)
  {
    if (m_unk_field_6D8[i] == item_id)
    {
      return i;
    }
  }

  return -1;
}

// 001FF170
// "GetHatsumeiNum"
uint CInventUserData::GetInventionNum()
{
  log_trace("CInventUserData::{}()", __func__);
  uint count = 0;

  for (auto item_id : m_unk_field_6D8)
  {
    if (item_id != ECommonItemData::Invalid)
    {
      ++count;
    }
  }

  return count;
}

// 00200350
bool CheckInventItem(MAYBE_UNUSED ECommonItemData item_id)
{
  log_trace("{}({})", __func__, common::to_underlying(item_id));

  todo;
  return false;
}

// 002005D0
usize CheckInventPhoto(MAYBE_UNUSED sint i1, MAYBE_UNUSED sint i2)
{
  log_trace("{}({}, {})", __func__, i1, i2);

  todo;
  return 0;
}
