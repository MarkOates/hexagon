
#include <gtest/gtest.h>

#include <Hexagon/ComponentNavigator/List.hpp>

TEST(Hexagon_ComponentNavigator_ListTest, run__returns_the_expected_response)
{
   std::string project_root_directory = "/Users/markoates/Repos/blast";
   Hexagon::ComponentNavigator::List list(project_root_directory);

   std::vector<std::string> expected_list = {
      "Blast/DirectoryCreator",
      "Blast/ShellCommandExecutorWithCallback",
      "Blast/CamelCaseToUnderscoreConverter",
      "Blast/Project/ComponentBasenameExtractor",
      "Blast/TemplatedFile",
      "Blast/Cpp/FunctionBody",
      "Blast/Cpp/Function",
      "Blast/DirectoryExistenceChecker",
      "Blast/StringSplitter",
   };

   std::vector<std::string> actual_list = list.components();

   EXPECT_EQ(expected_list, actual_list);
}
