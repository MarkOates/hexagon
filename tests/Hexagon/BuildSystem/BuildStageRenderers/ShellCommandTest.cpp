
#include <gtest/gtest.h>

#include <Hexagon/BuildSystem/BuildStageRenderers/ShellCommand.hpp>


TEST(Hexagon_BuildSystem_BuildStageRenderers_ShellCommandTest, can_be_created_without_blowing_up)
{
   Hexagon::BuildSystem::BuildStageRenderers::ShellCommand shell_command;
}


TEST(Hexagon_BuildSystem_BuildStageRenderers_ShellCommandTest, has_the_expected_type)
{
   Hexagon::BuildSystem::BuildStageRenderers::ShellCommand shell_command;
   EXPECT_EQ("ShellCommand", shell_command.get_type());
}


