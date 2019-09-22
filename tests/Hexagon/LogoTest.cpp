
#include <gtest/gtest.h>

#include <Hexagon/Logo.hpp>

TEST(Hexagon_LogoTest, run__returns_the_expected_response)
{
   Hexagon::Logo program_runner;
   std::string expected_string = "Hello World!";
   //EXPECT_EQ(expected_string, program_runner.run());
}
