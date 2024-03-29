
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/Daemus/ProgramRunner.hpp>
#include <filesystem> // for std::temp_directory_path()

#define BUILDS_FIXTURE_FOLDER_NAME "/Users/markoates/Repos/hexagon/tests/fixtures/data/builds"
#define FIXTURE_FOLDER_THAT_IS_EMPTY_BUT_HAS_A_DOT_KEEP_FILE \
   "/Users/markoates/Repos/hexagon/tests/fixtures/an_empty_directory_but_with_dot_keep_file"


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


TEST(Hexagon_Daemus_ProgramRunnerTest, run_simple_echo_command__will_run_the_command)
{
   Hexagon::Daemus::ProgramRunner daemus;

   testing::internal::CaptureStdout();
   daemus.run_simple_echo_command();
   std::string captured_cout_output = testing::internal::GetCapturedStdout();

   std::string expected_captured_cout_output = "hello";
   EXPECT_EQ(expected_captured_cout_output, captured_cout_output);
}


TEST(Hexagon_Daemus_ProgramRunnerTest, run_simple_sleep_command__will_run_the_command)
{
   Hexagon::Daemus::ProgramRunner daemus;

   testing::internal::CaptureStdout();
   daemus.run_simple_sleep_command();
   std::string captured_cout_output = testing::internal::GetCapturedStdout();

   std::string expected_captured_cout_output = "sleeping\ndone\n";
   EXPECT_EQ(expected_captured_cout_output, captured_cout_output);
}


TEST(Hexagon_Daemus_ProgramRunnerTest, run_component_test__runs_the_test_executable_for_the_component)
   // TODO not a very complete test
{
   // TODO: This test requires revision. See note in "__execute_command"
   Blast::Project::Component component("Blast/String/Trimmer", "/Users/markoates/Repos/hexagon/");
   Hexagon::Daemus::ProgramRunner daemus;
   daemus.run_component_test(component);
   SUCCEED();
}


TEST(Hexagon_Daemus_ProgramRunnerTest, run_component_test__returns_test_results)
{
   // TODO: This test requires revision. See note in "__execute_command"
   Blast::Project::Component component("Blast/String/Trimmer", "/Users/markoates/Repos/hexagon/");
   Hexagon::Daemus::ProgramRunner daemus;
   std::vector<Hexagon::Testing::GoogleTestRunTestResult> test_results = daemus.run_component_test(component);

   EXPECT_EQ(false, test_results.empty());
}


TEST(Hexagon_Daemus_ProgramRunnerTest, run_component_test__returns_the_expected_data_in_the_returned_results)
{
   // TODO: make this test more comprehensive
   // TODO: This test requires revision. See note in "__execute_command"

   Blast::Project::Component component("Blast/String/Trimmer", "/Users/markoates/Repos/hexagon/");
   Hexagon::Daemus::ProgramRunner daemus;
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


TEST(Hexagon_Daemus_ProgramRunnerTest,
   run_component_test__when_the_component_project_directory_is_not_present__raises_an_error)
{
   Hexagon::Daemus::ProgramRunner daemus;

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


TEST(Hexagon_Daemus_ProgramRunnerTest,
   run_component_test__when_the_component_does_not_exist__raises_an_error)
{
   Hexagon::Daemus::ProgramRunner daemus;

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


TEST(Hexagon_Daemus_ProgramRunnerTest,
   run_build_quintessence_file__when_the_required_project_directory_is_not_present__raises_an_error)
{
   Hexagon::Daemus::ProgramRunner daemus;
   std::string project_directory_that_does_not_exist = "/Users/markoates/Repos/project_that_does_not_exist";
   std::string expected_error_message = "Daemus::run_build_quintessence_file: error: the expected project directory " \
                                        "\"/Users/markoates/Repos/project_that_does_not_exist\" does not exist";
   ASSERT_THROW_WITH_MESSAGE(
      daemus.run_build_quintessence_file(project_directory_that_does_not_exist),
      std::runtime_error,
      expected_error_message
   );
}


TEST(Hexagon_Daemus_ProgramRunnerTest,
   find_oldest_filename__on_a_folder_that_does_not_exist__will_raise_an_exception)
{
   std::string folder_that_does_not_exist = "/This/is/a/folder/that/does/not/exist/hopefully/";
   std::string expected_error_message = "[Hexagon::Daemus::ProgramRunner::find_oldest_filename] error: "
                                        "The directory \"/This/is/a/folder/that/does/not/exist/hopefully/\" "
                                        "does not exist";
   ASSERT_THROW_WITH_MESSAGE(
      Hexagon::Daemus::ProgramRunner::find_oldest_filename(folder_that_does_not_exist),
      std::runtime_error,
      expected_error_message
   );
}


TEST(Hexagon_Daemus_ProgramRunnerTest,
   find_oldest_filename__when_no_files_are_present__returns_an_empty_string)
{
   std::string a_folder_that_is_empty_but_has_a_dot_keep_file = FIXTURE_FOLDER_THAT_IS_EMPTY_BUT_HAS_A_DOT_KEEP_FILE;
   std::string expected_dotfile_full_path = FIXTURE_FOLDER_THAT_IS_EMPTY_BUT_HAS_A_DOT_KEEP_FILE "/.keep";
   std::string actual_oldest_filename_path = Hexagon::Daemus::ProgramRunner::find_oldest_filename(
      a_folder_that_is_empty_but_has_a_dot_keep_file,
      false
   );

   EXPECT_EQ(expected_dotfile_full_path, actual_oldest_filename_path);
}


TEST(Hexagon_Daemus_ProgramRunnerTest,
   find_oldest_filename__when_no_files_are_present_or_dotfiles__returns_an_empty_string)
{
   std::string a_folder_that_is_empty_but_has_a_dot_keep_file = FIXTURE_FOLDER_THAT_IS_EMPTY_BUT_HAS_A_DOT_KEEP_FILE;
   EXPECT_EQ("", Hexagon::Daemus::ProgramRunner::find_oldest_filename(a_folder_that_is_empty_but_has_a_dot_keep_file));
}


TEST(Hexagon_Daemus_ProgramRunnerTest,
   find_oldest_filename__returns_the_oldest_file_in_the_directory)
{
   std::string folder_to_look_in = std::string(BUILDS_FIXTURE_FOLDER_NAME) + "/pending";
   std::string expected_oldest_file = folder_to_look_in + "/file_created_at_12_38.txt";

   std::string actual_oldest_file = Hexagon::Daemus::ProgramRunner::find_oldest_filename(folder_to_look_in);
   ASSERT_EQ(expected_oldest_file, actual_oldest_file);
}


