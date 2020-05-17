
#include <gtest/gtest.h>

#include <Hexagon/AdvancedComponentNavigator/List.hpp>

#include <gmock/gmock.h>
using ::testing::IsSupersetOf;

TEST(Hexagon_AdvancedComponentNavigator_ListTest, component_names__returns_the_expected_response)
{
   std::string project_root_directory = "/Users/markoates/Repos/blast";
   Hexagon::AdvancedComponentNavigator::List list(project_root_directory);

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

   std::vector<std::string> actual_list = list.component_names();

   EXPECT_THAT(actual_list, IsSupersetOf(actual_list));
}

