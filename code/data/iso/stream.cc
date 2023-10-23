#include "common/bits.h"
#include "common/file_helpers.h"
#include "common/log.h"

#include "data/iso/stream.h"
#include "data/iso/dual_endian.h"

set_log_channel("iso9660");

namespace data
{
  static inline std::string_view trim_version_id(std::string_view s)
  {
    const auto pos = s.find_last_of(';');

    if (pos == std::string_view::npos)
      return s;

    return s.substr(0, pos);
  }

  iso_stream::iso_stream(std::string_view path, std::unique_ptr<common::data_stream_base> stream)
    : m_file_stream{ std::move(stream) }
    , m_iso_file_path{ std::string{path} }
    , m_logical_block_size{ iso_default_sector_size }
    , m_logical_block_count{ m_file_stream->size() / iso_default_sector_size }
  {
  }

  iso_stream::~iso_stream() = default;

  std::unique_ptr<iso_stream> iso_stream::open(std::string_view path)
  {
    log_info("Opening iso file {}", path);

    auto iso_file_stream = common::file_stream::open(path, "rb");

    if (!iso_file_stream)
    {
      log_error("Failed to open data stream for iso");

      return nullptr;
    }

    auto out = std::make_unique<iso_stream>(path, std::move(iso_file_stream));

    if (!out->open_primary_volume_descriptor())
    {
      log_error("Failed to open primary volume descriptor");

      return nullptr;
    }

    if (!out->open_path_table())
    {
      log_error("Failed to open path table");

      return nullptr;
    }

    return out;
  }

  void iso_stream::seek_to_logical_block(u64 logical_block_address)
  {
    log_trace("Seeking to logical block {}", logical_block_address);

    if (logical_block_address > m_logical_block_count)
      panicf("Tried to seek to logical block {} but there are only {}", logical_block_address, m_logical_block_count);

    m_current_logical_block = logical_block_address;

    if (!m_file_stream->seek(logical_block_address * m_logical_block_size))
      panicf("Failed to seek to logical block {}", logical_block_address);
  }

  void iso_stream::seek_relative_to_logical_block(u64 byte_offset)
  {
    seek_to_logical_block(m_current_logical_block);

    if (!m_file_stream->seek_relative(byte_offset))
      panicf("Failed to seek to byte {} of logical block {}", byte_offset, m_current_logical_block);
  }

  bool iso_stream::open_primary_volume_descriptor()
  {
    log_info("Searching for primary volume descriptor at logical block {}", iso_data_start_logical_block_address);

    // ECMA 6.2.1
    // everything before this is application defined data
    // the spec reserves the first 15 LBAs for that purpose
    seek_to_logical_block(iso_data_start_logical_block_address);

    // ECMA 8.1
    // start with a base descriptor
    // this just has the required fields needed to check the type and magic\
    //
    // this descriptor happens to be 1 logical block in size
    iso_volume_descriptor_base base{ };
    if (!m_file_stream->read_buffer_checked(&base, sizeof(iso_volume_descriptor_base)))
    {
      log_error("Failed to read volume descriptor block");

      return false;
    }

    // EMCA 8.3.2
    // make sure the magic is right
    if (strncmp(base.header.magic, iso_primary_volume_magic_id, 5) != 0)
    {
      log_error("Block magic doesn't match primary volume descriptor");

      return false;
    }

    // ECMA 8.3.1
    // now make sure it's a primary volume deescriptor type
    // there are other types (secondary, partition, etc) but I did not write support for them
    if (base.header.type != iso_volume_descriptor_type::vd_primary)
    {
      log_error("Descriptor type doesn't match primary volume type");

      return false;
    }

    m_volume_descriptor = std::move(std::bit_cast<iso_volume_descriptor_primary>(base));

    // cache a few useful values
    m_logical_block_size  = iso_get_native_endian(m_volume_descriptor.logical_block_size);
    m_logical_block_count = iso_get_native_endian(m_volume_descriptor.volume_space_size);

    log_info("Logical block size (bytes): {}", m_logical_block_size);
    log_info("Number of logical blocks:   {}", m_logical_block_count);

    return true;
  }

