class TreeBuilder
  def build
    command_result = `git grep "^  - name" | grep q\.yml`
    puts command_result
  end
end

tree_builder = TreeBuilder.new
tree_builder.build
