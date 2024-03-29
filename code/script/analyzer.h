#pragma once
#include <map>

#include <functional>

#include "common/types.h"
#include "common/bits.h"
#include "common/strings.h"
#include "common/data_stream.h"
#include "common/helpers.h"

#include "script/bytecode.h"

namespace script
{
  using stream = std::unique_ptr<common::memory_stream_base>;
  
  enum class label_type : u32
  {
    branch_target,
    function,
    string_constant,
    count
  };

  struct label_entry
  {
    usize address;
    label_type type;
  };

  struct bytecode_entry
  {
    usize address;
    instruction inst;
    label_type label;
  };

  struct function_entry
  {
    usize address;
    usize code_address;
    usize size;
    u32 argument_count;
    u32 stack_entry_count;

    std::vector<bytecode_entry> code;
    std::map<usize, std::string> constants;
  };

  std::vector<function_entry> discover_functions(const stream& code);
  std::map<usize, label_entry> discover_labels(const std::vector<function_entry>& functions);
  std::optional<label_entry> label_at_address(const std::map<usize, label_entry>& entries, usize address);
}

template<>
struct fmt::formatter<script::label_type> : formatter<string_view>
{
  auto format(script::label_type type, format_context& ctx) const -> decltype(ctx.out())
  {
    static constexpr std::array<string_view, common::to_underlying(script::label_type::count)> table =
    {
      "loc",
      "fun",
      "str"
    };

    if (type > script::label_type::count)
      ctx.on_error("Label type out of bounds");

    return formatter<string_view>::format(table[common::to_underlying(type)], ctx);
  }
};

template<>
struct fmt::formatter<script::label_entry> : formatter<string_view>
{
  auto format(const script::label_entry& label, format_context& ctx) const -> decltype(ctx.out())
  {
    return fmt::format_to(ctx.out(), "{}_{:06x}:", label.type, label.address);
  }
};
