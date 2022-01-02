

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
   , parsed_test_results({})
   , parse_error_messages({})
{
}


GoogleTestRunOutputParser::~GoogleTestRunOutputParser()
{
}


std::vector<Hexagon::Testing::GoogleTestRunTestResult> GoogleTestRunOutputParser::get_parsed_test_results()
{
   return parsed_test_results;
}


std::vector<std::string> GoogleTestRunOutputParser::get_parse_error_messages()
{
   return parse_error_messages;
}


bool GoogleTestRunOutputParser::parse()
{
   parsed_test_results.empty();
   parse_error_messages.empty();
   bool test_suite_is_starting_line_was_found = false;
   bool test_suite_is_starting_line_was_detected_multiple_times = false;
   std::string captured_test_output_body = "";

   Blast::StringSplitter splitter(google_test_run_output, '\n');
   std::vector<std::string> lines = splitter.split();

   Hexagon::Testing::GoogleTestRunTestResult *current_test_case = nullptr;

   for (auto &line : lines)
   {
      // check for the "test suite is starting" line
      {
         std::string test_suite_starts_regex =
            "\\[==========\\] Running [0-9]+ tests? from [0-9]+ test suites?.";
            //an example:
            //"[==========] Running 5 tests from 2 test suites."
         RegexMatcher matcher(line, test_suite_starts_regex);
         std::vector<std::pair<int, int>> matcher_results = matcher.get_match_info();
         bool match_was_found = !matcher_results.empty();
         if (match_was_found)
         {
            if (test_suite_is_starting_line_was_found)
            {
               test_suite_is_starting_line_was_detected_multiple_times = true;
            }
            test_suite_is_starting_line_was_found = true;

            continue;
         }
      }

      // check for "test case run starts" line
      {
         std::string test_run_starts_regex =
            // an example:
            "\\[ RUN      \\] [A-Za-z0-9_]+\\.[A-Za-z0-9_]+";
            // a concrete example:
            //"[ RUN      ] Hexagon_Elements_StageInforOverlayTest.text__has_getters_and_setters";
         RegexMatcher matcher(line, test_run_starts_regex);
         std::vector<std::pair<int, int>> matcher_results = matcher.get_match_info();
         bool match_was_found = !matcher_results.empty();
         if (match_was_found)
         {
            std::pair<std::string, std::string> tokens = extract_test_class_name_and_test_description(line);
            std::string test_class_name = tokens.first;
            std::string test_description = tokens.second;
            Hexagon::Testing::GoogleTestRunTestResult google_test_run_test_result(
               test_class_name,
               test_description,
               "identified",
               -1,
               "",
               ""
            );

            parsed_test_results.push_back(google_test_run_test_result);
            current_test_case = &parsed_test_results.back();

            continue;
         }
      }

      // check for "test passes" line
      {
         std::string test_run_passes_regex =
            // an example:
            "\\[       OK \\] [A-Za-z0-9_]+\\.[A-Za-z0-9_]+ \\([0-9]+ ms\\)";
            // a concrete eample:
            //"[       OK ] Hexagon_Elements_StageInforOverlayTest.text__has_getters_and_setters (13 ms)";
         RegexMatcher matcher(line, test_run_passes_regex);
         std::vector<std::pair<int, int>> matcher_results = matcher.get_match_info();
         bool match_was_found = !matcher_results.empty();
         if (match_was_found)
         {
            if (!current_test_case) throw std::runtime_error("asdfasdf \"current_test_case\" expected");
            std::string result_to_set = "ok";
            int duration_msec_to_set = extract_ms(line);

            current_test_case->set_result(result_to_set);
            current_test_case->set_duration_msec(duration_msec_to_set);

            // end parsing for this test cases
            current_test_case = nullptr;

            continue;
         }
      }

      // check for "test fails" line
      {
         std::string test_run_passes_regex =
            // an example:
            "\\[  FAILED  \\] [A-Za-z0-9_]+\\.[A-Za-z0-9_]+ \\([0-9]+ ms\\)";
            // a concrete example:
            //"[ FAILED   ] Hexagon_Elements_StageInforOverlayTest.text__has_getters_and_setters (23 ms)";
         RegexMatcher matcher(line, test_run_passes_regex);
         std::vector<std::pair<int, int>> matcher_results = matcher.get_match_info();
         bool match_was_found = !matcher_results.empty();
         if (match_was_found)
         {
            if (!current_test_case) throw std::runtime_error("asdfasdfasdfasdf \"current_test_case\" expected");
            std::string result_to_set = "failed";
            int duration_msec_to_set = extract_ms(line);

            current_test_case->set_result(result_to_set);
            current_test_case->set_duration_msec(duration_msec_to_set);

            // end parsing for this test cases
            current_test_case = nullptr;

            continue;
         }
      }

      // if it's not any of the known detected lines,
      // and there is a current test case in RUN,
      // capture the line as body output
      {
         if (current_test_case)
         {
            std::string output_body = current_test_case->get_output_body();
            if (output_body.empty())
            {
               // if it's empty, set it
               current_test_case->set_output_body(line);
            }
            else
            {
               // otherwise if there's already content in it, append the line
               current_test_case->set_output_body(current_test_case->get_output_body() + "\n" + line);
            }
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

   if (!test_suite_is_starting_line_was_found)
   {
      parse_error_messages.push_back("expected test suite start line is missing");
   }
   if (test_suite_is_starting_line_was_detected_multiple_times)
   {
      parse_error_messages.push_back("test suite start line detected multiple times");
   }

   return parse_error_messages.empty();
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
} // namespace Testing
} // namespace Hexagon


