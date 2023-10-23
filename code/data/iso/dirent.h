#pragma once
#include "common/macros.h"

#include "data/iso/types.h"
#include "data/iso/datetime.h"

namespace data
{
  #pragma pack(push, 1)
  // directory entry
  struct iso_dirent
  {
    // 9.1.6
    enum file_flags
    {
      // 0: existence of file known to user upon unquiry
      // 1: existence of file need not be known to user
      file_flag_exists = 1 << 0,
      // 0: not a directory
      // 1: directory
      file_flag_directory = 1 << 1,
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

    // length of the directory record in bytes
    iso711_t bytes;

    // XA length if XA is used otherwise 0
    iso711_t extended_attribute_record_length;

    // LBA of the first local block allocated to the extent
    iso733_t extent_logical_block_number;

    // data length of the file section
    // not including XA
    iso733_t file_section_length;

    // recording date and time
    iso_datetime_short filetime;

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
  };

  assert_type_size_static(iso_dirent, 33);
  #pragma pack(pop)
}