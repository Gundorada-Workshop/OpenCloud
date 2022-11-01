#include "common/log.h"
#include "CMdsListSet.h"

set_log_channel("CMdsListSet")

// 001690D0
void CMdsListSet::Initialize()
{
  log_trace("CMdsListSet::Initialize()");

  m_n_mds_list = m_mds_list.size();
  for (int i = 0; i < m_n_mds_list; ++i)
  {
    m_mds_list[i].m_unk_field_0 = nullptr;
    m_mds_list[i].m_unk_field_4 = 0;
    m_mds_list[i].m_unk_field_8 = 0;
  }

  m_n_img_list = m_img_list.size();

  for (int i = 0; i < m_n_img_list; ++i)
  {
    m_img_list[i].m_unk_field_0 = nullptr;
    m_img_list[i].m_unk_field_4 = 0;
  }
}