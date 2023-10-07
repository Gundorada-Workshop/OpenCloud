#include "common/strings.h"

#include "script/file.h"
#include "script/analyzer.h"

namespace script
{
  using namespace common;

  ALWAYS_INLINE static std::string format_function_entry(function_entry entry)
  {
    static constexpr std::string_view tpl =
    {
      "// func_{:#06x}(argc: {}, stack_size: {})"
    };

    return strings::format(tpl, entry.code_address, entry.argument_count, entry.stack_entry_count);
  }

  ALWAYS_INLINE static u32 calculate_string_length(const stream& code, u32 address)
  {
    code->seek(address);

    char ch;
    while (code->read(&ch))
    {
      if (ch == '\0')
        break;
    }

    const auto end = static_cast<u32>(code->pos());

    return end - address;
  }

  ALWAYS_INLINE static u32 calculate_function_length(const stream& code, u32 address)
  {
    code->seek(address);

    instruction inst;
    while (code->read(&inst))
    {
      if (inst.opcode == opcode::end)
        break;
    }

    return static_cast<u32>(code->pos()) - address;
  }

  static std::vector<u32> discover_string_constant_locations(const stream& code, u32 address)
  {
    code->seek(address);

    std::vector<u32> addresses;

    instruction inst;
    while (code->read(&inst))
    {
      if (inst.opcode == opcode::end)
        break;

      if (inst.opcode != opcode::push)
        continue;

      const auto type = inst.load_store_immediate.type;
      const auto value = inst.load_store_immediate.data;

      if (type != value_data_type::string)
        continue;

      auto entry = std::find(addresses.begin(), addresses.end(), value.str_);

      if (entry == addresses.end())
        addresses.push_back(value.str_);
    }

    return addresses;
  }

  static std::string extract_string_constant(const stream& code, u32 address)
  {
    u32 size = calculate_string_length(code, address);

    std::string out;
    out.resize(size);

    code->seek(address);
    if (!code->read_buffer_checked(out.data(), out.size()))
      return { };

    return strings::sjis_to_utf8_or_none(out);
  }

  static std::map<usize, std::string> extract_string_constant_data(const stream& code, u32 address)
  {
    const auto locations = discover_string_constant_locations(code, address);

    std::map<usize, std::string> out;
    for (const auto location : locations)
    {
      std::string data = extract_string_constant(code, location);

      out.emplace(location, std::move(data));
    }

    return out;
  }

  ALWAYS_INLINE static u32 calculate_string_constant_section_length(const stream& code, u32 address)
  {
    const auto locations = discover_string_constant_locations(code, address);

    u32 size = 0;
    for (const auto location : locations)
      size += calculate_string_length(code, location);

    return common::align_up(size, 16);
  }

  std::vector<bytecode_entry> parse_instructions(const stream& code, u32 start_address)
  {
    code->seek(start_address);

    std::vector<bytecode_entry> out;

    instruction inst;

    auto pos = code->pos();

    while (code->read(&inst))
    {
      if (inst.opcode == opcode::end)
        break;

      bytecode_entry entry =
      {
        .address = static_cast<u32>(pos),
        .inst = inst
      };

      out.push_back(std::move(entry));

      pos = code->pos();
    }

    return out;
  }

  std::vector<function_entry> discover_functions(const stream& code)
  {
    code->seek_to_start();

    std::vector<function_entry> out;

    func_data_entry func_entry;
    while (code->read(&func_entry))
    {
      const auto start_address = func_entry.code_start_byte_offset;

      const auto length = calculate_function_length(code, start_address);
      const auto string_constant_data_length = calculate_string_constant_section_length(code, start_address);

      const auto end_address = start_address + length + string_constant_data_length;

      std::vector<bytecode_entry> instructions = parse_instructions(code, start_address);
      std::map<usize, std::string> constant_data = extract_string_constant_data(code, start_address);

      function_entry entry
      {
        .address           = start_address - sizeof(func_data_entry),
        .code_address      = start_address,
        .size              = length,
        .argument_count    = func_entry.argument_count,
        .stack_entry_count = func_entry.stack_byte_count,
        .code              = std::move(instructions),
        .constants         = std::move(constant_data)
      };

      code->seek(end_address);

      out.push_back(std::move(entry));
    }

    return out;
  }

  std::optional<label_entry> label_for_instruction(const instruction& inst)
  {
    const auto instruction_type = encoding_type_for_opcode(inst.opcode);

    switch (instruction_type)
    {
    case instruction_encoding_type::load_store_immediate:
    {
      const auto value_type = inst.load_store_immediate.type;
      const auto value = inst.load_store_immediate.data;

      if (value_type != value_data_type::string)
        break;

      label_entry entry =
      {
        .address = value.str_,
        .type    = label_type::string_constant,
      };

      return entry;
    }
    case instruction_encoding_type::conditional_branch:
    {
      const auto address = inst.conditional_branch.address;

      label_entry entry =
      {
        .address = address,
        .type    = label_type::branch_target
      };

      return entry;
    }
    case instruction_encoding_type::jump:
    {
      const auto address = inst.jump.address;

      label_entry entry =
      {
        .address = address,
        .type    = label_type::branch_target
      };

      return entry;
    }
    }

    return std::nullopt;
  }

  std::map<usize, label_entry> discover_labels(const std::vector<function_entry>& functions)
  {
    std::map<usize, label_entry> out;

    for (const auto& func : functions)
    {
      for (const auto& inst : func.code)
      {
        auto label = label_for_instruction(inst.inst);
        
        if (label)
          out.emplace(label->address, std::move(*label));
      }
    }

    return out;
  }

  std::optional<label_entry> label_at_address(const std::map<usize, label_entry>& entries, usize address)
  {
    const auto itr = entries.find(address);

    if (itr == entries.end())
      return std::nullopt;

    return itr->second;
  }
}