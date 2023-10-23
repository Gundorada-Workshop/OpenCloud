#pragma once
#include <fmt/format.h>

#include "common/macros.h"

#include "data/iso/types.h"
#include "data/iso/dirent.h"

namespace data
{
  // size of our temp buffer and assumed size of a sector
  constexpr usize iso_default_sector_size{ 2048 };

  // lba position of the start of the data area
  constexpr usize iso_data_start_logical_block_address{ 16 };

  // ECMA 6.8.2.1
  // maximum depth of the directory tree
  constexpr usize iso_max_directory_tree_depth{ 8 };

  constexpr const char* iso_primary_volume_magic_id = "CD001";

  constexpr usize iso_max_path_name_length = 255;
  constexpr usize iso_max_publisher_id_size = 128;
  constexpr usize iso_max_application_id_size = 128;
  constexpr usize iso_max_volume_set_id_size = 128;
  constexpr usize iso_max_preparer_id_size = 128;
  constexpr usize iso_max_system_id_size = 32;
  constexpr usize iso_max_volume_id_size = 32;

  enum iso_volume_descriptor_type : iso711_t
  {
    // bootable
    vd_boot_record = 0,
    // all iso-9660
    vd_primary = 1,
    // joliet and such
    vd_supplementary = 2,
    // cd partition
    vd_partition = 3,
    vd_max = 255,
  };

  #pragma pack(push, 1)
  struct iso_path_table_entry
  {
    iso711_t name_length;
    iso711_t extended_attributes_length;
    iso731_t extent;
    iso721_t parent;
  };

  struct iso_path_table_location_entry
  {
    u32 table;
    u32 optional_table;
  };

  using iso_path_table_de = iso_dual_endian<iso_path_table_location_entry>;

  static_assert(sizeof(iso_path_table_entry) == 8);

  struct iso_volume_descriptor_header
  {
    // the type of volume descriptor
    iso711_t type;

    // "CD001"
    char magic[5];

    // 1 (ECMA 119)
    iso711_t version;
  };

  // used for when we don't know the type yet
  struct iso_volume_descriptor_base
  {
    iso_volume_descriptor_header header;
    u8 pad[2041];
  };

  // This implements ISO9660 Joliet (8.5).
  // Which basically means it has two additional fields.
  // The additional fields are unused in the normal standard so it's no harm to include them.
  // Otherwise we'd duplicate this struct with minor edits as volume_table_secondary.
  struct iso_volume_descriptor_primary
  {
    //
    iso_volume_descriptor_header header;

    //
    iso711_t flags;

    //
    achar system_id[iso_max_system_id_size];

    //
    dchar volume_id[iso_max_volume_id_size];

    // unused
    u8 pad1[8];

    // total sector count
    iso733_t volume_space_size;

    // note: supplemental descriptor only
    char volume_escape_sequences[32];

    //
    iso723_t volume_set_size;

    //
    iso723_t volume_sequence_number;

    // sector size
    iso723_t logical_block_size;

    // bytes in the path table
    iso733_t path_table_size;

    // first sector of l path table
    iso_path_table_de path_table_lba;

    // root directory
    iso_dirent root_dir_ent;

    // this isn't in the spec but root dirent ends in a empty char array
    char pad[1];

    // volume set
    dchar volume_set_id[iso_max_volume_set_id_size];

    // publisher id
    achar publisher_id[iso_max_publisher_id_size];

    // preparer
    achar preparer_id[iso_max_preparer_id_size];

    // application
    char application_id[iso_max_application_id_size];

    // copyright file
    char copyright_file_id[37];

    // abstract file
    char abstract_file_id[37];

    // section 7.5
    char bibliography_file[37];

    // date time of the volume creation
    iso_datetime_long volume_created;

    // date time of the most recent modification to the volume
    iso_datetime_long volume_modified;

    // date time of the volume expiration
    iso_datetime_long volume_expires;

    // date time when the volume is effective
    iso_datetime_long volume_effective;

    // 1 for ECMA 119
    iso711_t file_structure_version;

    // unused
    u8 pad3[1];

    // app can add whatever custom data it wants here
    char app_data[512];

    // unused
    u8 pad4[653];
  };

  constexpr auto foo = sizeof(iso_volume_descriptor_primary);

  assert_type_size_static(iso_volume_descriptor_header, 7);
  assert_type_size_static(iso_volume_descriptor_base, iso_default_sector_size);
  assert_type_size_static(iso_volume_descriptor_primary, iso_default_sector_size);
  #pragma pack(pop)
}

template<>
struct fmt::formatter<data::iso_volume_descriptor_header> : formatter<std::string_view>
{
  auto format(const data::iso_volume_descriptor_header& header, format_context& ctx)
  {
    static constexpr std::string_view tpl =
    {
      "vdh(magic: {}, type: {}, version: {})"
    };

    return fmt::format_to(ctx.out(), tpl, header.magic, header.type, header.version);
  }
};

template<>
struct fmt::formatter<data::iso_volume_descriptor_base> : formatter<std::string_view>
{
  auto format(const data::iso_volume_descriptor_base& desc, format_context& ctx)
  {
    static constexpr std::string_view tpl =
    {
      "vd base(header: {})"
    };

    return fmt::format_to(ctx.out(), tpl, desc.header);
  }
};

template<>
struct fmt::formatter<data::iso_path_table_location_entry> : formatter<std::string_view>
{
  auto format(const data::iso_path_table_location_entry& path_table, format_context& ctx)
  {
    static constexpr std::string_view tpl =
    {
      "path table location(table: {}, optional table: {})"
    };

    return fmt::format_to(ctx.out(), tpl, path_table.table, path_table.optional_table);
  }
};

// dual endian of above
template<>
struct fmt::formatter<data::iso_path_table_de> : formatter<std::string_view>
{
  auto format(const data::iso_path_table_de& path_table, format_context& ctx)
  {
    return fmt::format_to(ctx.out(), "{}", data::iso_get_native_endian(path_table));
  }
};

template<>
struct fmt::formatter<data::iso_path_table_entry> : formatter<std::string_view>
{
  auto format(const data::iso_path_table_entry& path_table, format_context& ctx)
  {
    static constexpr std::string_view tpl =
    {
      "path table entry(XA length: {}, extent: {}, name length: {}, parent: {})"
    };

    return fmt::format_to(ctx.out(), tpl,
      path_table.extended_attributes_length, path_table.extent,
      path_table.name_length, path_table.parent);
  }
};