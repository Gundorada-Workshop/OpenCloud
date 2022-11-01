#pragma once
#include <memory>
#include <string_view>
#include <vector>
#include <bit>

#include "common/file_helpers.h"

#include "types.h"


namespace iso9660
{
  class extractor
  {
    // public types
  public:
    // pointer handle
    using ptr = std::unique_ptr<extractor>;
    using buffer_type = std::unique_ptr<u8[]>;

    struct file
    {
      std::string path{ };
      usize file_record_lba;
      usize size;
    };

    struct directory
    {
      std::string name{ };
      usize directory_record_lba;
      usize parent;
      bool root{ false };
    };

    // ctor and dtors
  public:
    // ctor
    extractor(std::string_view file);

    // dtor
    ~extractor();

    // static
  public:
    // get a handle to an iso file
    static ptr open(std::string_view file);

    // public instance functions
  public:
    bool extract_file(std::string_view iso_file_path, std::string_view to);
    bool extract_directory(std::string_view iso_file_path, std::string_view to);

    // private instance variables
  private:
    // file path of the ISO
    std::string m_file_path{ };

    // buffer for reading data
    buffer_type m_temp_buff{ };

    // handle to the underlying file
    std::FILE* m_file_handle{ nullptr };

    // current cached sector
    usize m_current_sector{ 0 };

    // the maximum number of sectors in the file
    usize m_max_sectors{ 0 };

    usize m_sector_size{ constants::assumed_sector_size };

    // the primary volume descriptor
    volume_descriptor_primary m_primary_volume_descriptor{ };

    // list of directories
    std::vector<directory> m_directory_records{ };

    // private instance functions
  private:
    // opens the underlying file
    bool open_iso_file();

    // closes the underlying file
    void close_iso_file();

    // get the size of the iso file
    std::optional<usize> get_iso_size();

    // read a sector into the temp buffer
    bool read_sector(usize sector_number);

    // search for the primary volume descriptor
    bool read_primary_volume_descriptor();

    std::optional<std::vector<file>> read_directory_descriptor(const directory& dir);

    // read out all directory entries
    bool open_path_table();

    // resize the temp buffer
    void resize_temp_buffer();

    // extract a file to a buffer
    bool extract_file_to(const file& file_entry, std::string_view dir);

    // private inline instance functions
  private:
    inline bool iso_seek(usize offset, int whence)
    {
      return common::file_helpers::seek64(m_file_handle, offset, whence);
    }

    inline std::optional<usize> iso_tell()
    {
      const auto pos = common::file_helpers::tell64(m_file_handle);

      if (iso_seek(pos, SEEK_SET))
        return pos;

      return std::nullopt;
    }

    // read the next sector into the temp buffer
    inline bool read_current_sector_to_temp()
    {
      if (m_current_sector >= m_max_sectors)
        return false;

      if (!read_sector(m_current_sector))
        return false;

      m_current_sector++;

      return true;
    }

    inline bool seek_sector(usize sector)
    {
      if (sector > m_max_sectors)
        return false;

      m_current_sector = sector;

      return true;
    }

    // read data out of the temp buffer
    inline bool temp_copy_buffer(void* buff, usize offset, usize size)
    {
      if (offset + size > m_sector_size)
        return false;

      memcpy(buff, &m_temp_buff[offset], size);

      return true;
    }

    // get the sector at file position
    inline usize get_sector_for_fpos(usize pos)
    {
      return pos / m_sector_size;
    }

    // get the file position at sector
    inline usize get_fpos_for_sector(usize sector_num)
    {
      return m_sector_size * sector_num;
    }

    // get offset in sector
    inline usize get_sector_offset_for_fpos(usize pos)
    {
      return pos % m_sector_size;
    }

    inline dirent root_directory_dirent()
    {
      return m_primary_volume_descriptor.root_dir_ent;
    }
  };
}
