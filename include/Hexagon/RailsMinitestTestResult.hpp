#pragma once


#include <string>
#include <ostream>


class RailsMinitestTestResult
{
public:
   enum test_state_t
   {
      UNKNOWN,
      RUNNING,
      PASS,
      FAILURE,
      SKIPPED,
      ERROR,
   };

   std::string test_name;
   std::string test_time_in_seconds;
   std::string test_result;
   test_state_t test_state;
   std::string test_result_output;
   int error_line_number;

   RailsMinitestTestResult(std::string test_name, std::string test_time_in_seconds, std::string test_result, test_state_t test_state);
   ~RailsMinitestTestResult();

   test_state_t get_test_state() const;
};



std::ostream &operator<<(std::ostream &out, RailsMinitestTestResult::test_state_t const &t);



std::ostream &operator<<(std::ostream &out, RailsMinitestTestResult const &t);



