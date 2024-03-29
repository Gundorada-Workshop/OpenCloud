require "erb"
require "ox"
require "facets/string/underscore"

require_relative "lib/template"

# This could probably be improved but my Ruby is a bit rusty

# load the xml for vk.xml
def load_registry_file(filepath)
  Ox.load_file(VK_REGISTRY_PATH)
end

# get the base enum list
def get_base_enums(document)
  data.locate("registry/enums[@type=enum]")
end

# return the includes for the header
def render_header_includes(system_includes, local_includes)
  render_template("header_includes", binding)
end

# get the warning comment
def render_header_comment(script_location)
  render_template("header_comment", binding)
end

# render a single enum value entry
def render_enum_entry_data(name)
  template = "<%= name %>, \"<%= name %>\","

  render_template(template, binding)
end

#get the data for the enums
def get_enum_entry_data(document)
  document.locate("registry/enums[@type=enum]")
end

# get EXT data for enum
def get_extended_enum_entry_data(document, name)
  document.locate("registry/extensions/extension/require/enum[@extends=#{name}]")
end

# get the values as an array of strings
def get_enum_value_names(document, element)
  base = element.locate("enum").collect do |v|
    v[:name]
  end

  ext = get_extended_enum_entry_data(document, element[:name]).collect do |v|
    v[:name]
  end

  base.concat(ext)
end

# build the enum map
def get_enums(document)
  entries = get_enum_entry_data(document)

  out = {}
  entries.each do |entry|
    values = get_enum_value_names(document, entry)

    out[entry[:name]] = values
  end

  out
end

def render_formatter_for_enums(enum_name_data)
  template = "<% enum_name_data.each_key do |name| -%>" \
               "// <%= name %>\n" \
               "template<>\n" \
               "struct fmt::formatter<<%= name %>> : formatter<string_view>\n" \
               "{\n" \
               "  auto format(<%= name %> value, format_context& ctx) const -> decltype(ctx.out())\n" \
               "  {\n" \
               "    static constexpr common::dictionary<<%= name %>, std::string_view, <%= enum_name_data[name].count %>> s_map =\n" \
               "    {\n" \
                      "<% enum_name_data[name].each do |value_name| -%>" \
                 "      {<%= value_name %>, \"<%= value_name %>\"},\n" \
                      "<% end -%>" \
               "    };\n\n" \
               "    return fmt::format_to(ctx.out(), \"{}\", s_map.find_or_panic(value));\n" \
               "  }\n" \
               "};\n\n" \
             "<% end -%>"

  render_template(template, binding)
end

VK_REGISTRY_PATH = ARGV[0]
OUTPUT_PATH = ARGV[1]

TEMPLATE = %{
<%= render_header_includes(system_includes, local_includes) %>
<%= render_header_comment(script_path) %>
<%= render_formatter_for_enums(enums) %>
}

system_includes = [
  "volk/volk.h",
  "string_view"
]

local_includes = [
  "common/dictionary.h",
  "common/strings.h"
]

script_path = $0

doc = load_registry_file(VK_REGISTRY_PATH)
enum_name_data = get_enums(doc)

result = render_template("enum_formatters", binding)

File.open(OUTPUT_PATH, "w") do |output_file|
  output_file.write(result)
end