
#include <gtest/gtest.h>

#include <Hexagon/RerunOutputWatcher.hpp>

TEST(Hexagon_RerunOutputWatcherTest, run__returns_the_expected_response)
{
   Hexagon::RerunOutputWatcher program_runner;
   std::string expected_string = "Hello World!";
   //EXPECT_EQ(expected_string, program_runner.run());
}
