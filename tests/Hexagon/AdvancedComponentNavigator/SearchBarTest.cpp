
#include <gtest/gtest.h>

#include <Hexagon/AdvancedComponentNavigator/SearchBar.hpp>

TEST(Hexagon_AdvancedComponentNavigator_SearchBarTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedComponentNavigator::SearchBar search_bar;
}

TEST(Hexagon_AdvancedComponentNavigator_SearchBarTest, run__returns_the_expected_response)
{
   Hexagon::AdvancedComponentNavigator::SearchBar search_bar;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, search_bar.run());
}
