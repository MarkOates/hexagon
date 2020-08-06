
#include <gtest/gtest.h>

#include <Hexagon/Shaders/Base.hpp>

TEST(Hexagon_Shaders_BaseTest, can_be_created_without_blowing_up)
{
   Hexagon::Shaders::Base base;
}

TEST(Hexagon_Shaders_BaseTest, run__returns_the_expected_response)
{
   Hexagon::Shaders::Base base;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, base.run());
}
