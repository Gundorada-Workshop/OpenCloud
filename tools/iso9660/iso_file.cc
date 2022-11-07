#include "iso_file.h"

#include "common/alignment.h"
#include "common/file_helpers.h"
#include "common/log.h"

set_log_channel("ISO9660");

namespace iso9660
{
  using namespace common;

  static inline std::string_view trim_version_id(std::string_view s)
  {
    const auto pos = s.find_last_of(';');

    if (pos == std::string_view::npos)
      return s;

    return s.substr(0, pos);
  }

  file::file() = default;

  file::~file()
  {
    log_info("Cleanup");

    if (m_file)
      fclose(m_file);
  }

  std::optional<usize> file::get_file_byte_count()
  {
    const auto current_position = file_helpers::tell64(m_file);

    if (!file_helpers::seek64(m_file, 0, SEEK_END))
      return std::nullopt;

    const auto end = file_helpers::tell64(m_file);

    if (!file_helpers::seek64(m_file, current_position, SEEK_SET))
      return std::nullopt;

    return end;
  }

  void file::resize_temp_buffer()
  {
    log_info("Resize buffer to {}", m_logical_block_size);

    m_temp_buffer = std::make_unique<u8[]>(m_logical_block_size);
  }

  bool file::open_file()
  {
    log_info("Open {}", m_path);

    return file_helpers::open_native(&m_file, m_path, "rb");
  }

  bool file::copy_data_from_block(u64 logical_block_address, u8* buff)
  {
    //log_info("Read {} logical blocks {} bytes", size, real_size);
    seek_block(logical_block_address);
    std::memcpy(buff, &m_temp_buffer[0], m_logical_block_size);

    return true;
  }

  void file::seek_block(u64 logical_block_address)
  {
    if (logical_block_address > m_logical_block_count)
      panicf("Tried to seek to logical block {} but there are only {}", logical_block_address, m_logical_block_count);

    m_current_logical_block = logical_block_address;

    const auto real_file_pos = logical_block_address * m_logical_block_size;

    if (!file_helpers::seek64(m_file, real_file_pos, SEEK_SET))
      panicf("Failed to seek to logical block {}", logical_block_address);

    if (fread(&m_temp_buffer[0], m_logical_block_size, 1, m_file) != 1)
      panicf("Failed to read logical block {}", logical_block_address);
  }

  u64 file::tell_block()
  {
    return file_helpers::tell64(m_file) * m_logical_block_size;
  }

  bool file::open_primary_volume_descriptor()
  {
    // ECMA 6.2.1
    // everything before this is application defined data
    // the spec reserves the first 15 LBAs for that purpose
    //
    // ECMA 8.1
    // start with a base descriptor
    // this just has the required fields needed to check the type and magic\
    //
    // this descriptor happens to be 1 logical block in size
    volume_descriptor_base base{ };
    copy_data_from_block(constants::data_lba_start, reinterpret_cast<u8*>(&base));

    // EMCA 8.3.2
    // make sure the magic is right
    if (strncmp(base.header.magic, iso9660::volume_descriptor_primary::magic_id, 5) != 0)
      return false;

    // ECMA 8.3.1
    // now make sure it's a primary volume deescriptor type
    // there are other types (secondary, partition, etc) but I did not write support for them
    if (base.header.type != iso9660::volume_descriptor_types::vd_primary)
      return false;

    m_volume_descriptor = std::move(std::bit_cast<volume_descriptor_primary>(base));

    // cache a few useful values
    m_logical_block_size = deget(m_volume_descriptor.logical_block_size);
    m_logical_block_count = deget(m_volume_descriptor.volume_space_size);

    // if the iso uses a logical block size different than 2048 we need to resize out buffer
    // warning: this destroys the current buffer. so get all the data we need before this.
    if (m_logical_block_size != constants::assumed_sector_size)
      resize_temp_buffer();

    return true;
  }

