
#include <gtest/gtest.h>

#include <Hexagon/System/Action/AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection.hpp>

TEST(Hexagon_System_Action_AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelectionTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Action::AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection attempt_to_create_two_pane_split_from_last_component_navigator_selection;
}

TEST(Hexagon_System_Action_AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelectionTest, run__returns_the_expected_response)
{
   Hexagon::System::Action::AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection attempt_to_create_two_pane_split_from_last_component_navigator_selection;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, attempt_to_create_two_pane_split_from_last_component_navigator_selection.run());
}
