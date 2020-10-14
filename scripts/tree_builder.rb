class TreeBuilder
  def build
    process_lines
  end

  def command_results
    @command_results ||= (`git grep "^  - name" | grep q\.yml`).split("\n")
  end

  def process_lines
    command_results.each do |command_result|
      index = command_result.index(": ")
      left = command_result[0...index]
      right = command_result[(index + 11)..-1]
      result = {
        left: left,
        right: right,
      }
      puts result
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
