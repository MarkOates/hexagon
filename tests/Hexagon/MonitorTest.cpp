
#include <gtest/gtest.h>

#include <Hexagon/Monitor.hpp>


TEST(Hexagon_MonitorTest, can_be_created_without_blowing_up)
{
   Hexagon::Monitor monitor;
}


TEST(Hexagon_MonitorTest, run__returns_the_expected_response)
{
   Hexagon::Monitor monitor;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, monitor.run());
}


