
#include <gtest/gtest.h>

#include <Hexagon/FileNavigator/Stage.hpp>

TEST(Hexagon_FileNavigator_StageTest, run__returns_the_expected_response)
{
   Hexagon::FileNavigator::Stage stage;
   std::string expected_string = "Hello World!";

   stage.process_local_event("move_cursor_down");
   stage.process_local_event("move_cursor_down");
   stage.process_local_event("move_cursor_up");
   stage.process_local_event("move_cursor_up");
}
