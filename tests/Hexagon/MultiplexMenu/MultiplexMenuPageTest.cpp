
#include <gtest/gtest.h>

#include <Hexagon/MultiplexMenu/MultiplexMenuPage.hpp>


TEST(Hexagon_MultiplexMenu_MultiplexMenuPageTest, can_be_created_without_blowing_up)
{
   Hexagon::MultiplexMenu::MultiplexMenuPage multiplex_menu_page;
}


TEST(Hexagon_MultiplexMenu_MultiplexMenuPageTest, run__returns_the_expected_response)
{
   Hexagon::MultiplexMenu::MultiplexMenuPage multiplex_menu_page;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, multiplex_menu_page.run());
}

