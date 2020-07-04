
#include <gtest/gtest.h>

#include <Hexagon/Testing/GoogleTestRunOutputParser.hpp>

TEST(Hexagon_Testing_GoogleTestRunOutputParserTest, can_be_created_without_blowing_up)
{
   Hexagon::Testing::GoogleTestRunOutputParser google_test_run_output_parser;
}

TEST(Hexagon_Testing_GoogleTestRunOutputParserTest, run__returns_the_expected_response)
{
   Hexagon::Testing::GoogleTestRunOutputParser google_test_run_output_parser;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, google_test_run_output_parser.run());
}
