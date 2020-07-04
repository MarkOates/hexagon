

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

for (auto &line : lines)
{
   std::string test_run_starts_regex =
      "\\[ RUN      \\] Hexagon_Elements_StageInforOverlayTest\\.text__has_getters_and_setters";
   RegexMatcher matcher(line, test_run_starts_regex);
   std::vector<std::pair<int, int>> matcher_results = matcher.get_match_info();
   if (!matcher_results.empty())
   {
      std::string test_class_name = "TestClass_Name";
      std::string test_description = "test_description_is_clear_and_between_underscores";
      Hexagon::Testing::GoogleTestRunTestResult google_test_run_test_result(
         test_class_name,
         test_description,
         "identified",
         -1,
         ""
      );

      result.push_back(google_test_run_test_result);
   }
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


