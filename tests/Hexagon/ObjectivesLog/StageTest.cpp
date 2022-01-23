
#include <gtest/gtest.h>

#include <Hexagon/ObjectivesLog/Stage.hpp>

TEST(Hexagon_ObjectivesLog_StageTest, can_be_created_without_blowing_up)
{
   Hexagon::ObjectivesLog::Stage stage;
}

TEST(Hexagon_ObjectivesLog_StageTest, run__returns_the_expected_response)
{
   Hexagon::ObjectivesLog::Stage stage;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, stage.run());
}
