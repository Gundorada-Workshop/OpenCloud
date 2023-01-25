#pragma once
#include <functional>

#include "common/types.h"
#include "common/strings.h"

#include "graph/rectangle.h"

namespace graph
{
  class texture
  {
  public:
    // format of the texture
    enum class data_format
    {
      unknown,
      rgba8,
      bgra8,
      rgb565,
      r8,
      d16,
      max
    };

    // how the texture is bound
    // can be none or more of these
    enum class bind_flags : u8
    {
      none = 0,
      shader_resource = 1 << 0,
      render_target =   1 << 1,
      depth_stencil =   1 << 2,
      max
    };

    // struct used for texture param passing
    struct create_info
    {
      u32 width;
      u32 height;
      u32 layers;
      u32 levels;
      u32 samples;
      data_format format{ data_format::rgba8 };
      bind_flags flags{ bind_flags::shader_resource };

      bool operator ==(const create_info& other) const
      {
        return std::tie(width, height, layers, levels, samples, format, flags) ==
          std::tie(other.width, other.height, other.layers, other.levels, other.samples, other.format, other.flags);
      }

      bool operator !=(const create_info& other) const
      {
        return !operator==(other);
      }
    };

    // construct a new texture
    explicit texture(const create_info& config);

    // dtor
    virtual ~texture() = default;

  public:
    // sets the debug name
    // this is optional
    ALWAYS_INLINE void set_debug_name(std::string_view name)
    {
      m_debug_name = std::string{ name };
    }

    // gets the debug name
    ALWAYS_INLINE std::string_view debug_name() const
    {
      return m_debug_name;
    }

    // rectangle
    ALWAYS_INLINE graph::irect rect() const
    {
      return graph::irect::from_extent(m_config.width, m_config.height);
    }

    // width
    ALWAYS_INLINE u32 width() const
    {
      return m_config.width;
    }

    // height
    ALWAYS_INLINE u32 height() const
    {
      return m_config.height;
    }

    // layers
    ALWAYS_INLINE u32 layers() const
    {
      return m_config.layers;
    }

    // levels
    ALWAYS_INLINE u32 levels() const
    {
      return m_config.levels;
    }

    // samples
    ALWAYS_INLINE u32 samples() const
    {
      return m_config.samples;
    }

    // data format
    ALWAYS_INLINE data_format format() const
    {
      return m_config.format;
    }

    // bind flags
    ALWAYS_INLINE bind_flags flags() const
    {
      return m_config.flags;
    }

    ALWAYS_INLINE create_info config() const
    {
      return m_config;
    }

  protected:
    // settings for the texture
    create_info m_config{ };

    // debug name for the texture
    std::string m_debug_name{ };
  };
}

IMPLEMENT_ENUM_CLASS_BITWISE_OPERATORS(graph::texture::bind_flags);

template<>
struct std::hash<graph::texture::create_info>
{
  usize operator()(const graph::texture::create_info& config) const noexcept
  {
    const u64 width  = static_cast<u64>(config.width);
    const u64 height = static_cast<u64>(config.height);
    const u64 layers = static_cast<u64>(config.layers);
    const u64 levels = static_cast<u64>(config.levels);
    const u64 format = static_cast<u64>(config.format);
    const u64 flags  = static_cast<u64>(config.flags);

    const u64 uid = width << 0 | height << 16 | layers << 32 | levels << 48 | format << 50 | flags << 58;

    return std::hash<u64>{}(uid);
  }
};

template<>
struct fmt::formatter<graph::texture::data_format> : formatter<string_view>
{
  auto format(const graph::texture::data_format data_format, format_context& ctx)
  {
    switch (data_format)
    {
    case graph::texture::data_format::rgba8:
      return fmt::format_to(ctx.out(), "{}", "R8G8B8A8");
    case graph::texture::data_format::bgra8:
      return fmt::format_to(ctx.out(), "{}", "B8G8R8A8");
    case graph::texture::data_format::rgb565:
      return fmt::format_to(ctx.out(), "{}", "R5G6B5");
    case graph::texture::data_format::r8:
      return fmt::format_to(ctx.out(), "{}", "R8");
    case graph::texture::data_format::d16:
      return fmt::format_to(ctx.out(), "{}", "D16");
    }

    return fmt::format_to(ctx.out(), "{}", "UNKNOWN");
  }
};

template<>
struct fmt::formatter<graph::texture::bind_flags> : formatter<string_view>
{
  // TODO: this kinda sucks
  auto format(const graph::texture::bind_flags flags, format_context& ctx)
  {
    if (std::to_underlying(flags) == 0)
      return fmt::format_to(ctx.out(), "flags(none)");

    constexpr std::array<std::string_view, 3> flag_names =
    {
      "shader_resource",
      "rander_target",
      "depth_stencil"
    };

    std::string flags_string;
    for (usize i = 0; i < std::to_underlying(graph::texture::bind_flags::max); ++i)
    {
      if (std::to_underlying(flags) & (1 << i))
      {
        flags_string += flag_names[i];
        flags_string += "|";
      }
    }

    // remove trailing |
    flags_string.pop_back();

    return fmt::format_to(ctx.out(), "flags({})", flags_string);
  }
};

template<>
struct fmt::formatter<graph::texture::create_info> : formatter<string_view>
{
  auto format(const graph::texture::create_info& config, format_context& ctx)
  {
    return fmt::format_to(ctx.out(), "create_info(fmt: {}, w: {}, h: {}, layers: {}, levels: {}, samples: {})",
      config.format, config.width, config.height, config.layers, config.levels, config.samples);
  }
};
