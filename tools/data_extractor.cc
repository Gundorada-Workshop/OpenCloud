#include <string.h>

#include "common/log.h"
#include "common/debug.h"
#include "common/scoped_function.h"

#include "hd/hd_file.h"
#include "data_extractor.h"

set_log_channel("DC2DataExtractor");

using namespace common;

extractor::extractor()
{
  const std::string_view app_directory_path = file_helpers::get_application_directory();

  m_output_directory_path = file_helpers::append(app_directory_path, "DATA");
}

extractor::~extractor() = default;

extractor::ptr_type extractor::open()
{
  auto out = std::make_unique<extractor>();

  if (!out)
  {
    log_error("Failed to allocate file.");

    return nullptr;
  }

  const auto logical_block_byte_count = g_iso_file->get_logical_block_size();
  auto temp_block_buffer = std::make_unique<u8[]>(logical_block_byte_count);

  if (!temp_block_buffer)
  {
    log_error("Failed to allocate temp buffer");

    return nullptr;
  }

  out->m_temp_block_buffer = std::move(temp_block_buffer);

  return out;
}

bool extractor::extract_file(std::string_view iso_file_path)
{
  const auto parent_directory_path = file_helpers::parent_directory(iso_file_path);
  const auto directory_file_list = g_iso_file->get_files_for_directory(parent_directory_path);

  const bool is_root = parent_directory_path.empty();

  if (directory_file_list.empty())
    return false;

  const auto itr = std::find_if(directory_file_list.begin(), directory_file_list.end(), [&](const iso9660::file::file_entry entry) {
    if (entry.path == iso_file_path)
      return true;

    return false;
  });

  if (itr == directory_file_list.end())
  {
    log_error("Failed to find file {}", iso_file_path);

    return false;
  }

  if (!is_root && !file_helpers::create_directory(parent_directory_path))
  {
    log_error("Failed to create directory {}", parent_directory_path);

    return false;
  }

  if (!extract(*itr))
  {
    log_error("Failed to extract {}", itr->path);

    return false;
  }

  return true;
}

bool extractor::extract_directory(std::string_view iso_file_path)
{
  const auto iso_file_directory_list = g_iso_file->get_directories();

  if (iso_file_directory_list.empty())
    return false;

  const auto itr = std::find_if(iso_file_directory_list.begin(), iso_file_directory_list.end(), [&](const iso9660::file::directory_entry& entry) {
    if (entry.path == iso_file_path)
      return true;

    return false;
  });

  if (itr == iso_file_directory_list.end())
  {
    log_error("Failed to file directory {}", iso_file_path);

    return false;
  }

  const auto output_directory = file_helpers::append(m_output_directory_path, itr->path);

  if (!file_helpers::create_directory(output_directory))
  {
    log_error("Failed to create directory {}", output_directory);

    return false;
  }

  log_info("Directory {}", output_directory);

  for (const auto& file : g_iso_file->get_files_for_directory(itr->path))
  {
    if (!extract(file))
    {
      log_error("Failed to extract file {}", file.path);

      return false;
    }
  }

  return true;
}

bool extractor::extract(const iso9660::file::file_entry& file)
{
  if (hd::file::is_valid_desciptor(file))
  {
    auto hd_file = hd::file(file);

    if (!hd_file.find_data_file())
    {
      log_warn("Found HDX file but unable to find corresponding data file");

      return false;
    }

    return extract_hdx(hd_file);
  }

  return extract_direct(file);
}

