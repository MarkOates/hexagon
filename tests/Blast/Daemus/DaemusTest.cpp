
#include <gtest/gtest.h>

#include <Blast/Daemus/Daemus.hpp>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

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

TEST(Blast_Daemus_DaemusTest, run_simple_sleep_command__will_run_the_command)
{
   Blast::Daemus::Daemus daemus;

   testing::internal::CaptureStdout();
   daemus.run_simple_sleep_command();
   std::string captured_cout_output = testing::internal::GetCapturedStdout();

   std::string expected_captured_cout_output = "sleeping\ndone\n";
   EXPECT_EQ(expected_captured_cout_output, captured_cout_output);
}

TEST(Blast_Daemus_DaemusTest,
   run_build_quintessence_file__when_the_required_project_directory_is_not_present__raises_an_error)
{
   Blast::Daemus::Daemus daemus;
   std::string project_directory_that_does_not_exist = "/Users/markoates/Repos/project_that_does_not_exist";
   std::string expected_error_message = "Daemus::run_build_quintessence_file: error: the expected project directory " \
                                        "\"/Users/markoates/Repos/project_that_does_not_exist\" does not exist";
   ASSERT_THROW_WITH_MESSAGE(
      daemus.run_build_quintessence_file(project_directory_that_does_not_exist),
      std::runtime_error,
      expected_error_message
   );
}

TEST(Blast_Daemus_DaemusTest, run_build_quintessence_file__when_the_required_executable_is_not_present__raises_an_error)
{
   Blast::Daemus::Daemus daemus("/An/executable/that/does_not_exist");
   std::string project_directory = "/Users/markoates/Repos/hexagon/tests/fixtures/FixtureProject/quintessence/";
   std::string expected_error_message = "Daemus::run_build_quintessence_file: error: the expected executable " \
                                        "\"/An/executable/that/does_not_exist\" is not present";
   ASSERT_THROW_WITH_MESSAGE(
      daemus.run_build_quintessence_file(project_directory),
      std::runtime_error,
      expected_error_message
   );
}

TEST(Blast_Daemus_DaemusTest, run_build_quintessence_file__when_the_quintessence_file_is_not_present__raises_an_error)
{
   std::string quintessence_file_that_does_not_exist = "/Users/markoates/Foo/DoesNotExist.q.yml";
   std::string project_directory = "/Users/markoates/Repos/hexagon/tests/fixtures/FixtureProject/quintessence/";
   Blast::Daemus::Daemus daemus;
   std::string expected_error_message = "Daemus::run_build_quintessence_file: error: the quintessence file " \
                                        "\"/Users/markoates/Foo/DoesNotExist.q.yml\" does not exist";
   ASSERT_THROW_WITH_MESSAGE(
      daemus.run_build_quintessence_file(project_directory, quintessence_file_that_does_not_exist),
      std::runtime_error,
      expected_error_message
   );
}

