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