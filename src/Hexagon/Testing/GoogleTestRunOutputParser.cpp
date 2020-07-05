

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


std::pair<std::string, std::string> GoogleTestRunOutputParser::extract_test_class_name_and_test_description(std::string line)
{
int initial_bracket_length = 13;
// example string: "[ RUN      ] Hexagon_Elements_StageInforOverlayTest.text__has_getters_and_setters";
std::string::size_type dot_pos = line.find('.');
if (dot_pos == std::string::npos) return {};

std::string test_class_name = line.substr(initial_bracket_length, dot_pos - initial_bracket_length);
std::string test_description = line.substr(dot_pos + 1);

return std::pair<std::string, std::string>{ test_class_name, test_description };

}

std::vector<Hexagon::Testing::GoogleTestRunTestResult> GoogleTestRunOutputParser::parse()
{
std::vector<Hexagon::Testing::GoogleTestRunTestResult> result;
Blast::StringSplitter splitter(google_test_run_output, '\n');
std::vector<std::string> lines = splitter.split();

for (auto &line : lines)
{
   std::string test_run_starts_regex =
      "\\[ RUN      \\] [A-Za-z0-9_]+\\.[A-Za-z0-9_]+";
      //an example:
      //"[ RUN      ] Hexagon_Elements_StageInforOverlayTest.text__has_getters_and_setters";
   RegexMatcher matcher(line, test_run_starts_regex);
   std::vector<std::pair<int, int>> matcher_results = matcher.get_match_info();
   if (!matcher_results.empty())
   {
      std::pair<std::string, std::string> tokens = extract_test_class_name_and_test_description(line);
      std::string test_class_name = tokens.first;
      std::string test_description = tokens.second;
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


