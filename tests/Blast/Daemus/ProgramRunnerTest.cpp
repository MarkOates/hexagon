
#include <gtest/gtest.h>

#include <Blast/Daemus/ProgramRunner.hpp>

TEST(Blast_Daemus_ProgramRunnerTest, can_be_created_without_blowing_up)
{
   Blast::Daemus::ProgramRunner program_runner;
}

TEST(Blast_Daemus_ProgramRunnerTest, run__runs_the_expected_command)
{
   Blast::Daemus::ProgramRunner program_runner;
   //Blast::Daemus::ProgramRunner program_runner;
   //program_runner.run();
   //FAIL();
}

TEST(Blast_Daemus_ProgramRunnerTest, run_in_holding_pattern__runs_in_a_suspended_state_waiting_for_command_to_execute)
{
   Blast::Daemus::ProgramRunner program_runner;
   // incomplete test
}

