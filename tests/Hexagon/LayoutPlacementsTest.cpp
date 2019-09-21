
#include <gtest/gtest.h>

#include <Hexagon/LayoutPlacements.hpp>

TEST(Hexagon__LayoutPlacementsTest, run__returns_the_expected_response)
{
   Hexagon::LayoutPlacements program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
