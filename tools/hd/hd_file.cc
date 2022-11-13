#include "common/log.h"

#include "hd_file.h"

set_log_channel("HDXFile")

namespace hd
{
  using namespace common;

  file::file(iso9660::file::file_entry entry)
  {
    if (strings::lowercase(file_helpers::ext(entry.path)) == "hd2")
      m_file_type = file_type::hd2_file;

    if (strings::lowercase(file_helpers::ext(entry.path)) == "hd3")
      m_file_type = file_type::hd3_file;

    m_descriptor_file_entry = std::move(entry);

    const auto iso_logical_block_byte_count = g_iso_file->get_logical_block_size();
    m_logical_block_temp_buffer = std::make_unique<u8[]>(iso_logical_block_byte_count);
  }

  file::~file() = default;

  bool file::find_data_file()
  {
    const std::string_view descriptor_file_path        = m_descriptor_file_entry.path;
    const std::string_view descriptor_file_name        = file_helpers::basename(descriptor_file_path);
    const std::string_view descriptor_parent_directory = file_helpers::parent_directory(descriptor_file_path);

    const std::string data_file_path  = file_helpers::append(descriptor_parent_directory, descriptor_file_name) + ".DAT";

    auto iso_directory_file_list = g_iso_file->get_files_for_directory(descriptor_parent_directory);

    auto itr = std::find_if(iso_directory_file_list.begin(), iso_directory_file_list.end(), [&](const iso9660::file::file_entry& file_entry) {
      if (file_entry.path == data_file_path)
        return true;

      return false;
    });

    if (itr == iso_directory_file_list.end())
    {
      log_info("Unable to find DATA file for HD data descriptor");

      return false;
    }

    m_data_file_entry = std::move(*itr);

    return true;
  }

  hdx_file_entry_list file::get_entries_for_descriptor_table_block_offset(u64 block_offset)
  {
    if (block_offset > m_descriptor_file_table_end_logical_block_offset)
      return {};

    switch (m_file_type)
    {
    case file_type::hd2_file:
      return read_hd2_file_entries_for_offset(block_offset);
    case file_type::hd3_file:
      return read_hd3_file_entries_for_offset(block_offset);
    }

    return {};
  }

  std::string file::read_entry_label(u64 block_offset, u64 byte_offset)
  {
    const auto logical_block_byte_count = g_iso_file->get_logical_block_size();

    const u64 descriptor_file_logical_block_start = m_descriptor_file_entry.logical_block_address;
    const auto label_logical_block_start = descriptor_file_logical_block_start + block_offset;

    g_iso_file->copy_data_from_block(label_logical_block_start, &m_logical_block_temp_buffer[0]);

    const char* s = std::bit_cast<char*>(&m_logical_block_temp_buffer[byte_offset]);

    // don't run off the end off the buffer
    // if we hit the end we need to pull out the next block
    auto string_length = strnlen_s(s, logical_block_byte_count - byte_offset);

    std::string label{ };
    label.resize(string_length);

    // copy the string out for far
    std::memcpy(label.data(), &m_logical_block_temp_buffer[byte_offset], string_length);

    // we ran off the end of the buffer
    // so let's pull in another to complete the string
    if (byte_offset + string_length == logical_block_byte_count && s[string_length] != '\0')
    {
      log_warn("HDX label offset {} out of range of logical block byte size {}", byte_offset, logical_block_byte_count);

      g_iso_file->copy_data_from_block(label_logical_block_start + 1, &m_logical_block_temp_buffer[0]);

      s = std::bit_cast<char*>(&m_logical_block_temp_buffer[0]);
      auto remaining_characters = strnlen_s(s, logical_block_byte_count);

      std::string temp{ };
      temp.resize(remaining_characters);

      std::memcpy(temp.data(), &m_logical_block_temp_buffer[0], remaining_characters);

      label += temp;
    }

    log_info("{} {} ----> {}", m_data_file_entry.path, m_descriptor_file_entry.path, label);

    return label;
  }

