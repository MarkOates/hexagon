
#include <gtest/gtest.h>

#include <Hexagon/RailsMinitestTestResultToCodeMessagePointConverter.hpp>

TEST(Hexagon_RailsMinitestTestResultToCodeMessagePointConverterTest, can_be_created_without_blowing_up)
{
   Hexagon::RailsMinitestTestResultToCodeMessagePointConverter rails_minitest_test_result_to_code_message_point_converter;
}

TEST(Hexagon_RailsMinitestTestResultToCodeMessagePointConverterTest, run__returns_the_expected_response)
{
   Hexagon::RailsMinitestTestResultToCodeMessagePointConverter rails_minitest_test_result_to_code_message_point_converter;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, rails_minitest_test_result_to_code_message_point_converter.run());
}
