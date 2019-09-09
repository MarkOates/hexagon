
#include <gtest/gtest.h>

#include <RailsTestOutputParser.hpp>

TEST(RailsTestOutputParserTest, run__returns_the_expected_response)
{
   RailsTestOutputParser program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
