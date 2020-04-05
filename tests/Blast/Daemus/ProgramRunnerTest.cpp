
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

