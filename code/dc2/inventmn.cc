#include "common/log.h"

#include "dc2/inventmn.h"
#include "dc2/mg/mg_lib.h"

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

  user_picture_info->m_unk_field_0 = 0;
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

  for (auto& unk_var : m_unk_field_408)
  {
    Initialize_USER_PICTURE_INFO(&unk_var.m_user_picture_info);
  }

  memset(&m_unk_field_6D8, 0, sizeof(m_unk_field_6D8));

  ResetAddress();
}

// 001fe970
void CInventUserData::ResetAddress()
{
  log_trace("CInventUserData::ResetAddress()");

  for (int i = 0; i < m_unk_field_408.size(); ++i)
  {
    m_unk_field_408[i].m_unk_field_14 = &m_unk_field_D60[i];
  }
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