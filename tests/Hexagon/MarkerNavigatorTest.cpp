
#include <gtest/gtest.h>

#include <Hexagon/MarkerNavigator.hpp>

TEST(Hexagon_MarkerNavigatorTest, can_be_created_without_blowing_up)
{
   Hexagon::MarkerNavigator marker_navigator;
}

TEST(Hexagon_MarkerNavigatorTest, run__returns_the_expected_response)
{
   Hexagon::MarkerNavigator marker_navigator;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, marker_navigator.run());
}
