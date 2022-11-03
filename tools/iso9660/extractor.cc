#include "common/log.h"
#include "common/debug.h"
#include "common/scoped_function.h"

#include "extractor.h"

// TODO: This is really messy. I wrote it in kind of a rush because I couldn't find a library that did exactly what I wanted.
// In the end I resolved to writing my own iso extracter which honestly was a bigger pain in the ass than I had hoped.
// Google ECMA 119. I referenced the sections of the spec when I could remember to. There will be quite a few missing.
// The spec however isn't that long and it's not hard to follow. The main issue is this standard kind of sucks and was clearly
// written for C with zero length arrays and everything is 1 indexed for some reason I can't understand.
//
// This is largely untested for anything but the DC2 ISO right now. I'll give it another look when my eyes aren't bleeding.
// I never want to write an iso reader again

set_log_channel("ExtractISO");

namespace iso9660
{
  extractor::extractor(std::string_view file)
    :m_file_path{ file }
  {
    resize_temp_buffer();
  }

  extractor::~extractor()
  {
    close_iso_file();
  }

  extractor::ptr extractor::open(std::string_view file)
  {
    auto out = std::make_unique<extractor>(file);

    if (!out)
    {
      log_error("Failed to allocate file.");

      return nullptr;
    }

    if (!out->open_iso_file())
    {
      log_error("Failed to open ISO file.");

      return nullptr;
    }

    // get the size of the iso in bytes
    const auto iso_size = out->get_iso_size();

    if (!iso_size)
    {
      log_error("Failed to get the size of the iso");

      return nullptr;
    }

    // find the size of the iso in sectors for now
    // the pvd will tell us the actual sector size and count
    out->m_max_sectors = *iso_size / constants::assumed_sector_size;

    // read out the primary volume descriptor
    // we need some sense of an LBA so we assume 2048 until we read it from here
    if (!out->read_primary_volume_descriptor())
    {
      log_error("Failed to find the primary volume descriptor. The file is likely corrupt.");

      return nullptr;
    }

    // read out the path table
    // this gets us a list of directories in the iso
    if (!out->open_path_table())
    {
      log_error("Failed to open path table.");

      return nullptr;
    }

    return out;
  }

  bool extractor::extract_file(std::string_view iso_file_path, std::string_view to)
  {
    auto parent_dir = common::file_helpers::parent_directory(iso_file_path);;

    auto dir_itr = std::find_if(m_directory_records.begin(), m_directory_records.end(), [&](const directory& dir) {
      // special case (root)
      if (!parent_dir.size() && dir.root)
        return true;

      if (dir.name == parent_dir)
        return true;

      return false;
    });

    if (dir_itr == m_directory_records.end())
      return false;

    std::string dir_name = dir_itr->name;
    if (dir_itr->root)
      dir_name = "[root]";

    log_info("Searching {}", dir_name);

    const auto files = read_directory_descriptor(*dir_itr);

    if (!files)
      return false;

    const auto file_itr = std::find_if(files->begin(), files->end(), [&](const file& file_info) {
      if (file_info.path == iso_file_path)
        return true;

      return false;
    });

    if (file_itr == files->end())
      return false;

    log_info("  {}", file_itr->path);

    if (!extract_file_to(*file_itr, to))
      return false;

    return true;
  }

  bool extractor::extract_directory(std::string_view iso_file_path, std::string_view to)
  {
    const auto itr = std::find_if(m_directory_records.begin(), m_directory_records.end(), [&](const directory& dir) {
      // special case (root)
      if (dir.root && (iso_file_path == "/" || iso_file_path == "." || iso_file_path == "\\"))
        return true;

      if (dir.name == iso_file_path)
        return true;

      return false;
    });

    if (itr == m_directory_records.end())
      return false;

    log_info("Extracting Directory: {}", itr->name);
    const auto files = read_directory_descriptor(*itr);

    if (!files)
      return false;

    for (const auto& file_entry : *files)
    {
      log_info("  {}", file_entry.path);

      if (!extract_file_to(file_entry, to))
        return false;
    }

    return true;
  }

  bool extractor::open_iso_file()
  {
    log_info("Opening ISO");

    if (!common::file_helpers::open_native(&m_file_handle, m_file_path, "rb"))
      return false;

    return true;
  }

  void extractor::close_iso_file()
  {
    log_info("Closing ISO");

    if (m_file_handle)
      fclose(m_file_handle);

    m_file_handle = nullptr;
  }

  std::optional<usize> extractor::get_iso_size()
  {
    if (!iso_seek(0, SEEK_END))
      return std::nullopt;

    return iso_tell();
  }

  void extractor::resize_temp_buffer()
  {
    log_info("Resizing temp buffer to {}", m_sector_size);
    m_temp_buff = std::make_unique<u8[]>(m_sector_size);
  }

  bool extractor::read_sector(usize sector_num)
  {
    if (sector_num > m_max_sectors)
      return false;

    if (!iso_seek(get_fpos_for_sector(sector_num), SEEK_SET))
    {
      log_error("Error: could not seek to sector {}", sector_num);

      return false;
    }

    // read one sector to the buffer
    const auto size = fread(&m_temp_buff[0], m_sector_size, 1, m_file_handle);

    // we read exactly 1 2048 buffer
    if (size < 1)
    {
      log_error("Error: Failed to read {} bytes into temp buffer", m_sector_size);

      return false;
    }

    return true;
  }

