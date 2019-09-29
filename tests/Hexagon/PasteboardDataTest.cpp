
#include <gtest/gtest.h>

#include <Hexagon/PasteboardData.hpp>

TEST(Hexagon_PasteboardDataTest, run__returns_the_expected_response)
{
   Hexagon::PasteboardData program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
