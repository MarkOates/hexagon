
#include <gtest/gtest.h>

#include <Hexagon/Testing/ComponentTestRunner.hpp>

TEST(Hexagon_Testing_ComponentTestRunnerTest, can_be_created_without_blowing_up)
{
   Hexagon::Testing::ComponentTestRunner component_test_runner;
}

TEST(Hexagon_Testing_ComponentTestRunnerTest, run__returns_the_expected_response)
{
   std::string project_root = "/Users/markoates/Repos/hexagon/";
   std::string component = "Hexagon/RendererInterface";
   Hexagon::Testing::ComponentTestRunner component_test_runner(project_root, component);

   std::string expected_response_string = "Testing ...";
   std::string actual_response_string = component_test_runner.run();
   EXPECT_EQ(expected_response_string, actual_response_string);
}

TEST(Hexagon_Testing_ComponentTestRunnerTest, generate_make_run_test_command__returns_the_expectd_string)
{
   Hexagon::Testing::ComponentTestRunner component_test_runner;

   std::string expected_make_command
      = std::string("(")
      + "cd /Users/markoates/Repos/hexagon/ "
      + "&& make /Users/markoates/Repos/hexagon/bin/tests/Hexagon/UnnamedComponentTest"
      + ")"
      + "; /Users/markoates/Repos/hexagon/bin/tests/Hexagon/UnnamedComponentTest "
      + "&& echo FINAL_EXIT_CODE:$?"
      ;

   ASSERT_EQ(expected_make_command, component_test_runner.generate_make_run_test_command());
}

