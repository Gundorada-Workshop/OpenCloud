require "git"
require "erb"

raise ArgumentError, "Not enough or too many arguments" unless ARGV.count == 3

GIT_ROOT_PATH = ARGV[0]

TEMPLATE_FILE = ARGV[1]
OUTPUT_FILE   = ARGV[2]

git = Git.open(GIT_ROOT_PATH, :log => Logger.new(STDOUT))

input_file = File.open(TEMPLATE_FILE)
template = ERB.new(input_file.read)

File.open(OUTPUT_FILE, "w") do |f|
  f.write(template.result(binding))
end