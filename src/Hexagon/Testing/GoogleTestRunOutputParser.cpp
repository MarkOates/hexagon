

#include <Hexagon/Testing/GoogleTestRunOutputParser.hpp>
#include <Hexagon/RegexMatcher.hpp>
#include <Blast/StringSplitter.hpp>
#include <iostream>


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

int GoogleTestRunOutputParser::extract_ms(std::string line)
{
int result = 0;
// example string: "[       OK ] Hexagon_Elements_StageInforOverlayTest.text__has_getters_and_setters (312 ms)";
std::string::size_type left_paren_pos = line.find(" (");
if (left_paren_pos == std::string::npos) return 0;
std::string::size_type right_paren_pos = line.find(" ms)");
if (right_paren_pos == std::string::npos) return 0;

std::string extracted_ms_as_string = line.substr(left_paren_pos + 2, right_paren_pos - left_paren_pos - 2);
return atoi(extracted_ms_as_string.c_str());

}

std::vector<Hexagon::Testing::GoogleTestRunTestResult> GoogleTestRunOutputParser::parse()
{
std::vector<Hexagon::Testing::GoogleTestRunTestResult> result;
Blast::StringSplitter splitter(google_test_run_output, '\n');
std::vector<std::string> lines = splitter.split();

Hexagon::Testing::GoogleTestRunTestResult *current_test_case = nullptr;

for (auto &line : lines)
{
   // check for "test run starts" line
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
         current_test_case = &result.back();
      }
   }

   // check for "test passes" line
   {
      std::string test_run_passes_regex =
         "\\[       OK \\] [A-Za-z0-9_]+\\.[A-Za-z0-9_]+ \\([0-9]+ ms\\)";
         //an example:
         //"[ RUN      ] Hexagon_Elements_StageInforOverlayTest.text__has_getters_and_setters";
      RegexMatcher matcher(line, test_run_passes_regex);
      std::vector<std::pair<int, int>> matcher_results = matcher.get_match_info();
      if (!matcher_results.empty())
      {
         if (!current_test_case) throw std::runtime_error("asdfasdf \"current_test_case\" expected");
         std::string result_to_set = "ok";
         int duration_msec_to_set = extract_ms(line);

         current_test_case->set_result(result_to_set);
         current_test_case->set_duration_msec(duration_msec_to_set);
      }
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


