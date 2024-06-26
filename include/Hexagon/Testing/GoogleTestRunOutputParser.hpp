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
      public:
         static constexpr char* RESULT_OK = (char*)"ok";
         static constexpr char* RESULT_FAILED = (char*)"failed";

      private:
         std::string google_test_run_output;
         std::vector<Hexagon::Testing::GoogleTestRunTestResult> parsed_test_results;
         std::vector<std::string> error_messages_during_parsing;
         std::pair<std::string, std::string> extract_test_class_name_and_test_description(std::string line="");
         int extract_ms(std::string line="");

      protected:


      public:
         GoogleTestRunOutputParser(std::string google_test_run_output="[unset-google_test_run_output]");
         ~GoogleTestRunOutputParser();

         void set_google_test_run_output(std::string google_test_run_output);
         std::vector<Hexagon::Testing::GoogleTestRunTestResult> get_parsed_test_results() const;
         std::vector<std::string> get_error_messages_during_parsing() const;
         bool parse();
      };
   }
}



