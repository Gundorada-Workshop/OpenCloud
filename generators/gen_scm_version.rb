require "git"
require "erb"

raise ArgumentError, "Not enough or too many arguments" unless ARGV.count == 3

GIT_ROOT_PATH = ARGV[0]

TEMPLATE_PATH = ARGV[1]
OUTPUT_PATH  = ARGV[2]

git = Git.open(GIT_ROOT_PATH, :log => Logger.new(STDOUT))

File.open(TEMPLATE_PATH, "r") do |input_file|
  template = ERB.new(input_file.read)

  File.open(OUTPUT_PATH, "w") do |output_file|
    output_file.write(template.result(binding))
  end
 end