#pragma once


#include <Hexagon/Testing/GoogleTestRunTestResult.hpp>
#include <string>
#include <utility>
#include <vector>


namespace Hexagon
{
   namespace Testing
   {
      class GoogleTestRunOutputParser
      {
      private:
         std::string google_test_run_output;
         std::vector<Hexagon::Testing::GoogleTestRunTestResult> parsed_test_results;
         std::vector<std::string> parse_error_messages;

      public:
         GoogleTestRunOutputParser(std::string google_test_run_output="");
         ~GoogleTestRunOutputParser();


         std::vector<Hexagon::Testing::GoogleTestRunTestResult> get_parsed_test_results();
         std::vector<std::string> get_parse_error_messages();
      bool parse();
      std::pair<std::string, std::string> extract_test_class_name_and_test_description(std::string line="");
      int extract_ms(std::string line="");
      };
   }
}



