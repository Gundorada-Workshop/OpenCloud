#include "common/log.h"
#include "common/debug.h"
#include "common/scoped_function.h"

#include "data_extractor.h"

set_log_channel("DC2DataExtractor");

using namespace common;

extractor::extractor()
{
  const auto app_directory = file_helpers::get_application_directory();

  m_output_directory = file_helpers::append(app_directory, "DATA");
}

extractor::~extractor() = default;

static inline std::string lowercase(std::string_view s)
{
  std::string out{ s };

  std::transform(out.begin(), out.end(), out.begin(), [&](char ch) {
      return std::tolower(ch);
  });

  return out;
}

static inline bool is_hd2_file(std::string_view path)
{
  return lowercase(file_helpers::ext(path)) == "hd2";
}

static inline bool is_hd3_file(std::string_view path)
{
  return lowercase(file_helpers::ext(path)) == "hd3";
}

static inline bool is_hd_file(std::string_view path)
{
  return is_hd2_file(path) || is_hd3_file(path);
}

static inline std::string_view trim_iso_version_id(std::string_view s)
{
  const auto pos = s.find_last_of(';');

  if (pos == std::string_view::npos)
    return s;

  return s.substr(0, pos);
}

extractor::ptr_type extractor::open(std::string_view file)
{
  auto out = std::make_unique<extractor>();

  if (!out)
  {
    log_error("Failed to allocate file.");

    return nullptr;
  }

  out->m_iso_file = iso9660::file::open(file);

  if (!out->m_iso_file)
  {
    log_error("Failed to open ISO file.");

    return nullptr;
  }

  return out;
}

bool extractor::extract_file(std::string_view iso_file_path)
{
  const auto parent_dir = file_helpers::parent_directory(iso_file_path);
  const auto files = m_iso_file->get_files_for_directory(parent_dir);

  const bool is_root = parent_dir.empty();

  if(files.empty())
    return false;

  const auto itr = std::find_if(files.begin(), files.end(), [&](const iso9660::file::file_entry entry) {
    if (trim_iso_version_id(entry.path) == iso_file_path)
      return true;

    return false;
  });

  if (itr == files.end())
  {
    log_error("Failed to find file {}", iso_file_path);

    return false;
  }

  if (is_root && !file_helpers::create_directory(parent_dir))
  {
    log_error("Failed to create directory {}", parent_dir);

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
  const auto directories = m_iso_file->get_directories();

  if (directories.empty())
    return false;

  const auto itr = std::find_if(directories.begin(), directories.end(), [&](const iso9660::file::directory_entry& entry) {
    if (entry.path == iso_file_path)
      return true;

    return false;
  });

  if (itr == directories.end())
  {
    log_error("Failed to file directory {}", iso_file_path);

    return false;
  }

  const auto output_directory = file_helpers::append(m_output_directory, itr->path);

  if (!file_helpers::create_directory(output_directory))
  {
    log_error("Failed to create directory {}", output_directory);

    return false;
  }

  log_info("Directory {}", output_directory);

  for (const auto& file : m_iso_file->get_files_for_directory(itr->path))
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
  std::FILE* output_file{ nullptr };

  const auto path = file_helpers::append(m_output_directory, trim_iso_version_id(file.path));

  if (!file_helpers::open_native(&output_file, path, "wb"))
  {
    log_error("Failed to open output file {}", path);

    return false;
  }

  scoped_function cleanup([&]() {
    fclose(output_file);
  });

  const auto block_size = m_iso_file->get_logical_block_size();

  // temp buffer to hold our data
  const auto buff = std::make_unique<u8[]>(block_size);

  log_info("Extracting {}...", path);

  // read all of the lbas
  for (u64 i = 0; i < file.logical_block_count; ++i)
  {
    log_info("LBA {} of {}", i, file.logical_block_count);

    if (!m_iso_file->seek(file.logical_block_address + i, SEEK_SET))
    {
      log_error("Unable to seek to file {}", file.logical_block_address + i);

      return false;
    }

    if (!m_iso_file->read(&buff[0], 1, 0))
    {
      log_error("Failed to read block {}", i);

      return false;
    }

    if (fwrite(&buff[0], block_size, 1, output_file) != 1)
    {
      log_error("Failed to write block {} to file", i);

      return false;
    }
  }

  // write out any non-lba aligned bytes
  if (file.extra_bytes)
  {
    log_info("Non-aligned bytes {}", file.extra_bytes);

    if (!m_iso_file->seek(file.logical_block_address + file.logical_block_count + 1, SEEK_SET))
    {
      log_error("Unable to seek to file {}", file.logical_block_address + file.logical_block_count + 1);

      return false;
    }
    if (!m_iso_file->read(&buff[0], 1, 0))
    {
      log_error("Failed to read remaining bytes {}", file.extra_bytes);

      return false;
    }

    if (fwrite(&buff[0], file.extra_bytes, 1, output_file) != 1)
    {
      log_error("Failed to write remaining {} bytes to file", file.extra_bytes);

      return false;
    }
  }

  return true;
}

