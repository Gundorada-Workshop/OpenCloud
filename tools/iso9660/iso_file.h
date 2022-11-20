#pragma once
#include <optional>

#include "common/strings.h"
#include "common/types.h"
#include "common/data_stream.h"

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
      u64 total_bytes{ 0 };
      iso9660::dirent entry{ };
    };

    using path_list = std::vector<path_entry>;
    using directory_list = std::vector<directory_entry>;
    using file_list = std::vector<file_entry>;

    // ctor
    file(std::string_view path, std::unique_ptr<common::data_stream_base> stream);

    // dtor
    ~file();

  public:
    // open an iso file
    static std::unique_ptr<file> open(std::string_view path);

    // close an iso file
    void close();

    // seek to lba
    void seek_to_logical_block(u64 logical_block_address);

    void seek_relative_to_logical_block(u64 byte_offset);

    // get a list of directories
    directory_list directories();

    // get a list of files in a directory
    file_list files_for_directory(std::string_view dir_path);

  public:
    // copy a logical block
    // caller is responsible for making sure buff is current_logical_block_size()
    bool copy_logical_block_to_buffer(void* buff);

    // write bytes to a stream
    bool copy_bytes_to_stream(common::data_stream_base* stream, usize count);

    // write bytes to a buffer
    bool copy_bytes_to_buffer(void* buff, usize size);

    // copy a file out to stream
    bool copy_file_entry_to_stream(const file_entry& entry, common::data_stream_base* stream);

    // get the LBA size in bytes
    inline u64 logical_block_size() const
    {
      return m_logical_block_size;
    }

    // get the path to the iso file
    inline std::string_view iso_file_path()
    {
      return m_iso_file_path;
    }

    // get the current LBA
    inline u64 current_logical_block_address()
    {
      return m_file_stream->pos() * m_logical_block_size;
    }

  private:
    // current path to the iso
    std::string m_iso_file_path{ };

    // c file handle for the iso
    std::unique_ptr<common::data_stream_base> m_file_stream;

    // logical block size
    u64 m_logical_block_size{ 0 };

    // number of logical blocks
    u64 m_logical_block_count{ 0 };

    // current block pointer
    u64 m_current_logical_block{ 0 };

    // primary volume descriptor
    volume_descriptor_primary m_volume_descriptor{ };

    // path table list
    path_list m_paths{ };

  private:
    // read the PVD into m_volume_descriptor
    bool open_primary_volume_descriptor();

    // open the path table
    bool open_path_table();
  };
}

extern std::unique_ptr<iso9660::file> g_iso_file;

template<>
struct fmt::formatter<iso9660::file::path_entry> : formatter<std::string_view>
{
  auto format(const iso9660::file::path_entry& entry, format_context& ctx)
  {
    constexpr std::string_view tpl =
    {
      "path_entry(path: {}, table: {})"
    };

    return fmt::format_to(ctx.out(), tpl, entry.path, entry.table);
  }
};

template<>
struct fmt::formatter<iso9660::file::directory_entry> : formatter<std::string_view>
{
  auto format(const iso9660::file::directory_entry& entry, format_context& ctx)
  {
    constexpr std::string_view tpl =
    {
      "path_entry(path: {}, lba: {})"
    };

    std::string path = entry.path.empty() ? "." : entry.path;

    return fmt::format_to(ctx.out(), tpl, path, entry.logical_block_address);
  }
};

template<>
struct fmt::formatter<iso9660::file::file_entry> : formatter<std::string_view>
{
  auto format(const iso9660::file::file_entry& entry, format_context& ctx)
  {
    constexpr std::string_view tpl =
    {
      "path_entry(path: {}, lba: {}, size: {})"
    };

    return fmt::format_to(ctx.out(), tpl, entry.path, entry.logical_block_address, entry.total_bytes);
  }
};
