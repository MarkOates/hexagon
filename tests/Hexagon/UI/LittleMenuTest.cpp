
#include <gtest/gtest.h>

#include <Hexagon/UI/LittleMenu.hpp>

TEST(Hexagon_UI_LittleMenuTest, can_be_created_without_blowing_up)
{
   Hexagon::UI::LittleMenu little_menu;
}

TEST(Hexagon_UI_LittleMenuTest, run__returns_the_expected_response)
{
   Hexagon::UI::LittleMenu little_menu;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, little_menu.run());
}
