
#include <gtest/gtest.h>

#include <Hexagon/ComponentNavigator/List.hpp>

TEST(Hexagon_ComponentNavigator_ListTest, run__returns_the_expected_response)
{
   Hexagon::ComponentNavigator::List list;
   std::vector<std::string> expected_list = {
     { "Hello World!" },
   };
   EXPECT_EQ(expected_list, list.components());
}
