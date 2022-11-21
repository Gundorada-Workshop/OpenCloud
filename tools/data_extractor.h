#pragma once
#include <memory>
#include <string_view>
#include <vector>
#include <bit>

#include "common/file_helpers.h"

#include "iso9660/types.h"
#include "iso9660/iso_file.h"
#include "hd/hd_file.h"

class extractor
{
public:
  // pointer handle
  using ptr_type = std::unique_ptr<extractor>;

public:
  // ctor
  extractor(iso9660::file::file_list files);

  // dtor
  ~extractor();

public:
  // get a handle to an iso file
  static ptr_type open();

public:
  bool extract_file(std::string_view iso_file_path);
  bool extract_hdx_file(std::string_view descriptor_file_path, std::string_view data_file_path);
  bool extract_directory(std::string_view iso_file_path);

public:
  inline void set_output_directory(std::string_view directory)
  {
    m_output_directory_path = directory;
  }

  inline bool create_output_directory()
  {
    if (!common::file_helpers::create_directory(m_output_directory_path))
      return false;

    return true;
  }

  inline std::string_view get_output_directory() const
  {
    return m_output_directory_path;
  }

private:
  // extract normal files
  bool extract_direct(const iso9660::file::file_entry& file);

  std::optional<iso9660::file::file_entry> find_file_by_name(std::string_view name);

  // output directory
  std::string m_output_directory_path{ };

  iso9660::file::file_list m_files{ };
};