  bool extractor::read_primary_volume_descriptor()
  {
    log_info("Reading primary volume descriptor");

    // ECMA 6.2.1
    // the first 15 LBAs are for system use
    // skip to the data area
    if (!seek_sector(constants::data_lba_start))
      return false;

    if (!read_current_sector_to_temp())
      return false;

    volume_descriptor_base vol = {};
    if (!temp_copy_buffer(&vol, 0, sizeof(vol)))
      return false;

    // make sure we have the PVD
    if (strncmp(vol.header.magic, volume_descriptor_primary::magic_id, 5) != 0 || vol.header.type != volume_descriptor_types::vd_primary)
      return false;

    m_primary_volume_descriptor = std::move(std::bit_cast<volume_descriptor_primary>(vol));

    m_sector_size = deget(m_primary_volume_descriptor.logical_block_size);
    m_max_sectors = deget(m_primary_volume_descriptor.volume_space_size);

    // resize the temp buffer to the new sector size
    // note: this deletes the current temp buffer so it must be done after we get everything we need
    if (m_sector_size != constants::assumed_sector_size)
      resize_temp_buffer();

    return true;
  }

  std::optional<std::vector<extractor::file>> extractor::read_directory_descriptor(const directory& dir)
  {
    if (!seek_sector(dir.directory_record_lba))
      return std::nullopt;

    if (!read_current_sector_to_temp())
      return std::nullopt;

    dirent desc{ };
    if (!temp_copy_buffer(&desc, 0, sizeof(dirent)))
      return std::nullopt;

    const auto length = deget(desc.file_section_length);

    usize current_off = desc.bytes;
    usize i = 0;

    std::vector<file> files;
    while (current_off < length)
    {
      if (!temp_copy_buffer(&desc, current_off, sizeof(dirent)))
        return std::nullopt;

      std::string name;
      name.resize(desc.name_length);

      if (!temp_copy_buffer(name.data(), current_off + sizeof(dirent) - 1, desc.name_length))
        return std::nullopt;

      current_off += desc.bytes;

      if (desc.flags & dirent::file_flags::file_flag_direcrtory)
        continue;

      // special directory names (.) and (..)
      if (!name.empty() && (desc.name[0] == '\1' || desc.name[0] == '\0'))
        continue;

      if (!dir.name.empty())
        name = common::file_helpers::append(dir.name, name);

      // trim off the version thingy
      auto colonpos = name.find_last_of(";");
      if (colonpos)
        name = name.substr(0, colonpos);

      file file_info
      {
        .path = std::move(name),
        .file_record_lba = deget(desc.extent_logical_block_number),
        .size = deget(desc.file_section_length),
      };

      files.push_back(std::move(file_info));
    }

    return files;
  }

  bool extractor::open_path_table()
  {
    log_info("Opening path table");

    if (!seek_sector(deget(m_primary_volume_descriptor.path_table_lba).table))
      return false;

    if (!read_current_sector_to_temp())
      return false;

    usize current_off = 0;
    for (usize i = 0; current_off < deget(m_primary_volume_descriptor.path_table_size); ++i)
    {
      path_table_entry pt{ };
      if (!temp_copy_buffer(&pt, current_off, sizeof(path_table_entry)))
        return false;

      const auto name_string_size = pt.name_length;

      std::string name{ };
      name.resize(name_string_size);

      if (!temp_copy_buffer(name.data(), current_off + sizeof(path_table_entry), name_string_size))
        return false;

      usize total_entry_size = sizeof(path_table_entry) + pt.name_length;

      // if not even, pad 1
      if (total_entry_size & 1)
        total_entry_size++;

      if (!name.empty() && name[0] == '\0')
        name = "";

      current_off += total_entry_size;

      log_info("  {}", name.c_str());
      log_info("    extended attributes length: {}", pt.extended_attributes_length);
      log_info("    extent:                     {}", pt.extent);
      log_info("    name length:                {}", pt.name_length);
      log_info("    parent:                     {}", pt.parent);

      // build the path name
      usize parent = pt.parent;
      while (parent > 1) // 1 is root
      {
        name = common::file_helpers::append(m_directory_records[--parent].name, name);
        parent = m_directory_records[--parent].parent;
      }

      directory dir
      {
        .name = std::move(name),
        .directory_record_lba = pt.extent,
        .parent = pt.parent,
        .root = dir.name.empty()
      };

      m_directory_records.push_back(std::move(dir));
    }

    return true;
  }

  bool extractor::extract_file_to(const file& file_entry, std::string_view to)
  {
    std::string output_path = common::file_helpers::append(to, file_entry.path);

    const auto remainder = file_entry.size % m_sector_size;
    auto sector_count = file_entry.size / m_sector_size;

    // read an extra sector
    if (remainder)
      sector_count++;

    auto sector = file_entry.file_record_lba;
    auto tmp = std::make_unique<u8[]>(m_sector_size);

    std::FILE* output_file;
    if (!common::file_helpers::open_native(&output_file, output_path, "w+b"))
      return false;

    common::scoped_function([&]() {
      fclose(output_file);
    });

    for (usize i = 0; i < sector_count; ++i)
    {
      const auto current_sector = sector + i;

      if (!seek_sector(current_sector))
        return false;

      if (!read_current_sector_to_temp())
        return false;

      auto read_size = m_sector_size;

      if (remainder && i == sector_count - 1)
        read_size = remainder;

      if (!temp_copy_buffer(&tmp[0], 0, read_size))
        return false;

      if (fwrite(&tmp[0], m_sector_size, 1, output_file) != 1)
        return false;
    }

    return true;
  }
}
