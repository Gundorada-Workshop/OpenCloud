#include <string.h>

#include "common/log.h"
#include "common/debug.h"
#include "common/data_stream.h"

#include "hd/hd_file.h"
#include "data_extractor.h"

set_log_channel("dc2data");

using namespace common;

extractor::extractor(iso9660::file::file_list files)
  : m_files{ std::move(files) }
  , m_output_directory_path{ file_helpers::append(file_helpers::get_application_directory(), "DATA") }
{
}

extractor::~extractor() = default;

extractor::ptr_type extractor::open()
{
  iso9660::file::file_list files;
  for (const auto& directory : g_iso_file->directories())
  {
    const auto entries = g_iso_file->files_for_directory(directory.path);
    files.insert(files.end(), entries.begin(), entries.end());
  }

  auto out = std::make_unique<extractor>(std::move(files));

  if (!out)
  {
    log_error("Failed to allocate file.");

    return nullptr;
  }

  return out;
}

bool extractor::extract_file(std::string_view iso_file_path)
{
  log_info("Extracting file {}", iso_file_path);

  const auto parent_directory_path = file_helpers::parent_directory(iso_file_path);
  const auto file = find_file_by_name(iso_file_path);

  if (!file)
    return false;

  // don't create the root directory
  if (!parent_directory_path.empty() && !file_helpers::create_directory(parent_directory_path))
  {
    log_error("Failed to create directory {}", parent_directory_path);

    return false;
  }

  if (!extract_direct(*file))
  {
    log_error("Failed to extract {}", file->path);

    return false;
  }

  return true;
}

bool extractor::extract_directory(std::string_view iso_file_path)
{
  log_info("Extracting directory {}", iso_file_path);

  for (const auto& file_entry : m_files)
  {
    const auto file_path = strings::from_sjis(file_entry.path);
    if (!file_path)
      panicf("Failed to convert file path to UTF8");

    const auto parent_directory = file_helpers::parent_directory(*file_path);

    if (parent_directory != iso_file_path)
      continue;

    const auto output_directory = file_helpers::append(m_output_directory_path, parent_directory);

    if (!file_helpers::create_directories(output_directory))
    {
      log_error("Failed to create directory {} skipping...", output_directory);

      continue;
    }

    if (!extract_direct(file_entry))
    {
      log_error("Failed to extract file {} skipping...", *file_path);

      continue;
    }

    log_info("File {} extracted from {}", file_helpers::filename(*file_path), parent_directory);
  }

  return true;
}

bool extractor::extract_hdx_file(std::string_view descriptor_file_path, std::string_view data_file_path)
{
  log_info("Extracting HDX file {} --> {}", descriptor_file_path, data_file_path);

  if (strings::lowercase(file_helpers::ext(descriptor_file_path)) != "hd3")
    return false;

  const auto descriptor_file = find_file_by_name(descriptor_file_path);
  if (!descriptor_file)
  {
    log_error("Failed to find descriptor file {}", descriptor_file_path);

    return false;
  }

  const auto data_file = find_file_by_name(data_file_path);
  if (!data_file)
  {
    log_error("Failed to find data file {}", data_file_path);

    return false;
  }

  usize current_byte = 0;
  while (current_byte < descriptor_file->total_bytes)
  {
    g_iso_file->seek_to_logical_block(descriptor_file->logical_block_address);
    g_iso_file->seek_relative_to_logical_block(current_byte);

    hdx::hd3_file_descriptor desc;
    if (!g_iso_file->copy_bytes_to_buffer(&desc, hdx::constants::hd3_size))
    {
      log_error("Failed to copy descriptor at {}", current_byte);

      return false;
    }

    if (desc.size == 0 && desc.logical_block_offset == 0 && desc.logical_block_size == 0)
      break;

    current_byte += hdx::constants::hd3_size;

    // we can continue from failure beyond this poin
    g_iso_file->seek_relative_to_logical_block(desc.name_location);

    std::array<u8, data_stream_base::block_size> temp{ };
    if (!g_iso_file->copy_bytes_to_buffer(temp.data(), temp.size()))
    {
      log_error("Failed to read name to temp buffer");

      continue;
    }

    char* name_of_unknown_length = std::bit_cast<char*>(temp.data());
    const auto name_length = strnlen_s(name_of_unknown_length, data_stream_base::block_size);

    // we ran off
    if (name_length >= data_stream_base::block_size)
    {
      log_error("Reading name ran off the end of the temp buffer");

      continue;
    }

    auto name = strings::from_sjis({name_of_unknown_length, name_length});

    if (!name)
      panicf("Failed to convert to UTF8");

    const std::string output_path = file_helpers::append(m_output_directory_path, *name);
    const auto parent = file_helpers::parent_directory(output_path);

    if (!file_helpers::create_directories(parent))
    {
      log_error("Failed to create directory {}", parent);

      continue;
    }

    log_info("--> {}", *name);

    g_iso_file->seek_to_logical_block(data_file->logical_block_address + desc.logical_block_offset);

    auto stream = file_stream::open(output_path, "wb");

    if (!stream)
    {
      log_error("Failed to open file stream for {}", output_path);

      continue;
    }

    if (!g_iso_file->copy_bytes_to_stream(stream.get(), desc.size))
    {
      log_error("Failed to copy {} bytes to stream", desc.size);

      continue;
    }
  }

  return true;
}

bool extractor::extract_direct(const iso9660::file::file_entry& file)
{
  const auto file_path = strings::from_sjis(file.path);

  if (!file_path)
    panicf("Failed to convert file path to utf8");

  const auto full_output_file_path = file_helpers::append(m_output_directory_path, *file_path);

  auto output_file_stream = file_stream::open(full_output_file_path, "wb");

  if (!output_file_stream)
  {
    log_error("Failed to open file {}", full_output_file_path);

    return false;
  }

  log_info("Extracting {}...", full_output_file_path);

  if (!g_iso_file->copy_file_entry_to_stream(file, output_file_stream.get()))
  {
    log_error("--> Extraction failed!");

    return false;
  }

  log_info("Extracted {}", file_helpers::filename(full_output_file_path));

  return true;
}

std::optional<iso9660::file::file_entry> extractor::find_file_by_name(std::string_view name)
{
  if (m_files.empty())
  {
    log_error("File list contains no entries searching for {}", name);

    return { };
  }

  const auto itr = std::find_if(m_files.begin(), m_files.end(), [&](const iso9660::file::file_entry& entry) {
    if (entry.path == name)
      return true;

    return false;
  });

  if (itr == m_files.end())
  {
    log_error("Failed to find file {}", name);

    return { };
  }

  return *itr;
}

