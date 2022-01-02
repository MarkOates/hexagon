
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Hexagon/Testing/GoogleTestRunOutputParser.hpp>

using ::testing::Contains;

const std::string BASIC_PASSING_TEST_RUN_OUTPUT = R"TEST_FIXTURE(
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


const std::string FAILING_TEST_RUN_OUTPUT = R"TEST_FIXTURE(
[==========] Running 5 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 5 tests from Hexagon_Testing_GoogleTestRunOutputParserTest
[ RUN      ] Hexagon_Testing_GoogleTestRunOutputParserTest.can_be_created_without_blowing_up
[       OK ] Hexagon_Testing_GoogleTestRunOutputParserTest.can_be_created_without_blowing_up (0 ms)
[ RUN      ] Hexagon_Testing_GoogleTestRunOutputParserTest.parse__returns_the_expected_number_of_test_results
tests/Hexagon/Testing/GoogleTestRunOutputParserTest.cpp:42: Failure
Expected: (5) != (results.size()), actual: 5 vs 5
[  FAILED  ] Hexagon_Testing_GoogleTestRunOutputParserTest.parse__returns_the_expected_number_of_test_results (6 ms)
[ RUN      ] Hexagon_Testing_GoogleTestRunOutputParserTest.parse__returns_the_correctly_named_test_class
[       OK ] Hexagon_Testing_GoogleTestRunOutputParserTest.parse__returns_the_correctly_named_test_class (6 ms)
[ RUN      ] Hexagon_Testing_GoogleTestRunOutputParserTest.parse__returns_the_correctly_named_test_description
[       OK ] Hexagon_Testing_GoogleTestRunOutputParserTest.parse__returns_the_correctly_named_test_description (6 ms)
[ RUN      ] Hexagon_Testing_GoogleTestRunOutputParserTest.parse__returns_the_correctly_set_duration_and_result
[       OK ] Hexagon_Testing_GoogleTestRunOutputParserTest.parse__returns_the_correctly_set_duration_and_result (6 ms)
[----------] 5 tests from Hexagon_Testing_GoogleTestRunOutputParserTest (24 ms total)

[----------] Global test environment tear-down
[==========] 5 tests from 1 test suite ran. (24 ms total)
[  PASSED  ] 4 tests.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] Hexagon_Testing_GoogleTestRunOutputParserTest.parse__returns_the_expected_number_of_test_results

 1 FAILED TEST
)TEST_FIXTURE";


TEST(Hexagon_Testing_GoogleTestRunOutputParserTest, can_be_created_without_blowing_up)
{
   Hexagon::Testing::GoogleTestRunOutputParser google_test_run_output_parser;
}

TEST(Hexagon_Testing_GoogleTestRunOutputParserTest, parse__returns_true_if_the_parsing_was_successful)
{
   Hexagon::Testing::GoogleTestRunOutputParser google_test_run_output_parser(BASIC_PASSING_TEST_RUN_OUTPUT);
   ASSERT_EQ(true, google_test_run_output_parser.parse());
}

TEST(Hexagon_Testing_GoogleTestRunOutputParserTest, parse__returns_false_if_the_parsing_was_not_successful)
{
   std::string unparseable_content = "Some content that has nothing to do with the expected parseable stuff.";
   Hexagon::Testing::GoogleTestRunOutputParser google_test_run_output_parser(unparseable_content);
   ASSERT_EQ(false, google_test_run_output_parser.parse());
}

TEST(Hexagon_Testing_GoogleTestRunOutputParserTest, parse__when_parsing_was_successful__will_have_no_error_messages)
{
   Hexagon::Testing::GoogleTestRunOutputParser google_test_run_output_parser(BASIC_PASSING_TEST_RUN_OUTPUT);
   ASSERT_EQ(true, google_test_run_output_parser.parse());
   ASSERT_EQ(true, google_test_run_output_parser.get_parse_error_messages().empty());
}

TEST(Hexagon_Testing_GoogleTestRunOutputParserTest, parse__when_unsuccessful__will_store_error_messages)
{
   std::string unparseable_content = "Some content that has nothing to do with the expected parseable stuff.";
   Hexagon::Testing::GoogleTestRunOutputParser google_test_run_output_parser(unparseable_content);

   ASSERT_EQ(false, google_test_run_output_parser.parse());
   std::vector<std::string> error_messages = google_test_run_output_parser.get_parse_error_messages();
   ASSERT_EQ(false, error_messages.empty());

   std::string expected_error_message = "expected test suite start line is missing";
   ASSERT_THAT(error_messages, Contains(expected_error_message));
}

TEST(Hexagon_Testing_GoogleTestRunOutputParserTest,
   parse__when_parsing_nested_test_run_outputs__produces_the_expected_error)
{
   std::string test_run_output_with_nested_test_outputs = std::string("")
      + "[==========] Running 5 tests from 2 test suites." + "\n"
      + "[----------] Global test environment set-up." + "\n"
      + "[==========] Running 1 test from 1 test suite." + "\n"
      + "[----------] Global test environment set-up." + "\n";

   Hexagon::Testing::GoogleTestRunOutputParser google_test_run_output_parser(
      test_run_output_with_nested_test_outputs
   );

   ASSERT_EQ(false, google_test_run_output_parser.parse());
   std::vector<std::string> error_messages = google_test_run_output_parser.get_parse_error_messages();
   ASSERT_EQ(false, error_messages.empty());

   std::string expected_error_message = "test suite start line detected multiple times";
   ASSERT_THAT(error_messages, Contains(expected_error_message));
}