  bool iso_stream::open_path_table()
  {
    const auto path_table_total_byte_count = iso_get_native_endian(m_volume_descriptor.path_table_size);

    // zero length path table
    if (!path_table_total_byte_count)
    {
      log_error("The path table was 0 bytes");

      return false;
    }

    log_info("Opening path table {} bytes", path_table_total_byte_count);

    seek_to_logical_block(iso_get_native_endian(m_volume_descriptor.path_table_lba).table);

    u64 path_table_byte_offset = 0;
    while (path_table_byte_offset < path_table_total_byte_count)
    {
      iso_path_table_entry current_path_table_entry;
      if (!m_file_stream->read_buffer_checked(&current_path_table_entry, sizeof(iso_path_table_entry)))
      {
        log_error("Failed to read path table entry");

        return false;
      }

      // the size of the string following the entry
      const auto path_string_byte_count = current_path_table_entry.name_length;

      // we need the total size of the entry plus the string
      // this way we get the next path table entry and not the string following this entry
      auto total_entry_byte_count = sizeof(iso_path_table_entry) + path_string_byte_count;

      std::string file_iso_relative_path;
      file_iso_relative_path.resize(path_string_byte_count);

      if (!m_file_stream->read_buffer_checked(file_iso_relative_path.data(), path_string_byte_count))
      {
        log_error("Failed to read path table path string");

        return false;
      }

      m_file_stream->seek_relative(total_entry_byte_count & 1);

      // special root case
      if (!file_iso_relative_path.empty() && file_iso_relative_path[0] == '\0')
        file_iso_relative_path = "";

      path_entry entry
      {
        .path  = std::move(file_iso_relative_path),
        .table = std::move(current_path_table_entry)
      };

      // if it's not even we need to pad so it is
      // this possible 1 byte pad is required by the spec
      path_table_byte_offset += common::align_up(total_entry_byte_count, 2);

      log_info("--> {}", entry);

      m_paths.push_back(std::move(entry));
    }

    return true;
  }

  iso_stream::directory_list iso_stream::directories()
  {
    log_info("Reading {} directory records", m_paths.size());

    directory_list list;
    for (u64 i = 0; i < m_paths.size(); ++i)
    {
      const auto& path = m_paths[i];
      const auto logical_block_address = path.table.extent;

      // it's 1 indexed because this standard is ridiculous
      auto parent = path.table.parent - 1;

      std::string full_path{ };

      // construct the full path by looking up the parents till we reach root
      while (parent > 0)
      {
        full_path = common::file_helpers::append(m_paths[parent].path, full_path);
        parent = m_paths[parent].table.parent - 1;
      }

      full_path = common::file_helpers::append(full_path, path.path);

      directory_entry entry =
      {
        .path                  = std::move(full_path),
        .logical_block_address = logical_block_address,
        .entry                 = path,
      };

      log_info("--> {}", entry);

      list.push_back(std::move(entry));
    }

    return list;
  }

