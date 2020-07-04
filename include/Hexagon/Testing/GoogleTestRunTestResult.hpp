#pragma once


#include <string>


namespace Hexagon
{
   namespace Testing
   {
      class GoogleTestRunTestResult
      {
      private:
         std::string test_class_name;
         std::string test_description;
         std::string result;
         int duration_msec;
         std::string failure_message;

      public:
         GoogleTestRunTestResult(std::string test_class_name="", std::string test_description="", std::string result="", int duration_msec=0, std::string failure_message="");
         ~GoogleTestRunTestResult();


      };
   }
}



