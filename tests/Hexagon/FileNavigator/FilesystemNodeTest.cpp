
#include <gtest/gtest.h>

#include <Hexagon/FileNavigator/FileystemNode.hpp>

TEST(Hexagon_FileNavigator_FileystemNodeTest, run__returns_the_expected_response)
{
   Hexagon::FileNavigator::FileystemNode program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
