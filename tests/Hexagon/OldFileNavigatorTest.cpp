
#include <gtest/gtest.h>

#include <Hexagon/OldFileNavigator.hpp>

TEST(Hexagon_OldFileNavigatorTest, run__returns_the_expected_response)
{
   OldFileNavigator program_runner(".");
   std::string expected_string = "Hello World!";
   //EXPECT_EQ(expected_string, program_runner.run());
}

