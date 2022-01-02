

#include <Hexagon/Testing/GoogleTestRunTestResult.hpp>



namespace Hexagon
{
namespace Testing
{


GoogleTestRunTestResult::GoogleTestRunTestResult(std::string test_class_name, std::string test_description, std::string result, int duration_msec, std::string output_body, std::string failure_message)
   : test_class_name(test_class_name)
   , test_description(test_description)
   , result(result)
   , duration_msec(duration_msec)
   , output_body(output_body)
   , failure_message(failure_message)
{
}


GoogleTestRunTestResult::~GoogleTestRunTestResult()
{
}


void GoogleTestRunTestResult::set_test_class_name(std::string test_class_name)
{
   this->test_class_name = test_class_name;
}


void GoogleTestRunTestResult::set_test_description(std::string test_description)
{
   this->test_description = test_description;
}


void GoogleTestRunTestResult::set_result(std::string result)
{
   this->result = result;
}


void GoogleTestRunTestResult::set_duration_msec(int duration_msec)
{
   this->duration_msec = duration_msec;
}


void GoogleTestRunTestResult::set_output_body(std::string output_body)
{
   this->output_body = output_body;
}


void GoogleTestRunTestResult::set_failure_message(std::string failure_message)
{
   this->failure_message = failure_message;
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


std::string GoogleTestRunTestResult::get_output_body()
{
   return output_body;
}


std::string GoogleTestRunTestResult::get_failure_message()
{
   return failure_message;
}


} // namespace Testing
} // namespace Hexagon


