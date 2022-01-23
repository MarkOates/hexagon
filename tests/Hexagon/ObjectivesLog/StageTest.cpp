
#include <gtest/gtest.h>

#include <Hexagon/ObjectivesLog/Stage.hpp>

TEST(Hexagon_ObjectivesLog_StageTest, can_be_created_without_blowing_up)
{
   Hexagon::ObjectivesLog::Stage stage;
}

TEST(Hexagon_ObjectivesLog_StageTest, render__returns_the_expected_response)
{
   Hexagon::ObjectivesLog::Stage stage;
   stage.render();
   SUCCEED();
}

TEST(Hexagon_ObjectivesLog_StageTest, process_local_event__does_not_blow_up)
{
   Hexagon::ObjectivesLog::Stage stage;
   stage.process_local_event();
   SUCCEED();
}

TEST(Hexagon_ObjectivesLog_StageTest, process_event__does_not_blow_up)
{
   Hexagon::ObjectivesLog::Stage stage;
   stage.process_event();
   SUCCEED();
}

