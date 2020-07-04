

#include <Hexagon/Testing/GoogleTestRunOutputParser.hpp>
#include <Hexagon/RegexMatcher.hpp>
#include <Blast/StringSplitter.hpp>


namespace Hexagon
{
namespace Testing
{


GoogleTestRunOutputParser::GoogleTestRunOutputParser(std::string google_test_run_output)
   : google_test_run_output(google_test_run_output)
{
}


GoogleTestRunOutputParser::~GoogleTestRunOutputParser()
{
}


std::vector<Hexagon::Testing::GoogleTestRunTestResult> GoogleTestRunOutputParser::parse()
{
std::vector<Hexagon::Testing::GoogleTestRunTestResult> result;
Blast::StringSplitter splitter(google_test_run_output, '\n');
std::vector<std::string> lines = splitter.split();

{
   std::string test_run_starts_regex =
      "[ RUN      ] Hexagon_Elements_StageInforOverlayTest.text__has_getters_and_setters";
   std::vector<std::pair<int, int>> matcher_results =
      RegexMatcher(google_test_run_output, test_run_starts_regex).get_match_info();

   Hexagon::Testing::GoogleTestRunTestResult google_test_run_test_result(
      "TestClass_Name",
      "test_description_is_clear_and_between_spaces",
      "passed",
      123,
      "failure message"
   );

   result.push_back(google_test_run_test_result);
}

//patterns:
//[==========] Running 5 tests from 2 test suites.
//[----------] 4 tests from Hexagon_Elements_StageInforOverlayTest
//[----------] 4 tests from Hexagon_Elements_StageInforOverlayTest (131 ms total)
//[ RUN      ] Hexagon_Elements_StageInforOverlayTest.text__has_getters_and_setters
//[       OK ] Hexagon_Elements_StageInforOverlayTest.text__has_getters_and_setters (0 ms)
//[==========] 5 tests from 2 test suites ran. (131 ms total)
//[==========] # tests from # test suites ran. (# ms total)
//[  PASSED  ] 5 tests.

//std::string failing_case = "just some unparsable garbage string";
//if (google_test_run_output == failing_case) return {};

return result;

}
} // namespace Testing
} // namespace Hexagon


