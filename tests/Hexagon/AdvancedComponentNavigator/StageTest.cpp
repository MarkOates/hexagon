
#include <gtest/gtest.h>

#include <Hexagon/AdvancedComponentNavigator/Stage.hpp>

TEST(Hexagon_AdvancedComponentNavigator_StageTest, run__returns_the_expected_response)
{
   Hexagon::AdvancedComponentNavigator::Stage stage;
   std::string expected_string = "Hello World!";

   stage.process_local_event("move_cursor_down");
   stage.process_local_event("move_cursor_down");
   stage.process_local_event("move_cursor_up");
   stage.process_local_event("move_cursor_up");
}

TEST(Hexagon_AdvancedComponentNavigator_StageTest, type__returns_the_expected_type)
{
   Hexagon::AdvancedComponentNavigator::Stage stage;
   StageInterface::type_t expected_type = StageInterface::COMPONENT_NAVIGATOR;

   ASSERT_EQ(expected_type, stage.get_type());
}

TEST(Hexagon_AdvancedComponentNavigator_StageTest, filter_list_with_search_string__returns_filtered_list)
{
   Hexagon::AdvancedComponentNavigator::Stage stage;
   StageInterface::type_t expected_type = StageInterface::COMPONENT_NAVIGATOR;

   ASSERT_EQ(expected_type, stage.get_type());
}

