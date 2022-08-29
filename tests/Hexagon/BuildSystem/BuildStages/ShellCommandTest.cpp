
#include <gtest/gtest.h>

#include <Hexagon/BuildSystem/BuildStages/ShellCommand.hpp>


TEST(Hexagon_BuildSystem_BuildStages_ShellCommandTest, can_be_created_without_blowing_up)
{
   Hexagon::BuildSystem::BuildStages::ShellCommand shell_command;
}


TEST(Hexagon_BuildSystem_BuildStages_ShellCommandTest, has_the_expected_type)
{
   Hexagon::BuildSystem::BuildStages::ShellCommand shell_command;
   EXPECT_EQ("ShellCommand", shell_command.get_type());
}


TEST(Hexagon_BuildSystem_BuildStages_ShellCommandTest,
   execute_raw__will_execute_the_shell_command_and_capture_the_result)
{
   std::string shell_command = "printf \"this is test output\"";
   Hexagon::BuildSystem::BuildStages::ShellCommand shell_command_build_stage(shell_command);

   shell_command_build_stage.execute_raw();

   EXPECT_EQ("this is test output", shell_command_build_stage.get_shell_command_result());
}


