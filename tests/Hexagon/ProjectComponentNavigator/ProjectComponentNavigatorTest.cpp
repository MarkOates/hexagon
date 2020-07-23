
#include <gtest/gtest.h>

#include <Hexagon/ProjectComponentNavigator/ProjectComponentNavigator.hpp>


TEST(Hexagon_ProjectComponentNavigator_ProjectComponentNavigatorTest, can_be_created_without_blowing_up)
{
   Hexagon::ProjectComponentNavigator::ProjectComponentNavigator advanced_component_navigator;
}


TEST(Hexagon_ProjectComponentNavigator_ProjectComponentNavigatorTest,
   mode__has_a_getter_that_is_set_to_the_expected_default_value)
{
   Hexagon::ProjectComponentNavigator::ProjectComponentNavigator advanced_component_navigator;
   ASSERT_EQ("navigating_list", advanced_component_navigator.get_mode());
}


TEST(Hexagon_ProjectComponentNavigator_ProjectComponentNavigatorTest,
   is_mode_navigating_list__returns_true_if_mode_is_currently_navigating_list)
{
   Hexagon::ProjectComponentNavigator::ProjectComponentNavigator advanced_component_navigator;
   advanced_component_navigator.set_mode_to_navigating_list();
   ASSERT_EQ(true, advanced_component_navigator.is_mode_navigating_list());
}


TEST(DISABLED_Hexagon_ProjectComponentNavigator_ProjectComponentNavigatorTest,
   is_mode_navigating_list__returns_false_if_mode_is_currently_navigating_list)
{
   Hexagon::ProjectComponentNavigator::ProjectComponentNavigator advanced_component_navigator;
   advanced_component_navigator.set_mode_to_typing_in_search_bar();
   ASSERT_EQ(false, advanced_component_navigator.is_mode_navigating_list());
}