bool extractor::extract_hdx(hd::file& hdx_file)
{
  log_info("Found HDX File...");

  const auto logical_block_byte_count = g_iso_file->get_logical_block_size();

  hdx_file.find_end_of_descriptor_table();

  u64 current_logical_block_offset = 0;
  while (!hdx_file.descriptor_table_final_logical_block_offset(current_logical_block_offset))
  {
    const auto block_entry_list = hdx_file.get_entries_for_descriptor_table_block_offset(current_logical_block_offset);

    for (auto& entry : block_entry_list)
    {
      const auto label = strings::from_sjis(entry.label);
      if (!label)
        panicf("Failed to convert label to utf8");

      log_info("--> {}", *label);

      const std::string output_file_path = file_helpers::append(m_output_directory_path, *label);
      const std::string_view output_file_parent_path = file_helpers::parent_directory(output_file_path);

      const auto entry_logical_block_count = entry.data_file_logical_block_count;
      const auto entry_logical_block_start = entry.data_file_logical_block_start;

      if (!file_helpers::create_directories(output_file_parent_path))
        panicf("Failed to create output directory {}", output_file_parent_path);

      std::FILE* output_file;
      if (!file_helpers::open_native(&output_file, output_file_path, "wb"))
        panicf("Failed to open output file {}", output_file_path);

      scoped_function cleanup([&]() {
        fclose(output_file);
      });

      u64 current_data_logical_block_offset = 0;
      while (current_data_logical_block_offset < entry_logical_block_count)
      {
        const auto current_data_logical_block_address = entry_logical_block_start + current_data_logical_block_offset;

        g_iso_file->copy_data_from_block(current_data_logical_block_address, &m_temp_block_buffer[0]);

        // write out a whole logical block
        if (fwrite(&m_temp_block_buffer[0], logical_block_byte_count, 1, output_file) != 1)
          panicf("Failed to write to file {}", output_file_path);

        current_data_logical_block_offset++;
      }

      const auto remaining_byte_count = entry.data_file_remaining_bytes_count;

      // write out remaining bytes
      if (remaining_byte_count)
      {
        // the above won't catch if the file is less than a logical block
        auto remaining_data_logical_block_address = entry_logical_block_start;

        // but if it is more than a logical block, we want the end
        if (entry_logical_block_count)
          remaining_data_logical_block_address += current_data_logical_block_offset;

        g_iso_file->copy_data_from_block(remaining_data_logical_block_address, &m_temp_block_buffer[0]);

        if (fwrite(&m_temp_block_buffer[0], remaining_byte_count, 1, output_file) != 1)
          panicf("Failed to write {} remaining bytes to file {}", remaining_byte_count, output_file_path);
      }
    }

    current_logical_block_offset++;
  }

  return true;
}

bool extractor::extract_direct(const iso9660::file::file_entry& file)
{
  std::FILE* output_file{ nullptr };

  const auto file_path = strings::from_sjis(file.path);
  if (!file_path)
    panicf("Failed to convert file path to utf8");

  const auto output_file_path = file_helpers::append(m_output_directory_path, *file_path);

  if (!file_helpers::open_native(&output_file, output_file_path, "wb"))
  {
    log_error("Failed to open output file {}", output_file_path);

    return false;
  }

  // make sure we clean up the file handle
  scoped_function cleanup([&]() {
    fclose(output_file);
  });

  const auto logical_block_byte_size    = g_iso_file->get_logical_block_size();
  const auto file_logical_block_count   = file.logical_block_count;
  const auto file_logical_block_address = file.logical_block_address;
  const auto file_remaining_byte_count  = file.extra_bytes;

  log_info("Extracting {}...", output_file_path);

  // read all of the lbas
  u64 current_file_logical_block_offset = 0;
  while (current_file_logical_block_offset < file_logical_block_count)
  {
    const auto current_logical_block_address = file_logical_block_address + current_file_logical_block_offset;

    g_iso_file->copy_data_from_block(current_logical_block_address, &m_temp_block_buffer[0]);

    if (fwrite(&m_temp_block_buffer[0], logical_block_byte_size, 1, output_file) != 1)
    {
      log_error("Failed to write block {} to file", current_file_logical_block_offset);

      return false;
    }

    current_file_logical_block_offset++;
  }

  // write out any non-lba aligned bytes
  if (file_remaining_byte_count)
  {
    const auto file_last_aligned_logical_block_address = file_logical_block_address + file_logical_block_count;
    const auto file_unaligned_logical_block_address    = file_last_aligned_logical_block_address + 1;

    log_info("Non-aligned bytes {}", file_remaining_byte_count);

    g_iso_file->copy_data_from_block(file_unaligned_logical_block_address, &m_temp_block_buffer[0]);

    if (fwrite(&m_temp_block_buffer[0], file.extra_bytes, 1, output_file) != 1)
    {
      log_error("Failed to write remaining {} bytes to file", file_remaining_byte_count);

      return false;
    }
  }

  return true;
}