  iso_stream::file_list iso_stream::files_for_directory(std::string_view dir_path)
  {
    log_info("Searching for entry records for {}", dir_path);

    directory_list directory_list = directories();

    const auto& itr = std::find_if(directory_list.begin(), directory_list.end(), [&](const directory_entry& entry) {
      if (entry.path == dir_path)
        return true;

      return false;
    });

    if (itr == directory_list.end())
    {
      log_warn("Directory not found {}", dir_path);

      return {};
    }

    const auto entry_record_logical_block_address = itr->logical_block_address;

    log_info("Entry records found at logical block address {}", entry_record_logical_block_address);

    seek_to_logical_block(entry_record_logical_block_address);

    iso_dirent dir{ };
    if (!m_file_stream->read_buffer_checked(&dir, sizeof(iso_dirent)))
    {
      log_error("Failed to read directory record at logical block address {}", entry_record_logical_block_address);

      return {};
    }

    const auto record_byte_count            = iso_get_native_endian(dir.file_section_length);
    const auto record_logical_block_address = iso_get_native_endian(dir.extent_logical_block_number);

    seek_to_logical_block(record_logical_block_address);

    u64 directory_record_byte_offset = 0;
    file_list list{ };

    while (directory_record_byte_offset < record_byte_count)
    {
      if (!m_file_stream->read_buffer_checked(&dir, sizeof(iso_dirent)))
      {
        log_error("Failed to read directory entry");

        break;
      }

      const auto entry_iso_relative_path_byte_count = dir.name_length;

      std::string entry_iso_relative_path{ };
      entry_iso_relative_path.resize(entry_iso_relative_path_byte_count);

      if (!m_file_stream->read_buffer_checked(entry_iso_relative_path.data(), entry_iso_relative_path_byte_count))
      {
        log_error("Failed to read directory entry path");

        break;
      }

      const usize remaining_bytes = dir.bytes - (sizeof(iso_dirent) + entry_iso_relative_path_byte_count);
      m_file_stream->seek_relative(remaining_bytes);

      directory_record_byte_offset += dir.bytes;

      if (dir.flags & iso_dirent::file_flag_directory)
        continue;

      const auto entry_logical_block_address = iso_get_native_endian(dir.extent_logical_block_number);
      const auto entry_total_bytes           = iso_get_native_endian(dir.file_section_length);

      file_entry entry =
      {
        .path                  = common::file_helpers::append(dir_path, trim_version_id(entry_iso_relative_path)),
        .logical_block_address = entry_logical_block_address,
        .total_bytes           = entry_total_bytes
      };

      log_info("--> {}", entry);

      list.push_back(std::move(entry));
    }

    return list;
  }

  bool iso_stream::copy_logical_block_to_buffer(void* buff)
  {
    return m_file_stream->read_buffer_checked(buff, m_logical_block_size);
  }

  bool iso_stream::copy_bytes_to_buffer(void* buff, usize size)
  {
    return m_file_stream->read_buffer_checked(buff, size);
  }

  bool iso_stream::copy_file_entry_to_stream(const file_entry& entry, common::data_stream_base* stream)
  {
    if (!stream->seek_to_start())
      return false;

    seek_to_logical_block(entry.logical_block_address);

    usize write_size = common::data_stream_base::block_size;

    std::array<u8, common::data_stream_base::block_size> temp_buffer{ };

    usize bytes_written = 0;
    while (bytes_written < entry.total_bytes)
    {
      if (bytes_written + write_size > entry.total_bytes)
      {
        write_size = entry.total_bytes - bytes_written;

        log_trace("Unaligned block write {} bytes instead of {}", write_size, common::data_stream_base::block_size);
      }

      if (!m_file_stream->read_buffer_checked(temp_buffer.data(), write_size))
        return false;

      if (!stream->write_buffer_checked(temp_buffer.data(), write_size))
        return false;

      bytes_written += write_size;
    }

    return true;
  }

  bool iso_stream::copy_bytes_to_stream(common::data_stream_base* stream, usize size)
  {
    if (!stream->seek_to_start())
      return false;

    usize write_size = common::data_stream_base::block_size;

    std::array<u8, common::data_stream_base::block_size> temp_buffer{ };

    usize bytes_written = 0;
    while (bytes_written < size)
    {
      if (bytes_written + write_size > size)
        write_size = size - bytes_written;

      if (!m_file_stream->read_buffer_checked(temp_buffer.data(), write_size))
        return false;

      if (!stream->write_buffer_checked(temp_buffer.data(), write_size))
        return false;

      bytes_written += write_size;
    }

    return true;
  }
}
