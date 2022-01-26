
#include <gtest/gtest.h>

#include <Hexagon/MultiplexMenu/MultiplexMenu.hpp>

TEST(Hexagon_MultiplexMenu_MultiplexMenuTest, can_be_created_without_blowing_up)
{
   Hexagon::MultiplexMenu::MultiplexMenu multiplex_menu;
}

TEST(Hexagon_MultiplexMenu_MultiplexMenuTest, run__returns_the_expected_response)
{
   Hexagon::MultiplexMenu::MultiplexMenu multiplex_menu;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, multiplex_menu.run());
}
