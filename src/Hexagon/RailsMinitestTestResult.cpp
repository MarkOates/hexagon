#include <Hexagon/RailsMinitestTestResult.hpp>


RailsMinitestTestResult::RailsMinitestTestResult(
      std::string test_name,
      std::string test_time_in_seconds,
      std::string test_result,
      RailsMinitestTestResult::test_state_t test_state
   )
   : test_name(test_name)
   , test_time_in_seconds(test_time_in_seconds)
   , test_result(test_result)
   , test_state(test_state)
   , test_result_output("")
   , error_line_number(-1)
{}


RailsMinitestTestResult::~RailsMinitestTestResult() {}


RailsMinitestTestResult::test_state_t RailsMinitestTestResult::get_test_state() const
{
   return test_state;
}



std::ostream &operator<<(std::ostream &out, RailsMinitestTestResult::test_state_t const &t)
{
   switch(t)
   {
   case RailsMinitestTestResult::UNKNOWN:
      out << "unprocessed";
   break;
   case RailsMinitestTestResult::RUNNING:
      out << "running";
   break;
   case RailsMinitestTestResult::PASS:
      out << "pass";
   break;
   case RailsMinitestTestResult::SKIPPED:
      out << "skip";
   break;
   case RailsMinitestTestResult::FAILURE:
      out << "failure";
   break;
   case RailsMinitestTestResult::ERROR:
      out << "error";
   break;
   }

   return out;
}



std::ostream &operator<<(std::ostream &out, RailsMinitestTestResult const &t)
{
   if (t.test_result == " F") out << "FAILED!!: ";
   out << t.test_name << "||||" << t.test_time_in_seconds << "||||" << t.test_result << "||||" << t.test_state << "||||" << std::endl << "######" << t.test_result_output << std::endl << "######";

   return out;
}




