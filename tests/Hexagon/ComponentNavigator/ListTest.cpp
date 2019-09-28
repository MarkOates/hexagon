
#include <gtest/gtest.h>

#include <Hexagon/ComponentNavigator/List.hpp>

TEST(Hexagon_ComponentNavigator_ListTest, run__returns_the_expected_response)
{
   Hexagon::ComponentNavigator::List list;
   std::vector<std::string> expected_list = {
      "Hexagon/RerunOutputWatcher",
      "Hexagon/RailsTestOutputParser",
      "Hexagon/LayoutPlacements",
      "Hexagon/Logo",
      "Hexagon/RegexStore",
      "Hexagon/ComponentNavigator/List",
      "Hexagon/FileNavigator/Stage",
      "Hexagon/FileNavigator/FileystemNode",
      "Hexagon/LayoutFromYAML",
      "NcursesArt/ProjectComponentBasenameExtractor",
      "Blast/ShellCommandExecutorWithCallback",
   };

   EXPECT_EQ(expected_list, list.components());
}
