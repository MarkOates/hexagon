require 'json'

class TreeBuilder
  def build
    #process_lines
    puts JSON.pretty_generate(rollup)
  end

  def command_results
    @command_results ||= (`git grep "^  - name" | grep q\.yml`).split("\n")
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
          symbol: method,
        }
        #puts result
      end
    end
  end
end

tree_builder = TreeBuilder.new
tree_builder.build



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
