#pragma once


#include <Hexagon/RailsMinitestTestResult.hpp>
#include <string>
#include <vector>


namespace Hexagon
{
   class RailsTestOutputParser
   {
   private:
      bool processed;
      std::string source_test_output;
      std::vector<RailsMinitestTestResult> test_result_lines;

   public:
      RailsTestOutputParser(std::string source_test_output="");
      ~RailsTestOutputParser();


   void process();
   std::vector<RailsMinitestTestResult>& get_test_result_lines();
   };
}



