
#include <gtest/gtest.h>

#include <Hexagon/Testing/GoogleTestRunOutputParser.hpp>

const std::string BASIC_TEST_RUN_OUTPUT = R"TEST_FIXTURE(
make[1]: Nothing to be done for `/Users/markoates/Repos/hexagon/bin/tests/Hexagon/Elements/StageInfoOverlayTest'.
[==========] Running 5 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 1 test from Hexagon_Elements_StageInfoOverlayTest
[ RUN      ] Hexagon_Elements_StageInfoOverlayTest.can_be_created_without_blowing_up
[       OK ] Hexagon_Elements_StageInfoOverlayTest.can_be_created_without_blowing_up (123 ms)
[----------] 1 test from Hexagon_Elements_StageInfoOverlayTest (0 ms total)

[----------] 4 tests from Hexagon_Elements_StageInforOverlayTest
[ RUN      ] Hexagon_Elements_StageInforOverlayTest.text__has_getters_and_setters
[       OK ] Hexagon_Elements_StageInforOverlayTest.text__has_getters_and_setters (0 ms)
[ RUN      ] Hexagon_Elements_StageInforOverlayTest.render__without_a_valid_backfill_color__throws_an_error
[       OK ] Hexagon_Elements_StageInforOverlayTest.render__without_a_valid_backfill_color__throws_an_error (0 ms)
[ RUN      ] Hexagon_Elements_StageInforOverlayTest.render__without_a_valid_title_font__throws_an_error
[       OK ] Hexagon_Elements_StageInforOverlayTest.render__without_a_valid_title_font__throws_an_error (0 ms)
[ RUN      ] Hexagon_Elements_StageInforOverlayTest.render__with_valid_dependencies__does_not_blow_up
[       OK ] Hexagon_Elements_StageInforOverlayTest.render__with_valid_dependencies__does_not_blow_up (131 ms)
[----------] 4 tests from Hexagon_Elements_StageInforOverlayTest (131 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 2 test suites ran. (131 ms total)
[  PASSED  ] 5 tests.
FINAL_EXIT_CODE:0
)TEST_FIXTURE";


TEST(Hexagon_Testing_GoogleTestRunOutputParserTest, can_be_created_without_blowing_up)
{
   Hexagon::Testing::GoogleTestRunOutputParser google_test_run_output_parser;
}

TEST(Hexagon_Testing_GoogleTestRunOutputParserTest, parse__returns_the_expected_number_of_test_results)
{
   Hexagon::Testing::GoogleTestRunOutputParser google_test_run_output_parser(BASIC_TEST_RUN_OUTPUT);
   std::vector<Hexagon::Testing::GoogleTestRunTestResult> results = google_test_run_output_parser.parse();
   ASSERT_EQ(5, results.size());
}

TEST(Hexagon_Testing_GoogleTestRunOutputParserTest, parse__returns_the_correctly_named_test_class)
{
   Hexagon::Testing::GoogleTestRunOutputParser google_test_run_output_parser(BASIC_TEST_RUN_OUTPUT);
   std::vector<Hexagon::Testing::GoogleTestRunTestResult> results = google_test_run_output_parser.parse();

   ASSERT_EQ(false, results.empty());

   Hexagon::Testing::GoogleTestRunTestResult first_test_result = results[0];

   std::string expected_result_class_name = "Hexagon_Elements_StageInfoOverlayTest";
   std::string actual_result_class_name = first_test_result.get_test_class_name();

   EXPECT_EQ(expected_result_class_name, actual_result_class_name);
}

TEST(Hexagon_Testing_GoogleTestRunOutputParserTest, parse__returns_the_correctly_named_test_description)
{
   Hexagon::Testing::GoogleTestRunOutputParser google_test_run_output_parser(BASIC_TEST_RUN_OUTPUT);
   std::vector<Hexagon::Testing::GoogleTestRunTestResult> results = google_test_run_output_parser.parse();

   ASSERT_EQ(false, results.empty());

   Hexagon::Testing::GoogleTestRunTestResult first_test_result = results[0];

   std::string expected_result_test_description = "can_be_created_without_blowing_up";
   std::string actual_result_test_description = first_test_result.get_test_description();

   EXPECT_EQ(expected_result_test_description, actual_result_test_description);
}

TEST(Hexagon_Testing_GoogleTestRunOutputParserTest, parse__returns_the_correctly_set_duration_and_result)
{
   Hexagon::Testing::GoogleTestRunOutputParser google_test_run_output_parser(BASIC_TEST_RUN_OUTPUT);
   std::vector<Hexagon::Testing::GoogleTestRunTestResult> results = google_test_run_output_parser.parse();

   ASSERT_EQ(false, results.empty());

   Hexagon::Testing::GoogleTestRunTestResult &first_test_result = results[0];

   std::string expected_result = "ok";
   std::string actual_result = first_test_result.get_result();

   EXPECT_EQ(expected_result, actual_result);

   int expected_duration_msec = 123;
   int actual_duration_msec = first_test_result.get_duration_msec();

   EXPECT_EQ(expected_duration_msec, actual_duration_msec);
}

