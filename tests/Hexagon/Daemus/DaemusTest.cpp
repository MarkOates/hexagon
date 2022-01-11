
#include <gtest/gtest.h>

#include <Hexagon/Daemus/Daemus.hpp>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

TEST(Hexagon_Daemus_DaemusTest, can_be_created_without_blowing_up)
{
   Hexagon::Daemus::Daemus daemus;
}

TEST(Hexagon_Daemus_DaemusTest, run_component_test__runs_the_test_executable_for_the_component)
   // TODO not a very complete test
{
   Blast::Project::Component component("Blast/String/Trimmer", "/Users/markoates/Repos/hexagon/");
   Hexagon::Daemus::Daemus daemus;
   daemus.run_component_test(component);
   SUCCEED();
}

TEST(Hexagon_Daemus_DaemusTest, run_component_test__returns_test_results)
{
   Blast::Project::Component component("Blast/String/Trimmer", "/Users/markoates/Repos/hexagon/");
   Hexagon::Daemus::Daemus daemus;
   std::vector<Hexagon::Testing::GoogleTestRunTestResult> test_results = daemus.run_component_test(component);

   EXPECT_EQ(false, test_results.empty());
}

TEST(Hexagon_Daemus_DaemusTest, run_component_test__returns_the_expected_data_in_the_returned_results)
{
   // TODO: make this test more comprehensive

   Blast::Project::Component component("Blast/String/Trimmer", "/Users/markoates/Repos/hexagon/");
   Hexagon::Daemus::Daemus daemus;
   std::vector<Hexagon::Testing::GoogleTestRunTestResult> actual_test_results = daemus.run_component_test(component);
   std::vector<Hexagon::Testing::GoogleTestRunTestResult> expected_test_results = {
      Hexagon::Testing::GoogleTestRunTestResult(
         "Blast_String_TrimmerTest",
         "can_be_created_without_arguments",
         "ok"
      )
   };

   EXPECT_EQ(expected_test_results[0].get_test_class_name(), actual_test_results[0].get_test_class_name());
   EXPECT_EQ(expected_test_results[0].get_test_description(), actual_test_results[0].get_test_description());
   EXPECT_EQ(expected_test_results[0].get_result(), actual_test_results[0].get_result());
}

TEST(Hexagon_Daemus_DaemusTest,
   run_component_test__when_the_component_project_directory_is_not_present__raises_an_error)
{
   Hexagon::Daemus::Daemus daemus;

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

TEST(Hexagon_Daemus_DaemusTest,
   run_component_test__when_the_component_does_not_exist__raises_an_error)
{
   Hexagon::Daemus::Daemus daemus;

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

TEST(Hexagon_Daemus_DaemusTest,
   run_build_quintessence_file__when_the_required_project_directory_is_not_present__raises_an_error)
{
   Hexagon::Daemus::Daemus daemus;
   std::string project_directory_that_does_not_exist = "/Users/markoates/Repos/project_that_does_not_exist";
   std::string expected_error_message = "Daemus::run_build_quintessence_file: error: the expected project directory " \
                                        "\"/Users/markoates/Repos/project_that_does_not_exist\" does not exist";
   ASSERT_THROW_WITH_MESSAGE(
      daemus.run_build_quintessence_file(project_directory_that_does_not_exist),
      std::runtime_error,
      expected_error_message
   );
}

TEST(Hexagon_Daemus_DaemusTest, run_build_quintessence_file__when_the_required_executable_is_not_present__raises_an_error)
{
   Hexagon::Daemus::Daemus daemus("/An/executable/that/does_not_exist");
   std::string project_directory = "/Users/markoates/Repos/hexagon/tests/fixtures/FixtureProject";
   std::string expected_error_message = "Daemus::run_build_quintessence_file: error: the expected executable " \
                                        "\"/An/executable/that/does_not_exist\" is not present";
   ASSERT_THROW_WITH_MESSAGE(
      daemus.run_build_quintessence_file(project_directory),
      std::runtime_error,
      expected_error_message
   );
}

TEST(Hexagon_Daemus_DaemusTest, run_build_quintessence_file__when_the_quintessence_file_is_not_present__raises_an_error)
{
   std::string quintessence_file_that_does_not_exist = "/Users/markoates/Foo/DoesNotExist.q.yml";
   std::string project_directory = "/Users/markoates/Repos/hexagon/tests/fixtures/FixtureProject";
   Hexagon::Daemus::Daemus daemus;
   std::string expected_error_message = "Daemus::run_build_quintessence_file: error: the quintessence file " \
                                        "\"/Users/markoates/Foo/DoesNotExist.q.yml\" does not exist";
   ASSERT_THROW_WITH_MESSAGE(
      daemus.run_build_quintessence_file(project_directory, quintessence_file_that_does_not_exist),
      std::runtime_error,
      expected_error_message
   );
}

TEST(Hexagon_Daemus_DaemusTest, run_build_quintessence_file__with_the_valid_required_dependencies__will_not_blow_up)
{
   std::string project_directory = "/Users/markoates/Repos/hexagon/tests/fixtures/FixtureProject";
   std::string quintessence_file = "quintessence/FixtureObjectThing.q.yml";

   Hexagon::Daemus::Daemus daemus;

   daemus.run_build_quintessence_file(project_directory, quintessence_file);

   SUCCEED();
}

TEST(Hexagon_Daemus_DaemusTest, run_build_quintessence_file__will_not_output_anything_to_stdout)
{
   std::string project_directory = "/Users/markoates/Repos/hexagon/tests/fixtures/FixtureProject";
   std::string quintessence_file = "quintessence/FixtureObjectThing.q.yml";

   Hexagon::Daemus::Daemus daemus;

   testing::internal::CaptureStdout();
   daemus.run_build_quintessence_file(project_directory, quintessence_file);
   std::string captured_cout_output = testing::internal::GetCapturedStdout();

   EXPECT_EQ(true, captured_cout_output.empty());
}

