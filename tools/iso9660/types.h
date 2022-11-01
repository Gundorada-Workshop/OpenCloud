#pragma once
#include "common/types.h"

namespace iso9660
{
  namespace constants
  {
    // size of our temp buffer and assumed size of a sector
    static constexpr usize assumed_sector_size{ 2048 };
    // lba position of the start of the data area
    static constexpr usize data_lba_start{ 16 };
    // ECMA 6.8.2.1
    // maximum depth of the directory tree
    static constexpr usize max_dir_depth{ 8 };
  }

  // some stuff is le followed by be (dual endian)
  // small helper for dealing with that
  template<typename T>
  struct dual_endian
  {
    std::array<T, 2> data{ };
  };

  template<typename T>
  static inline T deget(const dual_endian<T>& de)
  {
    if constexpr (std::endian::native == std::endian::little)
      return de.data[0];
    else
      return de.data[1];
  }

  // 8-bit unsigned numerical values
  using iso711_t = u8;
  // 8-bit signed numerical values
  using iso712_t = s8;
  // 16-bit numerical values le
  using iso721_t = u16;
  // 16-bit numerical values be
  using iso722_t = u16;
  // 16-bit numerical values de
  using iso723_t = dual_endian<u16>;
  // 32-bit numerical values le
  using iso731_t = u32;
  // 32-bit numerical values be
  using iso732_t = u32;
  // 32-but numerical values de
  using iso733_t = dual_endian<u32>;

  using achar = char;
  using dchar = char;

  enum volume_descriptor_types : iso711_t
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
  struct datetime_short_format
  {
    // number of years since 1900
    iso711_t years_since_1900;
    // month 1-12
    iso711_t months;
    // day 1-31
    iso711_t days;
    // hour 0-23
    iso711_t hours;
    // minute 0-59
    iso711_t minutes;
    // second 059
    iso711_t seconds;
    //-48 to +52
    iso712_t gmt_offset;
  };

  static_assert(sizeof(datetime_short_format) == 7);

  struct datetime_long_format
  {
    iso711_t year[4];
    iso711_t month[2];
    iso711_t day[2];
    iso711_t hour[2];
    iso711_t minute[2];
    iso711_t seconds[2];
    iso711_t hecta_seconds[2];
    iso712_t gmt_offset;
  };

  static_assert(sizeof(datetime_long_format) == 17);

  // directory entry
  struct dirent
  {
    // 9.1.6
    enum file_flags
    {
      // 0: existence of file known to user upon unquiry
      // 1: existence of file need not be known to user
      file_flag_exists = 1 << 0,
      // 0: not a directory
      // 1: directory
      file_flag_direcrtory = 1 << 1,
      // 0: not an associated file
      // 1: associated file
      file_flag_associated = 1 << 2,
      // 0: record format not specified by XA
      // 1: record format specified by XA
      file_flag_record = 1 << 3,
      // 0: no owner or grpup identification
      // 1: owner and group identification specified and permissions field of XA
      file_flag_protected = 1 << 4,
      // 0: final directory record
      // 1: not final directory record
      file_flat_multi_extent = 1 << 7,
      // a directory can't be any of these
      file_not_directory = file_flat_multi_extent | file_flag_associated | file_flag_exists
    };

    // langth of the directory record in bytes
    iso711_t bytes;
    // XA length if XA is used otherwise 0
    iso711_t extended_attribute_record_length;
    // LBA of the first local block allocated to the extent
    iso733_t extent_logical_block_number;
    // data length of the file section
    // not including XA
    iso733_t file_section_length;
    // recording date and time
    datetime_short_format filetime;
    // if no XA then 0
    // bits 2, 3 and 7 set to zero is a directory
    iso711_t flags;
    // file unit size for the file section
    iso711_t unit_size;
    // interleave gap
    iso711_t gap;
    // ordinal number of the volumn in the volume set
    iso723_t volume_sequence_num;
    // length of the string held in name
    iso711_t name_length;
    // the string
    char name[1];
  };

  static_assert(sizeof(dirent) == 34);

  struct path_table_entry
  {
    iso711_t name_length;
    iso711_t extended_attributes_length;
    iso731_t extent;
    iso721_t parent;
  };

  static_assert(sizeof(path_table_entry) == 8);

  struct volume_descriptor_header
  {
    // the type of volume descriptor
    iso711_t type;
    // "CD001"
    char magic[5];
    // 1 (ECMA 119)
    iso711_t version;
  };

  // used for when we don't know the type yet
  struct volume_descriptor_base
  {
    volume_descriptor_header header;
    u8 pad[2041];
  };

  // This implements ISO9660 Joliet (8.5).
  // Which basically means it has two additional fields.
  // The additional fields are unused in the normal standard so it's no harm to include them.
  // Otherwise we'd duplicate this struct with minor edits as volume_table_secondary.
  struct volume_descriptor_primary
  {
    static constexpr const char* magic_id = "CD001";
    static constexpr usize max_iso_path_name = 255;
    static constexpr usize max_publisher_id_size = 128;
    static constexpr usize max_application_id_size = 128;
    static constexpr usize max_volume_set_id_size = 128;
    static constexpr usize max_preparer_id_size = 128;
    static constexpr usize max_system_id_size = 32;
    static constexpr usize max_volume_id_size = 32;

    struct path_table_location_entry
    {
      u32 table;
      u32 optional_table;
    };

    using path_table_de = dual_endian<path_table_location_entry>;

    volume_descriptor_header header;
    iso711_t flags;
    achar system_id[max_system_id_size];
    dchar volume_id[max_volume_id_size];
    // unused
    u8 pad1[8];
    // total sector count
    iso733_t volume_space_size;
    // note: supplemental descriptor only
    char volume_escape_sequences[32];
    iso723_t volume_set_size;
    iso723_t volume_sequence_number;
    // sector size
    iso723_t logical_block_size;
    // bytes in the path table
    iso733_t path_table_size;
    // first sector of l path table
    path_table_de path_table_lba;
    // root directory
    dirent root_dir_ent;
    // volume set
    dchar volume_set_id[max_volume_set_id_size];
    // publisher id
    achar publisher_id[max_publisher_id_size];
    // preparer
    achar preparer_id[max_preparer_id_size];
    // application
    char application_id[max_application_id_size];
    // copyright file
    char copyright_file_id[37];
    // abstract file
    char abstract_file_id[37];
    // section 7.5
    char bibliography_file[37];
    // date time of the volume creation
    datetime_long_format volume_created;
    // date time of the most recent modification to the volume
    datetime_long_format volume_modified;
    // date time of the volume expiration
    datetime_long_format volume_expires;
    // date time when the volume is effective
    datetime_long_format volume_effective;
    // 1 for ECMA 119
    iso711_t file_structure_version;
    // unused
    u8 pad3[1];
    // app can add whatever custom data it wants here
    char app_data[512];
    // unused
    u8 pad4[653];
  };

  // must be exactly the sector size
  static_assert(sizeof(volume_descriptor_base) == constants::assumed_sector_size);
  static_assert(sizeof(volume_descriptor_primary) == constants::assumed_sector_size);
  #pragma pack(pop)
}
