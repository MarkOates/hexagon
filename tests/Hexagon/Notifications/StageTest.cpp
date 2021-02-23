
#include <gtest/gtest.h>

#include <Hexagon/Notifications/Stage.hpp>

TEST(Hexagon_Notifications_StageTest, can_be_created_without_blowing_up)
{
   Hexagon::Notifications::Stage stage;
}

TEST(Hexagon_Notifications_StageTest, render__returns_the_expected_response)
{
   Hexagon::Notifications::Stage stage;
   stage.render();
   SUCCEED();
}

TEST(Hexagon_Notifications_StageTest, process_local_event__does_not_blow_up)
{
   Hexagon::Notifications::Stage stage;
   stage.process_local_event();
   SUCCEED();
}

TEST(Hexagon_Notifications_StageTest, process_event__does_not_blow_up)
{
   Hexagon::Notifications::Stage stage;
   stage.process_event();
   SUCCEED();
}
