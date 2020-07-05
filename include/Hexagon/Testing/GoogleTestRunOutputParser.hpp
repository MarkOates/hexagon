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

      public:
         GoogleTestRunOutputParser(std::string google_test_run_output="");
         ~GoogleTestRunOutputParser();


      std::pair<std::string, std::string> extract_test_class_name_and_test_description(std::string line="");
      int extract_ms(std::string line="");
      std::vector<Hexagon::Testing::GoogleTestRunTestResult> parse();
      };
   }
}



