
#include <gtest/gtest.h>

#include <Hexagon/ObjectivesLog/Stage.hpp>

TEST(Hexagon_ObjectivesLog_StageTest, can_be_created_without_blowing_up)
{
   Hexagon::ObjectivesLog::Stage stage;
}

TEST(Hexagon_ObjectivesLog_StageTest, render__does_not_blow_up)
{
   Hexagon::ObjectivesLog::Stage stage;
   std::string expected_string = "Hello World!";
   stage.render();
}
