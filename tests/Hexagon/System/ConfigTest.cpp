
#include <gtest/gtest.h>

#include <Hexagon/System/Config.hpp>

TEST(Hexagon_System_ConfigTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Config config;
}

TEST(Hexagon_System_ConfigTest, run__returns_the_expected_response)
{
   Hexagon::System::Config config;
   //std::string expected_string = "Hello World!";
   //EXPECT_EQ(expected_string, config.run());
}
