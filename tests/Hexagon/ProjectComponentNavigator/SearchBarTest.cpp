
#include <gtest/gtest.h>

#include <Hexagon/ProjectComponentNavigator/SearchBar.hpp>

TEST(Hexagon_ProjectComponentNavigator_SearchBarTest, can_be_created_without_blowing_up)
{
   Hexagon::ProjectComponentNavigator::SearchBar search_bar;
}

TEST(Hexagon_ProjectComponentNavigator_SearchBarTest, run__returns_the_expected_response)
{
   Hexagon::ProjectComponentNavigator::SearchBar search_bar;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, search_bar.run());
}
