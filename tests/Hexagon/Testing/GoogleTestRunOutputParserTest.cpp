
#include <gtest/gtest.h>

#include <Hexagon/Testing/GoogleTestRunOutputParser.hpp>

const std::string test_run_output = R"TEST_FIXTURE(
make[1]: Nothing to be done for `/Users/markoates/Repos/hexagon/bin/tests/Hexagon/Elements/StageInfoOverlayTest'.
[==========] Running 5 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 1 test from Hexagon_Elements_StageInfoOverlayTest
[ RUN      ] Hexagon_Elements_StageInfoOverlayTest.can_be_created_without_blowing_up
[       OK ] Hexagon_Elements_StageInfoOverlayTest.can_be_created_without_blowing_up (0 ms)
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

TEST(Hexagon_Testing_GoogleTestRunOutputParserTest, parse__returns_true_if_the_parsing_was_successful)
{
   Hexagon::Testing::GoogleTestRunOutputParser google_test_run_output_parser;
   EXPECT_EQ(true, google_test_run_output_parser.parse());
}
