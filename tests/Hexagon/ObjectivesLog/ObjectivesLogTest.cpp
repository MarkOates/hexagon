
#include <gtest/gtest.h>

#include <Hexagon/ObjectivesLog/ObjectivesLog.hpp>

TEST(Hexagon_ObjectivesLog_ObjectivesLogTest, can_be_created_without_blowing_up)
{
   Hexagon::ObjectivesLog::ObjectivesLog objectives_log;
}

TEST(Hexagon_ObjectivesLog_ObjectivesLogTest, run__returns_the_expected_response)
{
   Hexagon::ObjectivesLog::ObjectivesLog objectives_log;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, objectives_log.run());
}
