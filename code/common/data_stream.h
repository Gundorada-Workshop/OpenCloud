// SPDX-License-Identifier: MIT

#pragma once
#include <memory>
#include <string_view>

#include "common/types.h"
#include "common/file_helpers.h"

namespace common
{
  class data_stream_base
  {
  public:
    static constexpr usize block_size = 4096;

    // ctor
    data_stream_base();

    // dtor
    virtual ~data_stream_base();

  public:
    // read type
    template<typename type>
    inline bool read(type* data)
    {
      return read_buffer_checked(static_cast<void*>(data), sizeof(type));
    }

    // write type
    template<typename type>
    inline bool write(const type& data)
    {
      return write_buffer_checked(static_cast<void*>(&data), sizeof(type));
    }

    // same as write buffer but returns true if the specified byte count is written in total
    inline bool write_buffer_checked(void* buff, usize size)
    {
      return write_buffer(buff, size) == size;
    }

    // same as read buffer but returns true if the specified byte count is read in total
    inline bool read_buffer_checked(void* buff, usize size)
    {
      return read_buffer(buff, size) == size;
    }

    inline bool seek_to_start()
    {
      return seek(0);
    }

  public:
    // read n bytes to buffer
    virtual usize read_buffer(void* buff, usize size) = 0;

    // write n bytes to buffer
    virtual usize write_buffer(void* buff, usize size) = 0;

    // seek to an offset in the stream relative to the start
    virtual bool seek(usize pos) = 0;

    // seek to an offset in the stream relative to the current byte offset
    virtual bool seek_relative(usize pos) = 0;

    // seek to the end of the stream
    virtual bool seek_to_end() = 0;

    // get the size of the stream in bytes
    virtual usize size() = 0;

    // current the current byte offset position
    virtual usize pos() = 0;

    // append another stream to this one
    bool append(data_stream_base* other);

    // copy the contents of another stream to this one
    bool copy(data_stream_base* other);

    bool copy_bytes_to_stream(data_stream_base* other, usize byte_count);
  };

  class file_stream : public data_stream_base
  {
  public:
    // ctor
    file_stream(std::FILE* file);

    // dtor
    ~file_stream();

  public:
    // open a new file stream given a path and open mode
    static std::unique_ptr<data_stream_base> open(std::string_view file_path, std::string_view mode);

  public:
    // read n bytes from file
    usize read_buffer(void* buff, usize size) override;

    // write n bytes to file
    usize write_buffer(void* buff, usize size) override;

    // seek to offset in file relative to the start
    bool seek(usize pos) override;

    // seek to offset in file relative to the current position
    bool seek_relative(usize pos) override;

    // seek to the end of the file
    bool seek_to_end() override;

    // get the size of the stream in bytes
    usize size() override;

    // current the current byte offset position
    usize pos() override;

  private:
    // file handle
    std::FILE* m_file;

    // whether the data in m_byte_count is synced with the file
    bool valid_byte_count{ true };
  };

  class memory_stream_base : public data_stream_base
  {
  public:
    memory_stream_base(usize size);
    ~memory_stream_base();

  public:
    // read n bytes from buffer
    usize read_buffer(void* buff, usize size) override;

    // write n bytes to buffer
    usize write_buffer(void* buff, usize size) override;

    // seek to an offset relative to the start of the memory
    bool seek(usize pos) override;

    // seek to a position relative to the current memory pointer
    bool seek_relative(usize pos) override;

    // seek to the end of the memory
    bool seek_to_end() override;

    // get the size of the memory
    usize size() override
    {
      return m_memory_size;
    }

    // get the current position
    usize pos() override
    {
      return m_memory_position;
    }

    virtual u8* data() const = 0;

  protected:
    // size of the memory
    usize m_memory_size{ 0 };

    // current position
    usize m_memory_position{ 0 };
  };

  class unmanaged_memory_stream : public memory_stream_base
  {
  public:
    // ctor
    unmanaged_memory_stream(void* mem, usize size);

    // dtor
    ~unmanaged_memory_stream();
  public:
    // open a new memory stream given a buffer and size
    static std::unique_ptr<memory_stream_base> create(void* buff, usize size);

    u8* data() const override
    {
      return &m_memory_ptr[m_memory_position];
    }

  private:
    // memory handle
    u8* m_memory_ptr{ nullptr };
  };

  class managed_memory_stream : public memory_stream_base
  {
  public:
    managed_memory_stream(std::unique_ptr<u8[]> mem, usize size);
    ~managed_memory_stream();

  public:
    static std::unique_ptr<memory_stream_base> create(usize size);

    u8* data() const override
    {
      return &m_memory[m_memory_position];
    }

  private:
    // memory handle
    std::unique_ptr<u8[]> m_memory;
  };
}
