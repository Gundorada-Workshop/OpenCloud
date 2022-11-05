#pragma once
#include <memory>
#include <string_view>
#include <vector>
#include <bit>

#include "common/file_helpers.h"

#include "iso9660/types.h"
#include "iso9660/iso_file.h"

class extractor
{
public:
  // pointer handle
  using ptr_type = std::unique_ptr<extractor>;

public:
  // ctor
  extractor();

  // dtor
  ~extractor();

public:
  // get a handle to an iso file
  static ptr_type open(std::string_view file);

public:
  bool extract_file(std::string_view iso_file_path);
  bool extract_directory(std::string_view iso_file_path);

public:
  inline void set_output_directory(std::string_view directory)
  {
    m_output_directory = directory;
  }

  inline bool create_output_directory()
  {
    if (!common::file_helpers::create_directory(m_output_directory))
      return false;

    return true;
  }

  inline std::string_view get_output_directory() const
  {
    return m_output_directory;
  }

private:
  // extract an iso file
  bool extract(const iso9660::file::file_entry& file);

  // iso file handle
  iso9660::file::ptr_type m_iso_file;

  // output directory
  std::string m_output_directory{ };
};