TEST(Hexagon_Testing_GoogleTestRunOutputParserTest, parse__returns_the_expected_number_of_test_results)
{
   Hexagon::Testing::GoogleTestRunOutputParser google_test_run_output_parser(BASIC_PASSING_TEST_RUN_OUTPUT);
   ASSERT_EQ(true, google_test_run_output_parser.parse());
   std::vector<Hexagon::Testing::GoogleTestRunTestResult> results =
      google_test_run_output_parser.get_parsed_test_results();
   ASSERT_EQ(5, results.size());
}

TEST(Hexagon_Testing_GoogleTestRunOutputParserTest, parse__returns_the_correctly_named_test_class)
{
   Hexagon::Testing::GoogleTestRunOutputParser google_test_run_output_parser(BASIC_PASSING_TEST_RUN_OUTPUT);
   ASSERT_EQ(true, google_test_run_output_parser.parse());
   std::vector<Hexagon::Testing::GoogleTestRunTestResult> results =
      google_test_run_output_parser.get_parsed_test_results();

   ASSERT_EQ(false, results.empty());

   Hexagon::Testing::GoogleTestRunTestResult first_test_result = results[0];

   std::string expected_result_class_name = "Hexagon_Elements_StageInfoOverlayTest";
   std::string actual_result_class_name = first_test_result.get_test_class_name();

   EXPECT_EQ(expected_result_class_name, actual_result_class_name);
}

TEST(Hexagon_Testing_GoogleTestRunOutputParserTest, parse__returns_the_correctly_named_test_description)
{
   Hexagon::Testing::GoogleTestRunOutputParser google_test_run_output_parser(BASIC_PASSING_TEST_RUN_OUTPUT);
   ASSERT_EQ(true, google_test_run_output_parser.parse());
   std::vector<Hexagon::Testing::GoogleTestRunTestResult> results =
      google_test_run_output_parser.get_parsed_test_results();

   ASSERT_EQ(false, results.empty());

   Hexagon::Testing::GoogleTestRunTestResult first_test_result = results[0];

   std::string expected_result_test_description = "can_be_created_without_blowing_up";
   std::string actual_result_test_description = first_test_result.get_test_description();

   EXPECT_EQ(expected_result_test_description, actual_result_test_description);
}

TEST(Hexagon_Testing_GoogleTestRunOutputParserTest, parse__returns_the_correctly_set_duration_and_result)
{
   Hexagon::Testing::GoogleTestRunOutputParser google_test_run_output_parser(BASIC_PASSING_TEST_RUN_OUTPUT);
   ASSERT_EQ(true, google_test_run_output_parser.parse());
   std::vector<Hexagon::Testing::GoogleTestRunTestResult> results =
      google_test_run_output_parser.get_parsed_test_results();

   ASSERT_EQ(false, results.empty());

   Hexagon::Testing::GoogleTestRunTestResult &first_test_result = results[0];

   std::string expected_result = "ok";
   std::string actual_result = first_test_result.get_result();

   EXPECT_EQ(expected_result, actual_result);

   int expected_duration_msec = 123;
   int actual_duration_msec = first_test_result.get_duration_msec();

   EXPECT_EQ(expected_duration_msec, actual_duration_msec);
}

TEST(Hexagon_Testing_GoogleTestRunOutputParserTest, parse__returns_the_correctly_set_duration_and_result_on_failure)
{
   // TODO: split this into multiple tests
   Hexagon::Testing::GoogleTestRunOutputParser google_test_run_output_parser(FAILING_TEST_RUN_OUTPUT);
   ASSERT_EQ(true, google_test_run_output_parser.parse());
   std::vector<Hexagon::Testing::GoogleTestRunTestResult> results =
      google_test_run_output_parser.get_parsed_test_results();

   ASSERT_EQ(false, results.empty());

   Hexagon::Testing::GoogleTestRunTestResult &second_test_result = results[1];

   std::string expected_result = "failed";
   std::string actual_result = second_test_result.get_result();

   EXPECT_EQ(expected_result, actual_result);

   int expected_duration_msec = 6;
   int actual_duration_msec = second_test_result.get_duration_msec();

   EXPECT_EQ(expected_duration_msec, actual_duration_msec);
}

TEST(Hexagon_Testing_GoogleTestRunOutputParserTest,
   parse__correctly_extracts_the_raw_output_of_a_test_that_contained_output)
{
   // TODO
}

TEST(Hexagon_Testing_GoogleTestRunOutputParserTest,
   parse__correctly_extracts_the_expected_and_actual_message_on_a_failed_test)
{
   // TODO
   // extract out expected and actual from:
   //   Expected: (5) != (results.size()), actual: 5 vs 5
   // NOTE there could be other formats for output

   Hexagon::Testing::GoogleTestRunOutputParser google_test_run_output_parser(FAILING_TEST_RUN_OUTPUT);
   ASSERT_EQ(true, google_test_run_output_parser.parse());
   std::vector<Hexagon::Testing::GoogleTestRunTestResult> results =
      google_test_run_output_parser.get_parsed_test_results();

   Hexagon::Testing::GoogleTestRunTestResult &second_test_result = results[1];

   std::string expected_output_body = "needs-to-be-parsed";
   std::string actual_output_body = second_test_result.get_output_body();

   //EXPECT_EQ(expected_output_body, actual_output_body);
}

