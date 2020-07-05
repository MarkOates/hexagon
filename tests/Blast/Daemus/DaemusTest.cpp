
#include <gtest/gtest.h>

#include <Blast/Daemus/Daemus.hpp>

TEST(Blast_Daemus_DaemusTest, can_be_created_without_blowing_up)
{
   Blast::Daemus::Daemus daemus;
}

TEST(Blast_Daemus_DaemusTest, run_simple_echo_command__will_run_the_command)
{
   Blast::Daemus::Daemus daemus;

   testing::internal::CaptureStdout();
   daemus.run_simple_echo_command();
   std::string captured_cout_output = testing::internal::GetCapturedStdout();

   std::string expected_captured_cout_output = "hello";
   EXPECT_EQ(expected_captured_cout_output, captured_cout_output);
}