  hdx_file_entry_list file::read_hd2_file_entries_for_offset(u64 block_offset)
  {
    u64 current_logical_block_byte_offset = 0;
    const u64 descriptor_file_logical_block_start = m_descriptor_file_entry.logical_block_address;
    const u64 data_file_logical_block_start = m_data_file_entry.logical_block_address;

    const u64 current_descriptor_file_logical_block_address = descriptor_file_logical_block_start + block_offset;

    const auto logical_block_byte_count = g_iso_file->get_logical_block_size();

    hdx_file_entry_list file_entry_list{ };
    while (current_logical_block_byte_offset < logical_block_byte_count)
    {
      hd::file_descriptor desc{ };

      g_iso_file->copy_data_from_block(current_descriptor_file_logical_block_address, &m_logical_block_temp_buffer[0]);
      std::memcpy(&desc, &m_logical_block_temp_buffer[current_logical_block_byte_offset], hd::constants::hd2_size);

      const auto label_logical_block_offset      = desc.hd2.name_location / logical_block_byte_count;
      const auto label_logical_block_byte_offset = desc.hd2.name_location % logical_block_byte_count;
      const auto label_logical_block_start       = current_descriptor_file_logical_block_address + label_logical_block_offset;

      unused_v(label_logical_block_start);

      const auto data_logical_block_address = data_file_logical_block_start + desc.hd2.logical_block_address;
      const auto data_logical_block_count   = desc.hd2.size / logical_block_byte_count;
      const auto data_remaining_bytes_count = desc.hd2.size % logical_block_byte_count;

      std::string label = read_entry_label(label_logical_block_offset, label_logical_block_byte_offset);

      hdx_file_entry entry =
      {
        .label = std::move(label),
        .data_file_logical_block_start   = data_logical_block_address,
        .data_file_logical_block_count   = data_logical_block_count,
        .data_file_remaining_bytes_count = data_remaining_bytes_count
      };

      file_entry_list.push_back(entry);

      current_logical_block_byte_offset += hd::constants::hd2_size;
    }

    return file_entry_list;
  }

  hdx_file_entry_list file::read_hd3_file_entries_for_offset(u64 block_offset)
  {
    u64 current_logical_block_byte_offset = 0;
    const u64 descriptor_file_logical_block_start = m_descriptor_file_entry.logical_block_address;
    const u64 data_file_logical_block_start = m_data_file_entry.logical_block_address;

    const u64 current_descriptor_file_logical_block_address = descriptor_file_logical_block_start + block_offset;

    const auto logical_block_byte_count = g_iso_file->get_logical_block_size();

    hdx_file_entry_list file_entry_list{ };
    while (current_logical_block_byte_offset < logical_block_byte_count)
    {
      hd::file_descriptor desc{ };

      g_iso_file->copy_data_from_block(current_descriptor_file_logical_block_address, &m_logical_block_temp_buffer[0]);
      std::memcpy(&desc, &m_logical_block_temp_buffer[current_logical_block_byte_offset], hd::constants::hd2_size);

      const auto label_logical_block_offset      = desc.hd3.name_location / logical_block_byte_count;
      const auto label_logical_block_byte_offset = desc.hd3.name_location % logical_block_byte_count;
      const auto label_logical_block_start       = current_descriptor_file_logical_block_address + label_logical_block_offset;

      const auto data_logical_block_address = data_file_logical_block_start + desc.hd3.logical_block_address;
      const auto data_logical_block_count   = desc.hd3.size / logical_block_byte_count;
      const auto data_remaining_bytes_count = desc.hd3.size % logical_block_byte_count;

      unused_v(data_logical_block_count);
      unused_v(label_logical_block_start);

      std::string label = read_entry_label(label_logical_block_offset, label_logical_block_byte_offset);

      hdx_file_entry entry =
      {
        .label = std::move(label),
        .data_file_logical_block_start   = data_logical_block_address,
        .data_file_logical_block_count   = desc.hd3.logical_block_size,
        .data_file_remaining_bytes_count = data_remaining_bytes_count
      };

      file_entry_list.push_back(entry);

      current_logical_block_byte_offset += hd::constants::hd3_size;
    }

    return file_entry_list;
  }

