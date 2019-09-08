
#include <gtest/gtest.h>

#include <Hexagon/StageLayout.hpp>

TEST(Hexagon__StageLayoutTest, run__returns_the_expected_response)
{
   Hexagon::StageLayout program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
