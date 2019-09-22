
#include <gtest/gtest.h>

#include <Hexagon/FileNavigator.hpp>

TEST(Hexagon_FileNavigatorTest, run__returns_the_expected_response)
{
   FileNavigator program_runner(".");
   std::string expected_string = "Hello World!";
   //EXPECT_EQ(expected_string, program_runner.run());
}

