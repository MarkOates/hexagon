
#include <gtest/gtest.h>

#include <Hexagon/Elements/ListMenu.hpp>

TEST(Hexagon_Elements_ListMenuTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::ListMenu list_menu;
}

TEST(Hexagon_Elements_ListMenuTest, run__returns_the_expected_response)
{
   Hexagon::Elements::ListMenu list_menu;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, list_menu.run());
}
