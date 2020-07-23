
#include <gtest/gtest.h>

#include <Hexagon/ProjectComponentNavigator/Stage.hpp>


TEST(Hexagon_ProjectComponentNavigator_StageTest, type__returns_the_expected_type)
{
   Hexagon::ProjectComponentNavigator::Stage stage;
   StageInterface::type_t expected_type = StageInterface::PROJECT_COMPONENT_NAVIGATOR;

   ASSERT_EQ(expected_type, stage.get_type());
}


TEST(Hexagon_ProjectComponentNavigator_StageTest, filter_list_with_search_text__returns_filtered_list)
{
}


TEST(Hexagon_ProjectComponentNavigator_StageTest, process_local_event__processes_the_events)
{
   Hexagon::ProjectComponentNavigator::Stage stage;
   Hexagon::ProjectComponentNavigator::ProjectComponentNavigator &component = stage.get_component_ref();

   stage.process_local_event("move_cursor_down");
   stage.process_local_event("move_cursor_down");
   stage.process_local_event("move_cursor_down");
   stage.process_local_event("move_cursor_up");

   ASSERT_EQ(2, component.get_cursor_position());
}


TEST(Hexagon_ProjectComponentNavigator_StageTest, mode__is_initialized_to_navigating_list)
{
   Hexagon::ProjectComponentNavigator::Stage stage;
   Hexagon::ProjectComponentNavigator::ProjectComponentNavigator &component = stage.get_component_ref();
   ASSERT_EQ("navigating_list", component.get_mode());
}


TEST(Hexagon_ProjectComponentNavigator_StageTest, process_local_event__processes_the_expected_events)
{
   Hexagon::ProjectComponentNavigator::Stage stage;
   Hexagon::ProjectComponentNavigator::ProjectComponentNavigator &component = stage.get_component_ref();

   stage.process_local_event("set_mode_to_navigating_list");
   ASSERT_EQ("navigating_list", component.get_mode());

   stage.process_local_event("set_mode_to_typing_in_search_bar");
   ASSERT_EQ("typing_in_search_bar", component.get_mode());
}


