#include "common/log.h"
#include "common/debug.h"
#include "common/macros.h"
#include "common/data_stream.h"

set_log_channel("data_stream");

FILE_WARNING_DISABLE(WARNING_ID_ASSIGNMENT_WITHIN_CONDITIONAL_STATEMENT);

namespace common
{
  data_stream_base::data_stream_base() = default;
  data_stream_base::~data_stream_base() = default;

  bool data_stream_base::append(data_stream_base* other)
  {
    assert_panic(other);

    if (!other->seek_to_start() || seek_to_end())
      return false;

    usize chunk_size = 0;

    std::array<u8, block_size> temp_buffer{ };
    while ((chunk_size = other->read_buffer(temp_buffer.data(), temp_buffer.size())))
    {
      if (!write_buffer_checked(temp_buffer.data(), chunk_size))
        return false;

      // EOF
      if (chunk_size < temp_buffer.size())
        break;
    }

    return true;
  }

  bool data_stream_base::copy(data_stream_base* other)
  {
    assert_panic(other);

    if (!other->seek_to_start() || !seek_to_start())
      return false;

    usize chunk_size = 0;

    std::array<u8, block_size> temp_buffer{ };
    while ((chunk_size = other->read_buffer(temp_buffer.data(), temp_buffer.size())))
    {
      if (!write_buffer_checked(temp_buffer.data(), chunk_size))
        return false;

      // EOF
      if (chunk_size < temp_buffer.size())
        break;
    }

    return true;
  }

  bool data_stream_base::copy_bytes_to_stream(data_stream_base* other, usize byte_count)
  {
    if (!other->seek_to_start())
      return false;

    usize write_size = block_size;

    std::array<u8, block_size> temp_buffer{ };

    usize bytes_written = 0;
    while (bytes_written < byte_count)
    {
      if (bytes_written + write_size > byte_count)
        write_size = byte_count - bytes_written;

      if (!read_buffer_checked(temp_buffer.data(), write_size))
        return false;

      if (!other->write_buffer_checked(temp_buffer.data(), write_size))
        return false;

      bytes_written += write_size;
    }

    return true;
  }

  file_stream::file_stream(std::FILE* file)
    : m_file{ file }
  {
  }

  file_stream::~file_stream()
  {
    if (m_file)
      fclose(m_file);
  }

  std::unique_ptr<data_stream_base> file_stream::open(std::string_view file_path, std::string_view mode)
  {
    std::FILE* file;
    if (!file_helpers::open_native(&file, file_path, mode))
      return nullptr;

    return std::make_unique<file_stream>(file);
  }

  usize file_stream::read_buffer(void* buff, usize size)
  {
    return fread(buff, 1, size, m_file);
  }

  usize file_stream::write_buffer(void* buff, usize size)
  {
    return fwrite(buff, 1, size, m_file);
  }

  bool file_stream::seek(usize pos)
  {
    return file_helpers::seek64(m_file, pos, SEEK_SET);
  }

  bool file_stream::seek_relative(usize pos)
  {
    return file_helpers::seek64(m_file, pos, SEEK_CUR);
  }

  bool file_stream::seek_to_end()
  {
    return file_helpers::seek64(m_file, 0, SEEK_END);
  }

  usize file_stream::pos()
  {
    return file_helpers::tell64(m_file);
  }

  usize file_stream::size()
  {
    const auto old_position = pos();

    if (!seek_to_end())
      return 0;

    const auto end = pos();

    if (!seek(old_position))
      return 0;

    return end;
  }

  memory_stream_base::memory_stream_base(usize size)
    : m_memory_size{ size }
  {
  }

  memory_stream_base::~memory_stream_base() = default;

  usize memory_stream_base::read_buffer(void* buff, usize size)
  {
    const auto data_end = m_memory_position + size;

    if (data_end > m_memory_size)
      size = m_memory_size - m_memory_position;

    const auto ptr = data();

    std::memcpy(buff, ptr, size);

    m_memory_position += size;

    return size;
  }

  usize memory_stream_base::write_buffer(void* buff, usize size)
  {
    const auto data_end = m_memory_position + size;

    if (data_end > m_memory_size)
      size = m_memory_size - m_memory_position;

    const auto ptr = data();

    std::memcpy(ptr, buff, size);

    m_memory_position += size;

    return size;
  }

  bool memory_stream_base::seek(usize pos)
  {
    if (pos >= m_memory_size)
      return false;

    m_memory_position = pos;

    return true;
  }

  bool memory_stream_base::seek_relative(usize pos)
  {
    return seek(m_memory_position + pos);
  }

  bool memory_stream_base::seek_to_end()
  {
    return seek(m_memory_size);
  }

  unmanaged_memory_stream::unmanaged_memory_stream(void* ptr, usize size)
    : memory_stream_base(size)
    , m_memory_ptr{ static_cast<u8*>(ptr) }
  {
  }

  unmanaged_memory_stream::~unmanaged_memory_stream() = default;

  std::unique_ptr<memory_stream_base> unmanaged_memory_stream::create(void* mem, usize size)
  {
    return std::make_unique<unmanaged_memory_stream>(mem, size);
  }

  managed_memory_stream::managed_memory_stream(std::unique_ptr<u8[]> mem, usize size)
    : memory_stream_base(size),
    m_memory{ std::move(mem) }
  {
  }

  managed_memory_stream::~managed_memory_stream() = default;

  std::unique_ptr<memory_stream_base> managed_memory_stream::create(usize size)
  {
    auto mem = std::make_unique<u8[]>(size);
    if (!mem)
      return nullptr;

    return std::make_unique<managed_memory_stream>(std::move(mem), size);
  }
}
