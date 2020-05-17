
#include <gtest/gtest.h>

#include <Hexagon/ComponentNavigator/Stage.hpp>

TEST(Hexagon_ComponentNavigator_StageTest, run__returns_the_expected_response)
{
   Hexagon::ComponentNavigator::Stage stage;
   std::string expected_string = "Hello World!";

   stage.process_local_event("move_cursor_down");
   stage.process_local_event("move_cursor_down");
   stage.process_local_event("move_cursor_up");
   stage.process_local_event("move_cursor_up");
}

TEST(Hexagon_ComponentNavigator_StageTest, type__returns_the_expected_type)
{
   Hexagon::ComponentNavigator::Stage stage;
   StageInterface::type_t expected_type = StageInterface::COMPONENT_NAVIGATOR;

   ASSERT_EQ(expected_type, stage.get_type());
}

