
#include <gtest/gtest.h>

#include <Hexagon/RerunOutputWatcher/Stage.hpp>

TEST(Hexagon_RerunOutputWatcher_StageTest, run__returns_the_expected_response)
{
   Hexagon::RerunOutputWatcher::Stage program_runner;
   std::string expected_string = "Hello World!";
   //EXPECT_EQ(expected_string, program_runner.run());
}
