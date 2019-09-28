
#include <gtest/gtest.h>

#include <Hexagon/ComponentNavigator/List.hpp>

TEST(Hexagon_ComponentNavigator_ListTest, run__returns_the_expected_response)
{
   std::string project_root_directory = "/Users/markoates/Repos/blast";
   Hexagon::ComponentNavigator::List list(project_root_directory);

   std::vector<std::string> expected_list = {
      "Hexagon/RerunOutputWatcher",
      "Hexagon/RailsTestOutputParser",
      "Hexagon/LayoutPlacements",
      "Hexagon/Logo",
      "Hexagon/RegexStore",
      "Hexagon/ComponentNavigator/List",
      "Hexagon/ComponentNavigator/Stage",
      "Hexagon/FileNavigator/Stage",
      "Hexagon/FileNavigator/FileystemNode",
      "Hexagon/LayoutFromYAML",
      "NcursesArt/ProjectComponentBasenameExtractor",
      "Blast/ShellCommandExecutorWithCallback",
   };
   std::vector<std::string> actual_list = list.components();

   EXPECT_EQ(expected_list, actual_list);
}
