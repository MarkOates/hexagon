
#include <gtest/gtest.h>

#include <Hexagon/AdvancedComponentNavigator/AdvancedComponentNavigator.hpp>

TEST(Hexagon_AdvancedComponentNavigator_AdvancedComponentNavigatorTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator advanced_component_navigator;
}

TEST(Hexagon_AdvancedComponentNavigator_AdvancedComponentNavigatorTest, run__returns_the_expected_response)
{
   Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator advanced_component_navigator;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, advanced_component_navigator.run());
}
