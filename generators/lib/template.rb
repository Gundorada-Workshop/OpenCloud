require "erb"

class TemplateCache
  TEMPLATE_DIR = "./generators/templates/"
  TEMPLATE_SEARCH = "*.erb"

  @@templates = {}

  def self.load
    return unless @@templates.empty?

    puts "Caching templates"

    template_files = Dir.glob(TEMPLATE_DIR + TEMPLATE_SEARCH)

    if template_files.empty?
      puts "No templates found in #{TEMPLATE_DIR}"

      return
    end

    Dir.glob(TEMPLATE_DIR + TEMPLATE_SEARCH).each do |path|
      id = File.basename(path, File.extname(path))

      puts "#{id} => #{path}"

      @@templates[id] = load_template_from_file(path)
    end
  end

  def self.load_template_from_file(path)
    File.read(path)
  end

  def self.load_template(name)
    load()

    puts "Searching cache for #{name}"

    raise "Template not found" unless @@templates.keys.include?(name)

    @@templates[name]
  end
end

# render an ERB template
def render_template(template_name, data)
  template = TemplateCache.load_template(template_name)

  output = ERB.new(template, trim_mode: '-')
  output.result(data)
end
