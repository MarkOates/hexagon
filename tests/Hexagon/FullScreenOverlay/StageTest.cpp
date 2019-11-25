
#include <gtest/gtest.h>

#include <Hexagon/FullScreenOverlay/Stage.hpp>

TEST(Hexagon_FullScreenOverlay_StageTest, run__returns_the_expected_response)
{
   Hexagon::FullScreenOverlay::Stage program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
