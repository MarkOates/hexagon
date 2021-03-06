
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

TEST(Blast_Daemus_DaemusTest, run_component_test__runs_the_test_executable_for_the_component)
   // not a very complete test
{
   Blast::Project::Component component("Blast/String/Trimmer", "/Users/markoates/Repos/hexagon/");
   Blast::Daemus::Daemus daemus;
   daemus.run_component_test(component);
   SUCCEED();
}

TEST(Blast_Daemus_DaemusTest, run_component_test__returns_test_results)
{
   Blast::Project::Component component("Blast/String/Trimmer", "/Users/markoates/Repos/hexagon/");
   Blast::Daemus::Daemus daemus;
   std::vector<Hexagon::Testing::GoogleTestRunTestResult> test_results = daemus.run_component_test(component);

   EXPECT_EQ(false, test_results.empty());
}

TEST(Blast_Daemus_DaemusTest,
   run_component_test__when_the_component_project_directory_is_not_present__raises_an_error)
{
   Blast::Daemus::Daemus daemus;

   std::string project_directory_that_does_not_exist = "/Users/markoates/Repos/project_that_does_not_exist";
   Blast::Project::Component component("Component/Does/Not/Exist", project_directory_that_does_not_exist);
   std::string expected_error_message = "Daemus::run_component_test: error: the expected project directory " \
                                        "\"/Users/markoates/Repos/project_that_does_not_exist\" does not exist";
   ASSERT_THROW_WITH_MESSAGE(
      daemus.run_component_test(component),
      std::runtime_error,
      expected_error_message
   );
}

TEST(Blast_Daemus_DaemusTest,
   run_component_test__when_the_component_does_not_exist__raises_an_error)
{
   Blast::Daemus::Daemus daemus;

   std::string project_directory = "/Users/markoates/Repos/hexagon/";
   Blast::Project::Component component("Component/Does/Not/Exist", project_directory);
   std::string expected_error_message = "Daemus::run_component_test: error: the test binary " \
                                        "\"/Users/markoates/Repos/hexagon/bin/tests/Component/Does/Not/ExistTest\" " \
                                        "does not exist";
   ASSERT_THROW_WITH_MESSAGE(
      daemus.run_component_test(component),
      std::runtime_error,
      expected_error_message
   );
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
   std::string project_directory = "/Users/markoates/Repos/hexagon/tests/fixtures/FixtureProject";
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
   std::string project_directory = "/Users/markoates/Repos/hexagon/tests/fixtures/FixtureProject";
   Blast::Daemus::Daemus daemus;
   std::string expected_error_message = "Daemus::run_build_quintessence_file: error: the quintessence file " \
                                        "\"/Users/markoates/Foo/DoesNotExist.q.yml\" does not exist";
   ASSERT_THROW_WITH_MESSAGE(
      daemus.run_build_quintessence_file(project_directory, quintessence_file_that_does_not_exist),
      std::runtime_error,
      expected_error_message
   );
}

TEST(Blast_Daemus_DaemusTest, run_build_quintessence_file__with_the_valid_required_dependencies__will_not_blow_up)
{
   std::string project_directory = "/Users/markoates/Repos/hexagon/tests/fixtures/FixtureProject";
   std::string quintessence_file = "quintessence/FixtureObjectThing.q.yml";

   Blast::Daemus::Daemus daemus;

   daemus.run_build_quintessence_file(project_directory, quintessence_file);

   SUCCEED();
}

TEST(Blast_Daemus_DaemusTest, run_build_quintessence_file__will_not_output_anything_to_stdout)
{
   std::string project_directory = "/Users/markoates/Repos/hexagon/tests/fixtures/FixtureProject";
   std::string quintessence_file = "quintessence/FixtureObjectThing.q.yml";

   Blast::Daemus::Daemus daemus;

   testing::internal::CaptureStdout();
   daemus.run_build_quintessence_file(project_directory, quintessence_file);
   std::string captured_cout_output = testing::internal::GetCapturedStdout();

   EXPECT_EQ(true, captured_cout_output.empty());
}

