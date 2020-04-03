
#include <gtest/gtest.h>

#include <Hexagon/System/Action/OpenConfigFile.hpp>

TEST(Hexagon_System_Action_OpenConfigFileTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Action::OpenConfigFile open_config_file;
}

TEST(Hexagon_System_Action_OpenConfigFileTest, run__returns_the_expected_response)
{
   Hexagon::System::Action::OpenConfigFile open_config_file;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, open_config_file.run());
}