  bool file::open_path_table()
  {
    const auto entry_bytes = deget(m_volume_descriptor.path_table_size);

    // zero length path table
    if (!entry_bytes)
    {
      log_error("The path table was 0 bytes");

      return false;
    }

    log_info("Opening path table {} bytes", entry_bytes);

    const auto entry_block_address = deget(m_volume_descriptor.path_table_lba).table;

    seek_block(entry_block_address);

    u64 offset = 0;
    while (offset < entry_bytes)
    {
      constexpr auto path_table_type_bytes = sizeof(path_table_entry);

      path_table_entry table_entry{ };

      std::memcpy(&table_entry, &m_temp_buffer[offset], path_table_type_bytes);

      const auto name_bytes = table_entry.name_length;
      auto total_entry_bytes = path_table_type_bytes + name_bytes;

      std::string path{ };
      path.resize(name_bytes);

      std::memcpy(path.data(), &m_temp_buffer[offset + path_table_type_bytes], name_bytes);

      // root
      if (!path.empty() && path[0] == '\0')
        path = "";

      path_entry entry
      {
        .path = std::move(path),
        .table = std::move(table_entry)
      };

      // if it's not even we need to pad so it is
      total_entry_bytes = align_up(total_entry_bytes, 2);

      offset += total_entry_bytes;

      log_info("  {}", entry);

      m_paths.push_back(std::move(entry));
    }

    return true;
  }

  file::directory_list file::get_directories()
  {
    log_info("Reading {} directory records", m_paths.size());

    directory_list list{ };
    for (u64 i = 0; i < m_paths.size(); ++i)
    {
      const auto& path = m_paths[i];
      const auto logical_block_address = path.table.extent;

      auto parent = path.table.parent - 1;

      std::string full_path{ };

      // construct the full path by looking up the parents till we reach root
      while (parent > 0)
      {
        full_path = file_helpers::append(m_paths[parent].path, full_path);
        parent = m_paths[parent].table.parent - 1;
      }

      full_path = file_helpers::append(full_path, path.path);

      directory_entry entry =
      {
        .path = std::move(full_path),
        .logical_block_address = logical_block_address,
        .entry = path,
      };

      list.push_back(std::move(entry));
    }

    return list;
  }

  file::file_list file::get_files_for_directory(std::string_view dir_path)
  {
    directory_list directory_list = get_directories();

    const auto& itr = std::find_if(directory_list.begin(), directory_list.end(), [&](const directory_entry& entry) {
      if (entry.path == dir_path)
        return true;

      return false;
    });

    if (itr == directory_list.end())
      return {};

    seek_block(itr->logical_block_address);

    dirent dir{ };
    memcpy(&dir, &m_temp_buffer[0], sizeof(dirent));

    const auto directory_record_length = deget(dir.file_section_length);
    const auto directory_record_logical_block_address = deget(dir.extent_logical_block_number);

    seek_block(directory_record_logical_block_address);

    u64 offset = 0;
    file_list list{ };

    while (offset < directory_record_length)
    {
      std::memcpy(&dir, &m_temp_buffer[offset], sizeof(dirent));

      std::string name{ };
      name.resize(dir.name_length);

      std::memcpy(name.data(), &m_temp_buffer[offset + sizeof(dirent)], dir.name_length);

      offset += dir.bytes;

      if (dir.flags & dirent::file_flag_directory)
        continue;

      const auto logical_block_number = deget(dir.extent_logical_block_number);
      const auto file_size = deget(dir.file_section_length);

      file_entry entry =
      {
        .path = file_helpers::append(dir_path, trim_version_id(name)),
        .logical_block_address = logical_block_number,
        .logical_block_count = file_size / m_logical_block_size,
        .extra_bytes = file_size % m_logical_block_size
      };

      list.push_back(std::move(entry));
    }

    return list;
  }

  file::ptr_type file::open(std::string_view path)
  {
    auto out = std::make_unique<file>();

    out->m_path = std::string{ path };

    // take a guess as to the byte coutn of the logical blocks
    // in practice it's usually 2048 anyway
    out->m_logical_block_size = constants::assumed_sector_size;

    // set up our temp buffer with our assumed size
    out->resize_temp_buffer();

    if (!out->open_file())
      return nullptr;

    const auto total_file_bytes = out->get_file_byte_count();

    if (!total_file_bytes)
      return nullptr;

    // take a guess as to the total number of logcal blocks for now
    // when we find the PVD we will know the actual block size and count
    // in practice it's usually this anyway
    out->m_logical_block_count = *total_file_bytes / out->m_logical_block_size;

    if (!out->open_primary_volume_descriptor())
      return nullptr;

    if (!out->open_path_table())
      return nullptr;

    return out;
  }
}

iso9660::file::ptr_type g_iso_file{ };
