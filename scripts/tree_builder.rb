require 'json'
require 'yaml'

class TreeBuilder
  def build
    #process_lines
    entries = rollup
    keys = entries.keys

    result =  "<!DOCTYPE html>\n"
    result += "<head>\n"
    result += "</head>\n"
    result += "<body>\n"


    result += "<h1>TOC</h1>\n"
    result += "<ul>\n"
    keys.each do |key|
      result += "  <li><a href=\"\##{key}\">#{key}</a></li>\n"
    end
    result += "</ul>\n"


    result += "<h1>Components</h1>\n"
    entries.each do |key, value|
      result += "<h4 id=\"#{key}\">#{key}</h4>\n"
      result += "<ul>\n"
      value.each do |symbol|
        result += "  <li>#{symbol}</li>\n"
      end
      result += "</ul>\n"
    end


    result += "</body>"
    puts result

    #puts JSON.pretty_generate(rollup)
  end

  def puts_yamls
    puts yamls
  end

  def command_results
    @command_results ||= (`git grep "^  - name" | grep quintessence | grep q\.yml`).split("\n")
  end

  def component_basename(filename:)
    basename = `~/Repos/ncurses-art/bin/programs/project_filename_generator -x#{filename} -B`
  end

  def yamls
    result = {}
    processed_lines.map do |processed_line|
      #processed_line[:symbol]
      filename = processed_line[:filename]
      yaml = YAML.load(file_contents(filename: filename))
      result[filename] = yaml
      #(result[processed_line[:filename]] ||= []) << processed_line[:symbol]
      #processed_line[:symbol]
    end
    result
  end

  def file_contents(filename:)
    file = File.open(filename)
    file_data = file.read
    file.close
    return file_data
  end

  def rollup
    @rollup ||= begin
      result = {}
      processed_lines.each do |processed_line|
        #processed_line[:symbol]
        (result[processed_line[:filename]] ||= []) << processed_line[:symbol]
        #processed_line[:symbol]
      end
      result
    end
  end

  def processed_lines
    @processed_lines ||= begin
      command_results.map do |command_result|
        index = command_result.index(": ")
        filename = command_result[0...index]
        method = command_result[(index + 11)..-1]
        result = {
          filename: filename,
          # basename: component_basename(filename: filename),
          basename: '[not-set]',
          symbol: method,
          dependencies: {
            direct: [],
            collaborated: [],
          },
          private_methods: [], # mostly not important, it represents a complex internal arrangement to resolve the implementation
          input_types: [],
          input_type_states: [ :requires_initialization ],
          internal_dependencies: [],
          external_dependencies: [],
          private_parent: [],
          private_static_data: [], # constants, methods that return values that will not change
        }
        #puts result
      end
    end
  end
end

tree_builder = TreeBuilder.new
#tree_builder.build
tree_builder.puts_yamls



# make a new method with a form
# have an abstraction up/down or in/out


=begin

class ClassA
  def method_a
    command_result = `git grep "^  - name" | grep q\.yml`
    puts command_result
  end
  def method_a2
    command_result = `git grep "^  - name" | grep q\.yml`
    puts command_result
  end
  def method_a3
    command_result = `git grep "^  - name" | grep q\.yml`
    puts command_result
  end
end

class ClassB
  def method_b
    command_result = `git grep "^  - name" | grep q\.yml`
    puts command_result
  end
end

class ClassC
  def method_c
    command_result = `git grep "^  - name" | grep q\.yml`
    puts command_result
  end
end


# ///////////////////

ClassA
  - method_a
  - method_a2
  - method_a3

ClassB
  - method_b

ClassC
  - method_c

=end
