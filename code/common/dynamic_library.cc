#if defined(_WIN32)
#include <wil/resource.h>
#elif defined(__linux__)
#include <dlfcn.h>
#else
#error Not Implemented
#endif

#include "common/strings.h"
#include "common/debug.h"
#include "common/macros.h"
#include "common/dynamic_library.h"

namespace common
{
  #if defined(_WIN32)
  using handle_type = wil::unique_hmodule;
  #elif defined(__linux__)
  using handle_type = void*;
  #else
  #error Not Implemented
  #endif

  class dynamic_library::impl
  {
  public:
    impl();
    ~impl();

    bool open(std::string_view name);
    void close();

    void* load(std::string_view name);

    ALWAYS_INLINE bool is_open() const;

  private:
    handle_type m_handle{ };
  };

  dynamic_library::impl::impl() = default;
  dynamic_library::impl::~impl() = default;

  ALWAYS_INLINE bool dynamic_library::impl::is_open() const
  {
    return m_handle != nullptr;
  }

  #if defined(_WIN32)
  bool dynamic_library::impl::open(std::string_view name)
  {
    const auto wide_name = strings::utf8_to_wstring_or_panic(name);

    m_handle.reset(LoadLibraryW(wide_name.c_str()));

    return is_open();
  }

  void dynamic_library::impl::close()
  {
    m_handle.reset();
  }

  void* dynamic_library::impl::load(std::string_view name)
  {
    const auto string_name = std::string{ name };
    const auto addr = GetProcAddress(m_handle.get(), string_name.c_str());

    return reinterpret_cast<void*>(addr);
  }
  #elif defined(__linux__)
  bool dynamic_library::impl::open(std::string_view name)
  {
    const auto name_string = std::string{ name };

    m_handle = dlopen(name_string.c_str(), RTLD_NOW);

    return is_open();
  }

  void dynamic_library::impl::close()
  {
    dlclose(m_handle);
    m_handle = nullptr;
  }

  void* dynamic_library::impl::load(std::string_view name)
  {
    const auto name_string = std::string{ name };

    return dlsym(m_handle, name_string.c_str());
  }
  #else
  #error Not Implemented
  #endif

  dynamic_library::dynamic_library()
    : m_impl{ std::make_unique<impl>() }
  {
    assert_panic(m_impl);
  }

  dynamic_library::dynamic_library(std::string_view name)
    : m_impl{ std::make_unique<impl>() }
  {
    assert_panic(m_impl);
    assert_panic(open(name));
  }

  dynamic_library::~dynamic_library()
  {
    close();
  }

  bool dynamic_library::open(std::string_view name)
  {
    assert_panic(!m_impl->is_open());

    return m_impl->open(name);
  }

  void dynamic_library::close()
  {
    if (m_impl->is_open())
      m_impl->close();
  }

  void* dynamic_library::load_pfn(std::string_view name)
  {
    assert_panic(m_impl->is_open());

    return m_impl->load(name);
  }
}
