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


         std::string get_test_class_name();
         std::string get_test_description();
         std::string get_result();
         int get_duration_msec();
         std::string get_failure_message();
      };
   }
}



