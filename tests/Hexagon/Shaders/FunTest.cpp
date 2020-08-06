
#include <gtest/gtest.h>

#include <Hexagon/Shaders/Fun.hpp>

TEST(Hexagon_Shaders_FunTest, can_be_created_without_blowing_up)
{
   Hexagon::Shaders::Fun fun;
}

TEST(Hexagon_Shaders_FunTest, run__returns_the_expected_response)
{
   Hexagon::Shaders::Fun fun;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, fun.run());
}
