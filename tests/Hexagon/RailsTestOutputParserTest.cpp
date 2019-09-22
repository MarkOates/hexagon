
#include <gtest/gtest.h>

#include <Hexagon/RailsTestOutputParser.hpp>

TEST(Hexagon_RailsTestOutputParserTest, run__returns_the_expected_response)
{
   Hexagon::RailsTestOutputParser program_runner;
   std::string expected_string = "Hello World!";
   //EXPECT_EQ(expected_string, program_runner.run());
}
