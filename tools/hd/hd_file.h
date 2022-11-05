#pragma once
#include <algorithm>
#include "common/types.h"
#include "common/strings.h"
#include "common/file_helpers.h"

#include "../iso9660/iso_file.h"

namespace hd
{
  #pragma pack(push, 1)
  struct hd2_file_descriptor
  {
    // offset in the file of the location of the name
    u32 name_location;
    // I don't know what these are for, padding maybe?
    u32 unk0;
    u32 unk1;
    u32 unk2;
    // position in the file
    u32 offset;
    // size of the file at pos
    u32 size;
    // ISO9660 LBA
    u32 logical_block_address;
    // ISO9660 extent
    u32 logical_block_size;
  };

  struct hd3_file_descriptor
  {
    // offset in the file of the location of the name
    u32 name_location;
    // size of the file at pos
    u32 size;
    // ISO9660 LBA
    u32 logical_block_address;
    // ISO9660 extent
    u32 logical_block_size;
  };

  union file_descriptor
  {
    hd3_file_descriptor hd3;
    hd2_file_descriptor hd2;
  };
  #pragma pack(pop)

  static_assert(sizeof(hd2_file_descriptor) == 32);
  static_assert(sizeof(hd3_file_descriptor) == 16);

  static_assert(sizeof(file_descriptor) == sizeof(hd2_file_descriptor));

  enum class file_type
  {
    not_hd_file,
    hd2_file,
    hd3_file
  };

  struct hdx_file_entry
  {
    std::string label{ };

    // the location of the start of the data in the ISO
    u64 data_file_logical_block_start{ 0 };

    // the size of the data in the ISO (aligned up)
    u64 data_file_logical_block_count{ 0 };

    // any extra bytes that need to be copied out
    u64 data_file_remaining_bytes_count{ 0 };
  };

  using hdx_file_entry_list = std::vector<hd::hdx_file_entry>;

  namespace constants
  {
    static constexpr usize hd3_size = sizeof(hd3_file_descriptor);
    static constexpr usize hd2_size = sizeof(hd2_file_descriptor);
  }

  class file
  {
  public:
    file() = delete;
    file(iso9660::file::file_entry entry);
    ~file();

  public:
    static inline bool is_valid_desciptor(const iso9660::file::file_entry& entry)
    {
      const std::string_view file_path = entry.path;
      const std::string_view file_ext = common::file_helpers::ext(file_path);

      if (common::strings::lowercase(file_ext) == "hd2" || common::strings::lowercase(file_ext) == "hd3")
        return true;

      return false;
    }

    inline bool descriptor_is_valid() const
    {
      return m_file_type != file_type::not_hd_file;
    }

    bool descriptor_table_final_logical_block_offset(u64 block_offset) const
    {
      return block_offset == m_descriptor_file_table_end_logical_block_offset;
    }

    bool find_data_file();
    bool block_offset_is_end_of_descriptor_table(u64 block_offset);

    void find_end_of_descriptor_table();

    hdx_file_entry_list get_entries_for_descriptor_table_block_offset(u64 block_offset);
  private:
    void read_hd2_descriptor(hd2_file_descriptor* desc, u64 block, u64 index);
    void read_hd3_descriptor(hd3_file_descriptor* desc, u64 block, u64 index);

    hdx_file_entry_list read_hd2_file_entries_for_offset(u64 block_offset);
    hdx_file_entry_list read_hd3_file_entries_for_offset(u64 block_offset);

    std::string read_entry_label(u64 block_offset, u64 byte_offset);

    u64 total_descriptor_entries_per_block();
  private:
    file_type m_file_type{ file_type::not_hd_file };

    iso9660::file::file_entry m_data_file_entry{ };
    iso9660::file::file_entry m_descriptor_file_entry{ };

    u64 m_descriptor_file_table_end_logical_block_offset{ 0 };

    std::unique_ptr<u8[]> m_logical_block_temp_buffer{ };
  };
}

template<>
struct fmt::formatter<hd::hdx_file_entry> : formatter<std::string_view>
{
  auto format(const hd::hdx_file_entry& hdx, format_context& ctx)
  {
    constexpr std::string_view tpl =
    {
      "HDX(LBA: {}, LBA count: {})"
    };

    fmt::format_to(ctx.out(), tpl, hdx.data_file_logical_block_count, hdx.data_file_logical_block_count);
  }
};