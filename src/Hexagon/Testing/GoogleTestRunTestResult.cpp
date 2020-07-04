

#include <Hexagon/Testing/GoogleTestRunTestResult.hpp>



namespace Hexagon
{
namespace Testing
{


GoogleTestRunTestResult::GoogleTestRunTestResult(std::string test_class_name, std::string test_description, std::string result, int duration_msec, std::string failure_message)
   : test_class_name(test_class_name)
   , test_description(test_description)
   , result(result)
   , duration_msec(duration_msec)
   , failure_message(failure_message)
{
}


GoogleTestRunTestResult::~GoogleTestRunTestResult()
{
}


std::string GoogleTestRunTestResult::get_test_class_name()
{
   return test_class_name;
}


std::string GoogleTestRunTestResult::get_test_description()
{
   return test_description;
}


std::string GoogleTestRunTestResult::get_result()
{
   return result;
}


int GoogleTestRunTestResult::get_duration_msec()
{
   return duration_msec;
}


std::string GoogleTestRunTestResult::get_failure_message()
{
   return failure_message;
}


} // namespace Testing
} // namespace Hexagon


