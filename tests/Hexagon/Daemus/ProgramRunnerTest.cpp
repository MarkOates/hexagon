
#include <gtest/gtest.h>

#include <Hexagon/Daemus/ProgramRunner.hpp>

TEST(Hexagon_Daemus_ProgramRunnerTest, can_be_created_without_blowing_up)
{
   Hexagon::Daemus::ProgramRunner program_runner;
}

TEST(Hexagon_Daemus_ProgramRunnerTest, run__runs_the_expected_command)
{
   Hexagon::Daemus::ProgramRunner program_runner;
   //Blast::Daemus::ProgramRunner program_runner;
   //program_runner.run();
   //FAIL();
}

TEST(Hexagon_Daemus_ProgramRunnerTest, run_in_holding_pattern__runs_in_a_suspended_state_waiting_for_command_to_execute)
{
   Hexagon::Daemus::ProgramRunner program_runner;
   // incomplete test
}

