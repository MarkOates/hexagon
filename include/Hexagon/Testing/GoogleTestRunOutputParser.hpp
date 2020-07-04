#pragma once


#include <Hexagon/Testing/GoogleTestRunTestResult.hpp>
#include <string>
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


      std::vector<Hexagon::Testing::GoogleTestRunTestResult> parse();
      };
   }
}