  u64 file::total_descriptor_entries_per_block()
  {
    const auto total_bytes_per_logical_block = g_iso_file->get_logical_block_size();

    switch (m_file_type)
    {
    case file_type::hd2_file:
      return total_bytes_per_logical_block / constants::hd2_size;
    case file_type::hd3_file:
      return total_bytes_per_logical_block / constants::hd3_size;
    }

    return 0;
  }

  void file::read_hd2_descriptor(hd2_file_descriptor* desc, u64 block, u64 index)
  {
    const auto iso_logical_block_size = g_iso_file->get_logical_block_size();
    const auto descriptor_byte_offset = index * hd::constants::hd2_size;

    if (descriptor_byte_offset > iso_logical_block_size)
      panicf("HDX descriptor index {} is out of bounds of logical block size {}", index, iso_logical_block_size);

    g_iso_file->copy_data_from_block(block, &m_logical_block_temp_buffer[0]);

    std::memcpy(desc, &m_logical_block_temp_buffer[descriptor_byte_offset], hd::constants::hd2_size);
  }

  void file::read_hd3_descriptor(hd3_file_descriptor* desc, u64 block, u64 index)
  {
    const auto iso_logical_block_size = g_iso_file->get_logical_block_size();
    const auto descriptor_byte_offset = index * hd::constants::hd3_size;

    if (descriptor_byte_offset > iso_logical_block_size)
      panicf("HDX descriptor index {} is out of bounds of logical block size {}", index, iso_logical_block_size);

    auto logical_block_temp_buffer = std::make_unique<u8[]>(iso_logical_block_size);

    g_iso_file->copy_data_from_block(block, &logical_block_temp_buffer[0]);

    std::memcpy(desc, &logical_block_temp_buffer[descriptor_byte_offset], hd::constants::hd3_size);
  }

  void file::find_end_of_descriptor_table()
  {
    const auto iso_logical_block_byte_count = g_iso_file->get_logical_block_size();

    unused_v(iso_logical_block_byte_count);

    const auto descriptor_file_logical_block_start        = m_descriptor_file_entry.logical_block_address;
    const auto descriptor_file_logical_block_count        = m_descriptor_file_entry.logical_block_count;
    const auto total_descriptor_entries_per_logical_block = total_descriptor_entries_per_block();

    u64 current_logical_block = descriptor_file_logical_block_start;
    while (current_logical_block < descriptor_file_logical_block_start + descriptor_file_logical_block_count)
    {
      u64 current_descriptor_index = 0;
      while (current_descriptor_index < total_descriptor_entries_per_logical_block)
      {
        switch (m_file_type)
        {
        case file_type::hd2_file:
        {
          hd::hd2_file_descriptor hd2_file_descriptor{ };
          read_hd2_descriptor(&hd2_file_descriptor, current_logical_block, current_descriptor_index);

          const auto descriptor_logical_block_address = hd2_file_descriptor.logical_block_address;
          const auto descriptor_logical_block_count = hd2_file_descriptor.logical_block_size;
          const auto descriptor_byte_count = hd2_file_descriptor.size;

          if (descriptor_logical_block_address == 0 && descriptor_logical_block_count == 0 && descriptor_byte_count == 0)
          {
            m_descriptor_file_table_end_logical_block_offset = current_logical_block - descriptor_file_logical_block_start;

            break;
          }
        }
        break;
        case file_type::hd3_file:
        {
          hd::hd3_file_descriptor hd3_file_descriptor{ };
          read_hd3_descriptor(&hd3_file_descriptor, current_logical_block, current_descriptor_index);

          const auto descriptor_logical_block_address = hd3_file_descriptor.logical_block_address;
          const auto descriptor_logical_block_count = hd3_file_descriptor.logical_block_size;
          const auto descriptor_byte_count = hd3_file_descriptor.size;

          if (descriptor_logical_block_address == 0 && descriptor_logical_block_count == 0 && descriptor_byte_count == 0)
          {
            m_descriptor_file_table_end_logical_block_offset = current_logical_block - descriptor_file_logical_block_start;

            break;
          }
        }
        break;
        default:
          unreachable_code;
        }

        current_descriptor_index++;
      }

      if (m_descriptor_file_table_end_logical_block_offset != 0)
        break;

      current_logical_block++;
    }
  }

}