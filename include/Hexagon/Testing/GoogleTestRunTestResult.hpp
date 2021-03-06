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

         void set_test_class_name(std::string test_class_name);
         void set_test_description(std::string test_description);
         void set_result(std::string result);
         void set_duration_msec(int duration_msec);
         void set_failure_message(std::string failure_message);
         std::string get_test_class_name();
         std::string get_test_description();
         std::string get_result();
         int get_duration_msec();
         std::string get_failure_message();
      };
   }
}



