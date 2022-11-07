#pragma once
#include <optional>

#include "common/strings.h"
#include "common/types.h"

#include "types.h"

namespace iso9660
{
  class file
  {
  public:
    struct path_entry
    {
      std::string path{ };
      iso9660::path_table_entry table;
    };

    struct directory_entry
    {
      std::string path{ };
      u64 logical_block_address{ 0 };
      path_entry entry{ };
    };

    struct file_entry
    {
      std::string path{ };
      u64 logical_block_address{ 0 };
      u64 logical_block_count{ 0 };
      u64 extra_bytes{ 0 };
      iso9660::dirent entry{ };
    };

    using ptr_type = std::unique_ptr<file>;
    using buffer_type = std::unique_ptr<u8[]>;

    using path_list = std::vector<path_entry>;
    using directory_list = std::vector<directory_entry>;
    using file_list = std::vector<file_entry>;

    // ctor
    file();

    // dtor
    ~file();

  public:
    // open an iso file
    static ptr_type open(std::string_view path);

    // close an iso file
    void close();

    // seek to lba
    void seek_block(u64 logical_block_address);

    // tell lba
    u64 tell_block();

    // read data
    bool copy_data_from_block(u64 logical_block_address, u8* buff);

    // get a list of directories
    directory_list get_directories();

    // get a list of files in a directory
    file_list get_files_for_directory(std::string_view dir_path);

  public:
    inline u64 get_logical_block_size() const
    {
      return m_logical_block_size;
    }

    inline std::string_view get_path()
    {
      return m_path;
    }

  private:
    // current path to the iso
    std::string m_path{ };

    // c file handle for the iso
    std::FILE* m_file{ nullptr };

    // logical block size
    u64 m_logical_block_size{ 0 };

    // number of logical blocks
    u64 m_logical_block_count{ 0 };

    // current block pointer
    u64 m_current_logical_block{ 0 };

    // primary volume descriptor
    volume_descriptor_primary m_volume_descriptor{ };

    // temp buffer of logical block size
    buffer_type m_temp_buffer{ };

    // path table list
    path_list m_paths{ };

  private:
    // get the file size in bytes (as opposed to LBA count)
    std::optional<usize> get_file_byte_count();

    // resize the temp buffer to m_logical_block_size
    void resize_temp_buffer();

    // open the underlying iso file
    bool open_file();

    // read the PVD into m_volume_descriptor
    bool open_primary_volume_descriptor();

    // open the path table
    bool open_path_table();
  };
}

extern iso9660::file::ptr_type g_iso_file;

template<>
struct fmt::formatter<iso9660::file::path_entry> : formatter<std::string_view>
{
  auto format(const iso9660::file::path_entry& path_entry, format_context& ctx)
  {
    constexpr std::string_view tpl =
    {
      "path_entry(path: {}, table: {})"
    };

    return fmt::format_to(ctx.out(), tpl, path_entry.path, path_entry.table);
  }
};
